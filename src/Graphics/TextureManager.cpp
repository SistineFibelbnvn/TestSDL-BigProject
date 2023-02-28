#include "TextureManager.h"
#include "Engine.h"

TextureManager* TextureManager::s_Instance=nullptr;
bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* Surface=IMG_Load(filename.c_str());
    if(Surface==nullptr){
        SDL_Log("Failed to load Texture: %s,%s",filename.c_str(),SDL_GetError());
        return false;
    }
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(),Surface);
    if(Texture==nullptr){
        SDL_Log("Failed to create Texture from surface: %s",SDL_GetError());
        return false;
    }
    m_TextureMap[id]=Texture;
    return true;
}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);

}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin();it !=m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
    SDL_Log("Texture map cleaned");
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = {x, y, tilesize, tilesize};
    SDL_Rect srcRect = {tilesize*frame, tilesize*(row-1), tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

