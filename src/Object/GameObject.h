#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include "Point.h"
#include "Animation.h"
struct Properties
{
    public:
        Properties(std::string textureID, float x, float y, SDL_RendererFlip flip=SDL_FLIP_NONE){
            X=x;
            Y=y;
            Flip=Flip;
            TextureID=textureID;
        }
    public:
        float m_Width=80,m_Height=80;
        float X,Y;
        std::string TextureID;
        SDL_RendererFlip Flip;
};
class GameObject : public IObject
{
public:
        GameObject(Properties* props): m_TextureID(props->TextureID),m_Flip(props->Flip){
            m_Transform=new Transform(props->X,props->Y);
            float px=props->X+props->m_Width/2;
            float py=props->Y+props->m_Height/2;
            m_Origin=new Point(px,py);
        }
        inline Point* GetOrigin(){return m_Origin;}
        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;

    public:
        Point* m_Origin;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
        Transform* m_Transform;
        float m_Width=80,m_Height=80;

};

#endif // GAMEOBJECT_H
