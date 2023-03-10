#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>

class Vector2D
{
    public:
        int X,Y;
    public:
        Vector2D(int x=0, int y=0):X(x), Y(y){}
    public:
        inline  Vector2D operator+ (const Vector2D &v2) const {return Vector2D(X+v2.X,Y+v2.Y);}
        inline  Vector2D operator- (const Vector2D &v2) const {return Vector2D(X-v2.X,Y-v2.Y);}
        inline  Vector2D operator* (const int scalar) const {return Vector2D(X*scalar,Y*scalar);}
        inline  Vector2D operator/ (const int div) const {return Vector2D(X/div,Y/div);}
        void Log(std::string msg=""){std::cout<<msg<<"(X Y)=("<<X<<" "<<Y<< ")"<<std::endl;}

};

#endif // VECTOR2D_H
