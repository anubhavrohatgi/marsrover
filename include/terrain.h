#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "common.h"

namespace nasa {

/**
 * @brief The terrain class
 *  Describes the plateau terrain
 */
class terrain
{
public:
    /**
     * @brief terrain Initalizes the dimensions of the terrain in x,y coordinates
     * @param max_X Input maximum X coordinate of terrain
     * @param max_Y Input maximum Y coordinate of terrain
     */
    terrain(int max_X, int max_Y);
    ~terrain();

    /**
     * @brief name Outputs name of the class
     * @return output name
     */
    std::string name() const {
        return mName;
    }

    /**
     * @brief isOccupied Checks if the coordinate on terrain is
     *  occupied by any rover
     * @param c Input coordinate
     * @return true if occupied
     */
    bool isOccupied(const cell& c);


    /**
     * @brief isOutOfBounds Checks if the coordinate is not on
     *  terrain plain
     * @param c Input coordinate
     * @return true if coordinate is outside the terrain boundary
     */
    bool isOutOfBounds(const cell& c) const;

//    int getRoverIdAtCell(const cell& c);
//    cell getCellAtRoverId(int rover_id);

    /**
     * @brief updateTerrain Updates the rover location map. Updates with the
     *  last location to which the rover was moved
     * @param rovId Input rover id
     * @param loc Input location
     */
    void updateTerrain(int rovId, const cell& loc);


    /**
     * @brief removeRoverFromTerrain removes the rover from terrain if the. Updates the
     *  rover location map by erasing the rover with requested rover id
     * @param rovId Input rover id
     */
    void removeRoverFromTerrain(int rovId);


    /**
     * @brief getTerrainMap Outputs the terrain
     * @return
     */
    std::map<int,cell> getTerrainMap() const {
        return rovLocMap;
    }

private:
    const std::string mName = "TERRAIN";
    int maxX;
    int maxY;
//    std::map<cell,int> roverLastLoc;
    std::map<int,cell> rovLocMap;
};

}//end of namespace nasa

#endif // TERRAIN_H
