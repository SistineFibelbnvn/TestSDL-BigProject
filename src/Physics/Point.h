#ifndef POINT_H
#define POINT_H
#include<string>
#include<iostream>
class Point
{
    public:
        float X,Y;
    public:
        Point(float x=0, float y=0):X(x), Y(y){}
    public:
        inline  Point operator+ (const Point &p2) const {return Point(X+p2.X,Y+p2.Y);}
        inline friend Point operator+= (Point &p1, const Point &p2) {p1.X+=p2.X;p1.Y+=p2.Y;return p1;}
        inline  Point operator- (const Point &p2) const {return Point(X-p2.X,Y-p2.Y);}
        inline friend Point operator-= (Point &p1, const Point &p2) {p1.X-=p2.X;p1.Y-=p2.Y;return p1;}
        inline  Point operator* (const float scalar) const {return Point(X*scalar,Y*scalar);}
        inline  Point operator/ (const float div) const {return Point(X/div,Y/div);}
};

#endif // POINT_H
