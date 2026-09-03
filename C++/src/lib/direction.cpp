/*
 * File: direction.cpp
 * -------------------
 * This file implements the direction.h interface.
 */

#include <string>
#include "direction.h"

using namespace std;

/*
 * Implementation notes: leftFrom, rightFrom, opposite
 * ---------------------------------------------------
 * 通过对枚举值做模 4 运算在四个方向之间循环。
 */

Direction leftFrom(Direction dir) {
   return Direction((dir + 3) % 4);
}

Direction rightFrom(Direction dir) {
   return Direction((dir + 1) % 4);
}

Direction opposite(Direction dir) {
   return Direction((dir + 2) % 4);
}

/*
 * Implementation notes: directionToString
 * ----------------------------------------
 * 把方向枚举转换为对应的名称字符串。
 */

string directionToString(Direction dir) {
   switch (dir) {
    case NORTH: return "NORTH";
    case EAST:  return "EAST";
    case SOUTH: return "SOUTH";
    case WEST:  return "WEST";
    default:    return "???";
   }
}

/*
 * Implementation notes: << and >> operators
 * ------------------------------------------
 * 让 Direction 值可以直接用流输入输出。
 */

ostream & operator<<(ostream & os, const Direction & dir) {
   return os << directionToString(dir);
}

istream & operator>>(istream & is, Direction & dir) {
   string word;
   is >> word;
   if (word == "NORTH") dir = NORTH;
   else if (word == "EAST") dir = EAST;
   else if (word == "SOUTH") dir = SOUTH;
   else if (word == "WEST") dir = WEST;
   else is.setstate(ios_base::failbit);
   return is;
}

/*
 * Implementation notes: ++ operator
 * ---------------------------------
 * 后缀 ++ 让方向按 NORTH -> EAST -> SOUTH -> WEST 递增。
 */

Direction operator++(Direction & dir, int) {
   Direction old = dir;
   dir = Direction((dir + 1) % 4);
   return old;
}
