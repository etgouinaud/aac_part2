// Class POINT
#ifndef __Point__
#define __Point__

#include "Point.hpp"

/*
Constructors
*/
Point::Point(): x(0), y(0){

}

Point::Point(int x, int y): x(x), y(y){

}

/*
Operators
*/
std::ostream& operator <<(std::ostream & os, const Point & p){
    os << p.getX() << "," << p.getY() << " ";
    return os;
}

bool operator ==(const Point &p1, const Point &p2){
    return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}

bool operator !=(const Point &p1, const Point &p2){
    return (p1.getX() != p2.getX()) || (p1.getY() != p2.getY());
}


#endif