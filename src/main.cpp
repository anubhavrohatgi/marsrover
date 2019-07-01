#include <iostream>

#include "common.h"
#include "rover.h"
#include "terrain.h"
#include "fileio.h"

using namespace std;


int main()
{
    nasa::fileio fo("../../rover.txt","../../roverout.txt");
    std::vector<std::pair<nasa::position,std::string> > roversfTxt;
    nasa::cell tercoord;

    if(fo.readFile(roversfTxt,tercoord)){
        std::cout<<"\nRead File with no of rovers : "<<roversfTxt.size()<<"   terrain max : "<<tercoord <<std::endl;

         std::shared_ptr<nasa::terrain> ter = std::make_shared<nasa::terrain>(tercoord.x,tercoord.y);
         std::vector<nasa::rover> rovers; //though not required

        //lets move rovers sequentially
        for(auto k : roversfTxt){
            std::cout<<"Rover   : "<<k.first
                   <<"\nCommand : "<<k.second
                   <<std::endl;

            nasa::rover rov(k.first,ter);
            rov.decodeCommands(k.second);
            std::cout<<"Pose : "<<rov.stringifyTrail()<<std::endl<<std::endl;

            fo.updateFile(rov.getID(),rov.stringifyTrail());
            rovers.push_back(rov);
        }

        rovers.clear();
    }

    roversfTxt.clear();

    return 0;
}



