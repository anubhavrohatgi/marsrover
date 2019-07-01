#include "terrain.h"
#include <algorithm>
namespace nasa {

terrain::terrain(int max_X, int max_Y) : maxX(max_X), maxY(max_Y)
{
    //ctor
    std::cout<<"["<<mName<<"]"<<"terrain created with : ("<<maxX<<","<<maxY<<")"<<std::endl;
}

terrain::~terrain()
{
//    roverLastLoc.clear();
    rovLocMap.clear();
    //dtor
}

bool terrain::isOccupied(const cell& c)
{
    for(std::map<int, cell>::iterator it = rovLocMap.begin(); it != rovLocMap.end(); it++)
    {
        if((it->second) == c)
        {
            return true;
        }
    }
    return false;
}

bool terrain::isOutOfBounds(const cell& c) const
{
    return ((c.x < 0) || (c.y < 0) || (c.x > maxX) || (c.y > maxY)) ? true : false;
}


//cell terrain::getCellAtRoverId(int rover_id)
//{
//    cell c(-1,-1);
//    for_each(roverLastLoc.begin(), roverLastLoc.end(),
//                  [&c, &rover_id](const std::pair<cell, int> &p) {
//        if (p.second == rover_id) {
//            c = p.first;
//        }
//    });
//    return c;
//}



//int terrain::getRoverIdAtCell(const cell& c)
//{
//    std::map<nasa::cell, int>::iterator itr = roverLastLoc.find(c);
//    if(itr != roverLastLoc.end())
//    {
//        return itr->second;
//    } else {
//        return -1;
//    }
//}


void terrain::updateTerrain(int rovId,const cell& loc)
{
    std::map<int,cell>::iterator it= rovLocMap.find(rovId);

    if(it != rovLocMap.end()){
        it->second = loc;
    } else {
        rovLocMap.insert(std::make_pair(rovId,loc));
    }
}


void terrain::removeRoverFromTerrain(int rovId)
{
    auto it = rovLocMap.find(rovId);
    if(it != rovLocMap.end())
        rovLocMap.erase(it);
    else {
        throw "No rover with that Id found";
    }
}


}//end of namespace nasa
