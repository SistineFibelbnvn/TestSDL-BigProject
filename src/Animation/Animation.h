#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include <string>
class Animation
{
    public:
        Animation(){}
        void Update();
        void Draw(int x, int y,  SDL_RendererFlip flip);
        void SetProps(std::string textureID,float width,float height, int spritRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    public:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        float m_Width,m_Height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
