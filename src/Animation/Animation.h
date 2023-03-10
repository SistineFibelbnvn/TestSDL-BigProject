#ifndef ANIMATION_H
#define ANIMATION_H
#include "SDL.h"
#include <string>
class Animation
{
    public:
        Animation(){}
        void Update();
        void Draw(int x, int y,int spritWidth, int spritHeight);
        void SetProps(std::string textureID, int spritRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
