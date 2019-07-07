#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>

class Point {
    int x, y;

  public:
    Point(int, int);
    int getX();
    int getY();
    friend std::istream& operator>>(std::istream&, Point&);
    friend std::ostream& operator<<(std::ostream&, Point&);
};

#endif