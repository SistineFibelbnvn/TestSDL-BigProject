#include "Animation.h"
#include "TextureManager.h"
void Animation::Update()
{
    m_SpriteFrame=(SDL_GetTicks()/m_AnimSpeed)%m_FrameCount;
}
void Animation::SetProps(std::string textureID,float width , float height, int spritRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID=textureID;
    m_SpriteRow=spritRow;
    m_FrameCount=frameCount;
    m_AnimSpeed=animSpeed;
    m_Flip=flip;
    m_Width=width;
    m_Height=height;
}
void Animation::Draw(int x, int y,SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID,x,y,m_Width,m_Height,m_SpriteRow,m_SpriteFrame,flip);
}



