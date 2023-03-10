#ifndef CAMERA_H
#define CAMERA_H
#include "Point.h"
#include "SDL.h"
#include"Vector2D.h"
#include "Engine.h"

class Camera
{
    public:

        static Camera* GetInstance(){return s_Instance = (s_Instance!=nullptr)? s_Instance : new Camera();}
        inline SDL_Rect GetViewBox(){return m_Viewbox;}
        inline Vector2D GetPosition(){return m_Position;}
        inline void SetTarget(Point* target){m_Target=target;}
        void Update(float dt);

    private:

        Camera(){m_Viewbox = {0,0,Engine::GetInstance()->GetScreenWidth(),Engine::GetInstance()->GetScreenHeight()};}
        Point* m_Target;
        SDL_Rect m_Viewbox;
        Vector2D m_Position;
        float SpeedCamera=1.00;
        static Camera* s_Instance;
};

#endif // CAMERA_H
