#include "Animation.h"
#include "TextureManager.h"
void Animation::Update()
{
    m_SpriteFrame=(SDL_GetTicks()/m_AnimSpeed)%m_FrameCount;
}
void Animation::SetProps(std::string textureID, int spritRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID=textureID;
    m_SpriteRow=spritRow;
    m_FrameCount=frameCount;
    m_AnimSpeed=animSpeed;
    m_Flip=flip;
}
void Animation::Draw(int x, int y, int spritWidth, int spritHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID,x,y,spritWidth,spritHeight,m_SpriteRow,m_SpriteFrame,m_Flip);
}



