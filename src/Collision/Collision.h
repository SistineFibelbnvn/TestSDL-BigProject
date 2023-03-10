#include "SDL.h"
#include "Vector2D.h"
#include "GameMap.h"
#include "TileLayer.h"
#include <vector>
#ifndef COLLISION_H
#define COLLISION_H


class Collision
{
    public:
        static Collision* GetInstance(){return s_Instance = (s_Instance!=nullptr)? s_Instance : new Collision();}
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        bool MapCollision(SDL_Rect a);


    private:
        Collision();
        Tilemap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
        static Collision* s_Instance;
};

#endif // COLLISION_H
