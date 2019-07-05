#ifndef __POINT_H__
#define __POINT_H__
#include <iostream>

class Point {
	int x, y;
  public:
		Point(int,int);
		friend std::istream operator>>(std::istream, Point&);//should we use friend here
		friend std::istream operator<<(std::ostream, Point&);
};

#endif