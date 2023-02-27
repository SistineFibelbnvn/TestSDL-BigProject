#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
struct Properties
{
    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE){
            X=x;
            Y=y;
            Flip=Flip;
            Width=width;
            Height=height;
            TextureID=textureID;
        }
    public:
        float X,Y;
        int Width, Height;
        std::string TextureID;
        SDL_RendererFlip Flip;
};
class GameObject : public IObject
{
    public:
        GameObject(Properties* props): m_TextureID(props->TextureID),
            m_Width(props->Width),m_Height(props->Height),m_Flip(props->Flip){
            m_Transform=new Transform(props->X,props->Y);}

        virtual void Draw()=0;
        virtual void Update(float dt)=0;
        virtual void Clean()=0;

    protected:
        std::string m_TextureID;
        int m_Width, m_Height;
        SDL_RendererFlip m_Flip;
        Transform* m_Transform;

};

#endif // GAMEOBJECT_H
