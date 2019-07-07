#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>

class Point {
    int x, y;
    int getX();
    int getY();

  public:
    Point(int, int);
    friend std::istream& operator>>(std::istream&, Point&);
    friend std::ostream& operator<<(std::ostream&, Point&);
};

#endif