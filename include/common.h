#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

namespace nasa {

/**
 * @brief The compass enum
 *      Describes the orientation and direction
 */
enum compass {
    INVALID = 0,
    NORTH,      //1
    EAST,       //2
    SOUTH,      //3
    WEST        //4
};


/**
 * @brief charToCompass Converts the char to orientation enum value
 * @param s Input Orientaion char
 * @return output compass enum
 */
inline compass charToCompass(char s)
{
    switch (s) {
    case 'N':
        return NORTH;
    case 'S':
        return  SOUTH;
    case 'E':
        return EAST;
    case 'W':
        return WEST;
    default:
        return INVALID;
    }
}


/**
 * @brief compassToChar Converts the compass enum value to chracter
 * @param c Input compass enum
 * @return output respective orientation char
 */
inline char compassToChar(compass c)
{
    switch (c) {
    case NORTH:
        return 'N';
    case SOUTH:
        return  'S';
    case EAST:
        return 'E';
    case WEST:
        return 'W';
    default:
        return 'I';
    }
}


/**
 * @brief The cell struct
 *  Describes the location in x,y coordinates on the terrain map
 */
struct cell {
    int x;
    int y;

    cell(){
        x = 0;
        y=0;
    }

    cell(int _x, int _y){
        x = _x;
        y = _y;
    }

    inline bool operator==(const cell& c) const {
        return ((this->x == c.x) && (this->y == c.y))?true:false;
    }

    inline bool operator<(const cell& c) const
      {
          if (x < c.x)
          {
              return true;
          } else if (x == c.x) {
              if (y < c.y)
              {
                  return true;
              }
              else if (y == c.x)
              {
                  return false;
              } else {
                  //;
              }
          }
              return false;
      }

    friend std::istream& operator>>(std::istream& is, cell& c)
    {
        is >> c.x >>c.y;
        return is;
    }

    friend std::ostream & operator << (std::ostream &out, const cell &c)
    {
        out << c.x<<" "<<c.y;
        return out;
    }

    friend std::ifstream& operator>>(std::ifstream& is, cell& c)
    {
        is >> c.x >>c.y;
        return is;
    }

    friend std::ofstream & operator << (std::ofstream &out, const cell &c)
    {
        out << c.x<<","<<c.y;
        return out;
    }
};


/**
 * @brief The position struct
 *  Describes the location and orientation of rover on the terrain
 */
struct position{
    cell coordinate;
    compass orientation;

    position(){
        orientation = INVALID;
    }

    friend std::istream& operator>>(std::istream& is, position& p)
    {
        char n;
        is >> p.coordinate.x >> p.coordinate.y>>n;
        p.orientation = charToCompass(n);
        return is;
    }

    friend std::ostream & operator << (std::ostream &out, const position &p)
    {
        out << p.coordinate<<" "<<compassToChar(p.orientation);
        return out;
    }

    friend std::ifstream& operator>>(std::ifstream& is, position& p)
    {
        char n;
        is >> p.coordinate.x >> p.coordinate.y>>n;
        p.orientation = charToCompass(n);
        return is;
    }

    friend std::ofstream & operator << (std::ofstream &out, const position &p)
    {
        out << "("<<p.coordinate<<","<<compassToChar(p.orientation)<<") ";
        return out;
    }
};


/**
 * @brief validateCommands Validates the input command string
 * @param cmd Input command string
 * @return true if valid commands L,R or M are passed
 */
inline bool validateCommands(const std::string& cmd)
{
    std::string str = cmd;
    str.erase(std::remove(str.begin(), str.end(), 'L'), str.end());
    str.erase(std::remove(str.begin(), str.end(), 'R'), str.end());
    str.erase(std::remove(str.begin(), str.end(), 'M'), str.end());
    if(str.empty())
        return true;
    else
        return false;
}


/**
 * @brief rtrim trim string from end. Remove spaces.
 * @param s
 */
inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

/**
 * @brief ltrim trim the string from start.Remove spaces.
 * @param s
 */
inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

/**
 * @brief trim removes spaces from the string begin and end
 * @param s input string
 */
inline std::string trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
    return s;
}

}//end of namespace nasa

#endif // COMMON_H
