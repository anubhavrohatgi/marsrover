#include "fileio.h"
#include <cstring>
#include <errno.h>

namespace nasa {


fileio::fileio(const std::string& infile, const std::string& outfile)
{
    inFile = infile;
    outFile = outfile;

    std::remove(outFile.c_str()); //no error handled here also a wrong choice of adding this in a ctor

    //ctor
}


bool fileio::readFile(std::vector<std::pair<nasa::position,std::string> >& rovers, nasa::cell& tercoord)
{

    //clear junk if any
    rovers.clear();

    if(ifExists(inFile)) {
        std::ifstream rfs;
        rfs.open(inFile);

        if (rfs.is_open()) {


            std::string line;

            //read the first line to get terrain info
            if(getline(rfs, line)) {
                //this read the terrain dimensions
                std::vector<std::string> terMax;
                line = nasa::trim(line);
                strSplit(line,terMax);
                if(terMax.size() == 2){
                    tercoord.x = std::atoi(terMax.at(0).c_str());
                    tercoord.y = std::atoi(terMax.at(1).c_str());
                } else {
                    std::cout<<"\n["<<mName<<"]"<<"No Terrain Dimensions were specified."<<std::endl;
                    rfs.close();
                    return false;
                }
            }

            //lets read two lines at a time now
            while (getline(rfs, line)) {
                std::pair<nasa::position,std::string> rov;
                std::vector<std::string> psv;
                line = nasa::trim(line);

                if(line.empty())
                    continue;

                strSplit(line,psv);

                if(psv.size() != 3)
                    continue;

                //extract the position -- not validated compass line string
                //what if it is not a single char
                rov.first.coordinate.x = std::atoi(psv[0].c_str());
                rov.first.coordinate.y = std::atoi(psv[1].c_str());
                rov.first.orientation =  nasa::charToCompass(psv[2][0]);

                if(std::getline(rfs, line)) {
                    // correctly read commands stream
                    line = nasa::trim(line);
                    if(!line.empty()) {
                        rov.second = line;

                        if(!nasa::validateCommands(line)){
                            std::cout<<"\n["<<mName<<"]"<<"Invalid command string"<<std::endl;
                            continue;
                        }

                        rovers.push_back(rov);
                    }
                } else {
                    // you are at end of the file and line is not read
                    break;
                }
            }

            rfs.close();
        } else {
            std::cout<<"\n["<<mName<<"]"<<"Input File is not opened"<<std::endl;
            return false;
        }

    } else {
        std::cout<<"\n["<<mName<<"]"<<"Can't Open Input File"<<std::endl;
        return false;
    }

    return true;
}


bool fileio::updateFile(int rovId, std::string trail)
{
    std::ofstream file;

    try {
        file.open(outFile, std::ios::out | std::ios::app);
        if (file.fail()) {
            throw std::ios_base::failure(std::strerror(errno));
        }

        file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);
        file <<"RoverID("<<rovId<<") : " <<trail << std::endl;

    } catch (const char* s){
        std::cout<<"\n["<<mName<<"]"<<"Can't Open Output File @ exception "<<s<<std::endl;
        file.close();
        return  false;
    }

    file.close();

    return true;
}



bool fileio::ifExists(const std::string& fname)
{
    std::ifstream f(fname.c_str());
    return f.good();
}


void fileio::strSplit(const std::string& str, std::vector<std::string>& cont, char delim)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

}//end of namespace nasa
