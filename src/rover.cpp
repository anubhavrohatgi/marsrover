#include "rover.h"

namespace nasa {

int rover::id = 0;

rover::rover(position initP, std::shared_ptr<terrain> ter) : initalPos(initP),terrainInfo(ter)
{
    //ctor
    ++id;
    poseTrail.push_back(initP); //set the inital pose and update the trail array
//    terrainInfo->updateTerrain(id,initP.coordinate); // update the terrain info
}

rover::~rover()
{
    poseTrail.clear();
    //dtor
}


std::string rover::name() const {
    return mName;
}


int rover::getID() const {
    return id;
}


bool rover::decodeCommands(const std::string& cmds)
{
    bool roverLeftTerrain  = false;
    for (const char& c : cmds)
    {
        position prePose = poseTrail.at(poseTrail.size()-1);
        position newPose = prePose;
        //commands are L, R and M
        switch (c) {
        case 'L': /*Orientation LEFT --- AnitClockwise*/
            newPose.orientation = (static_cast<compass>(prePose.orientation - 1) < 1) ?
                        compass::WEST: static_cast<nasa::compass>(prePose.orientation-1);
            break;
        case 'R': /*Orientation RIGHT -- Clockwise*/
            newPose.orientation = (static_cast<compass>(prePose.orientation + 1) > 4) ?
                        compass::NORTH : static_cast<nasa::compass>(prePose.orientation+1);
            break;
        case 'M': /*Move*/
            switch (prePose.orientation) {
            case NORTH:
                newPose.coordinate.y+=1;
                break;
            case EAST:
                newPose.coordinate.x += 1;
                break;
            case SOUTH:
                newPose.coordinate.y -= 1;
                break;
            case WEST:
                newPose.coordinate.x -= 1;
                break;
            case INVALID:
                break;
            }
            break;
        }
        //newpose updated now we check validity w.r.t. terrain

        if(terrainInfo->isOccupied(newPose.coordinate)) {
            std::cout<<"\n["<<mName<<"]"<<"Cant Move Another Rover detected at same position"<<std::endl;
            return false;
        }

        if(terrainInfo->isOutOfBounds(newPose.coordinate)) {
            std::cout<<"\n["<<mName<<"]"<<"Cant Move, Terrain Bounds detected"<<std::endl;
            roverLeftTerrain = true;
            //lets push the last coordinate even though it is out of bounds
            poseTrail.push_back(newPose);
            break;
        }

        poseTrail.push_back(newPose);
    }

    //TODO:
    // what happens when the rover leaves the terrain. Also no idea how the rover will
    // leave the terrain, it can only go out of bounds./
    //Tried now : -- removeRoverFromTerrain()
    if(roverLeftTerrain){
        terrainInfo->removeRoverFromTerrain(id);
        std::cout<<"\n["<<mName<<"]"<<"Rover "<<id<<" left the terrain"<<std::endl;
        return true;
    }

    //all movement successful lets update the terrain with the final coordinates of the rover
    terrainInfo->updateTerrain(id,poseTrail.at(poseTrail.size()-1).coordinate);
    return true;
}


std::string rover::stringifyTrail()
{
    std::string str = "";
    for(const position& p : poseTrail){
        str += "(" + std::to_string(p.coordinate.x) + "," + std::to_string(p.coordinate.y)
                + "," + compassToChar(p.orientation) + ") ";
    }
    return str;
}

}//end of namespace nasa
