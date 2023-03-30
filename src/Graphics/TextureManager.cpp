#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include "tinyxml.h"
#include "SoundManager.h"
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
bool TextureManager::ParseTexture(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout<<"Failed to load: "<<source<<std::endl;
        return false;
    }
    TiXmlElement* root=xml.RootElement();
     for(TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if(e->Value()==std::string("texture")){
            std::string id=e->Attribute("id");
            std::string src=e->Attribute("source");
            Load(id,src);
        }
    }
    return true;
}
bool TextureManager::ParseSound(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout<<"Failed to load:"<<source<<std::endl;
        return false;
    }
    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if(e->Value()==std::string("effect")){
            SoundManager::GetInstance()->LoadEffect(e->Attribute("id"),e->Attribute("source"));
            continue;
        }
        if(e->Value()==std::string("music")){
            SoundManager::GetInstance()->LoadMusic(e->Attribute("id"),e->Attribute("source"));
            continue;
        }
    }
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
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
    Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x-cam.X, y-cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    SDL_Rect dstRect = {x-cam.X, y-cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {x-cam.X, y-cam.Y, tilesize, tilesize};
    SDL_Rect srcRect = {tilesize*frame, tilesize*row, tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}
void TextureManager::QueryTexture(std::string id, int* out_w, int* out_h)
{
    SDL_QueryTexture(m_TextureMap[id],NULL,NULL,out_w,out_h);
}


