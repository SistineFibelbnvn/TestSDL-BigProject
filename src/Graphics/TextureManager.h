#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <string>
#include "SDL.h"
#include <map>
#include "SDL_ttf.h"
class TextureManager
{
    public:

        static TextureManager* GetInstance(){return s_Instance = (s_Instance!=nullptr)? s_Instance : new TextureManager();}
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        bool Load(std::string id, std::string filename);
        bool ParseTexture(std::string source);
        bool ParseSound(std::string source);
        void QueryTexture(std::string id, int* out_w, int* out_h);
        void Drop(std::string id);
        void Clean();
        void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height,int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);


    private:
        TextureManager(){}
        std::map<std::string, SDL_Texture*>m_TextureMap;
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
