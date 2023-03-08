#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Vector2D.h"

class Transform
{
    public:
        int X,Y;
    public:
        Transform(int x=0, int y=0): X(x),Y(y){}
        void Log(std::string msg=""){std::cout<<msg<<"(X Y)=("<<X<<" "<<Y<< ")"<<std::endl;}
    public:
        inline void TranslateX(int x){X+=x;}
        inline void TranslateY(int y){Y+=y;}
        inline void Translate(Vector2D v){X+=v.X;Y+=v.Y;}
};

#endif // TRANSFORM_H
