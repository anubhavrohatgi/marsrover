#include "common.h"
#include "rover.h"
#include "terrain.h"
#include "fileio.h"
#include <gtest/gtest.h>

namespace {

const int maxX = 5;
const int maxY = 5;

TEST(terrain,ctorwithArguments) {
    const nasa::terrain ter(maxX,maxY);
    EXPECT_LT(0, maxX);
    EXPECT_LT(0,maxY);
}


const nasa::cell negC(-1,-1);
const nasa::cell lbC(0,0);
const nasa::cell ubC(5,5);
const nasa::cell midC(2,2);

TEST(terrain, isoccupied) {
    nasa::terrain ter(maxX,maxY);
    ter.updateTerrain(2,midC);
    EXPECT_TRUE(ter.isOccupied(midC));
    EXPECT_FALSE(ter.isOccupied(lbC));
    EXPECT_FALSE(ter.isOccupied(negC));
}

TEST(terrain, isoutofbounds) {
    nasa::terrain ter(maxX,maxY);
    EXPECT_FALSE(ter.isOutOfBounds(ubC));
    EXPECT_FALSE(ter.isOutOfBounds(lbC));
    EXPECT_FALSE(ter.isOutOfBounds(midC));
    EXPECT_TRUE(ter.isOutOfBounds(negC));
}

TEST(terrain, removeRoverFromTerrain) {
    nasa::terrain ter(maxX,maxY);
//    ter.updateTerrain(2,midC);

    EXPECT_NO_THROW({
          ter.removeRoverFromTerrain(2);
    });
}

}  // namespace

