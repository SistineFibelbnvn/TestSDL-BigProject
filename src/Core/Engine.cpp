#include <iostream>
#include "Engine.h"
#include "TextureManager.h"
#include "Waifu.h"
#include "Input.h"
#include "Timer.h"
Engine* Engine::s_Instance = nullptr;
Waifu* player=nullptr;
bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0&&IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)!=0){
        SDL_Log("Failed to initialize SDL: %s",SDL_GetError());
        return false;
    }
    m_Window=SDL_CreateWindow("Sistinefibel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREN_WIDTH,SCREN_HEIGHT,0);
    if(m_Window==nullptr){
        SDL_Log("Failed to create Window: %s",SDL_GetError());
        return false;
    }
    m_Renderer=SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer==nullptr){
        SDL_Log("Failed to create Renderer: %s",SDL_GetError());
        return false;
    }
    TextureManager::GetInstance()->Load("2","images/Nurse2.png");
    TextureManager::GetInstance()->Load("1","images/Nurse1.png");
    TextureManager::GetInstance()->Load("3","images/Nurse3.png");
    TextureManager::GetInstance()->Load("4","images/Nurse4.png");
    player=new Waifu(new Properties("1",100,200,270/4,75));
    return m_IsRunning=true;
}

bool Engine::Clean()
{
    SDL_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TextureManager::GetInstance()->Clean();
}

void Engine::Quit()
{
    m_IsRunning=false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    player->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer,153, 102, 204, 255);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("bg",100,100,1254,600);
    player->Draw();
    SDL_RenderPresent(m_Renderer);

}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
