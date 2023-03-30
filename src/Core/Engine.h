#ifndef ENGINE_H
#define ENGINE_H
#include "SDL.h"
#include "SDL_image.h"
#include "GameMap.h"
#include"GameObject.h"
class Engine
{
    public:
        static Engine* GetInstance(){return s_Instance = (s_Instance!=nullptr)? s_Instance : new Engine();}
        bool Init();
        void Clean();
        void Quit();
        void Update();
        void Render();
        void Events();
        int GetScreenWidth();
        int GetScreenHeight();
        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}
        inline GameMap* GetMap(){return m_LevelMap;}
    public:
        Engine(){}
        bool m_IsRunning;
        SDL_Window* m_Window=nullptr;
        SDL_Renderer* m_Renderer=nullptr;
        GameMap* m_LevelMap;
        static Engine* s_Instance;
        std::vector<GameObject*> m_GameObject;
};

#endif // ENGINE_H
