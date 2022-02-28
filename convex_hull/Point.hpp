// Class POINT
#include <iostream>

class Point{
    private:
        /*
        Attributes
        */
        int x;
        int y;

    public:
        /*
        Constructors
        */
        Point();
        Point(int x, int y);

        /*
        Getters
        */
        inline int getX() const {return this->x;};
        inline int getY() const {return this->y;};

        /*
        Operators
        */
        friend std::ostream& operator <<(std::ostream & os, const Point & p);
        friend bool operator ==(const Point &p1, const Point &p2);
        friend bool operator !=(const Point &p1, const Point &p2);
};