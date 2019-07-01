#ifndef ROVER_H
#define ROVER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "common.h"
#include "terrain.h"

namespace nasa {

/**
 * @brief The rover class Describes the rover entity
 */
class rover
{
public:
    /**
     * @brief rover Initates the rover object with default values
     * @param initP Input initial position of rover
     * @param ter Input terrain map
     */
    rover(position initP, std::shared_ptr<terrain> ter);

    ~rover();

    /**
     * @brief name Outputs the name of the class
     * @return Output name
     */
    std::string name() const;

    /**
     * @brief getID returns the allocated id of the rover
     * @return output rover id
     */
    int getID() const;

    /**
     * @brief decodeCommands Decodes the command string and moves the rover
     * @param cmds Input command string
     * @return true if rover has moved or orientation is updated
     */
    bool decodeCommands(const std::string& cmds);


    /**
     * @brief stringifyTrail Stringifies the rover movement trail
     * @return output trail string
     */
    std::string stringifyTrail();


private:
    const std::string mName = "ROVER";
    static int id;
    position initalPos;
    std::shared_ptr<terrain> terrainInfo;
    std::vector<position> poseTrail;

};


}//end of namespace

#endif // ROVER_H
