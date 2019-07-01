#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "common.h"
#include <algorithm>

namespace nasa {

/**
 * @brief The fileio class Handles the file input output actions
 */
class fileio
{
public:
    /**
     * @brief fileio Instantiates the class
     * @param infile Input filename
     * @param outfile Output filename
     */
    fileio(const std::string& infile, const std::string& outfile);


    /**
     * @brief readFile Reads the text file and obtains command and info about rovers
     * @param rovers Output rover info -> initial position and command string
     * @param tercoord Output info about terrains max dimensions
     * @return true if read is successful
     */
    bool readFile(std::vector<std::pair<nasa::position,std::string> >& rovers, nasa::cell& tercoord);

    /**
     * @brief updateFile Append to the file the trail of the rovers
     * @param rovId Rover ID
     * @param trail input trail string
     * @return true if update is successful
     */
    bool updateFile(int rovId,std::string trail);

private:
    const std::string mName = "FILEIO";
    std::string inFile;
    std::string outFile;

    /**
     * @brief ifExists Checks if the file exsists
     * @param fname Input filename
     * @return true if file exsists
     */
    bool ifExists(const std::string& fname);


    /**
     * @brief strSplit Splits the string w.r.t. delimiter
     * @param str Input string to be split
     * @param cont Output vector of strings, separated ones
     * @param delim Input delimiter
     */
    void strSplit(const std::string& str, std::vector<std::string>& cont, char delim = ' ');
};

}//end of namespace nasa

#endif // FILEIO_H
