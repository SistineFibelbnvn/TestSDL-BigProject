#include <iostream>
#include "Engine.h"
#include "TextureManager.h"
#include "Waifu.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include "Camera.h"
#include "Boss1.h"
#include "Boss2.h"
Engine* Engine::s_Instance = nullptr;
Waifu* player=nullptr;
Boss1* boss1=nullptr;
Boss2* boss2=nullptr;
bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0&&IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)!=0){
        SDL_Log("Failed to initialize SDL: %s",SDL_GetError());
        return false;
    }
    m_Window=SDL_CreateWindow("Sistinefibel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,GetScreenWidth(),GetScreenHeight(),0);
    if(m_Window==nullptr){
        SDL_Log("Failed to create Window: %s",SDL_GetError());
        return false;
    }
    m_Renderer=SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer==nullptr){
        SDL_Log("Failed to create Renderer: %s",SDL_GetError());
        return false;
    }
    if(!MapParser::GetInstance()->Load()){
        std::cout<<"Failed to load map"<<std::endl;
    }
    m_LevelMap=MapParser::GetInstance()->GetMaps("MAP");
    TextureManager::GetInstance()->ParseTexture("images/Textures.tml");
    TextureManager::GetInstance()->ParseSound("images/Sounds.tml");
    boss1=new Boss1(new Properties("Ice",5800,2*GetScreenHeight()-300));
    boss2=new Boss2(new Properties("Fire",GetScreenWidth()/2,0));
    player=new Waifu(new Properties("SistineFibel",40,5800)); //40 5800 //3000 1600
    m_GameObject.push_back(player);
    m_GameObject.push_back(boss1);
    m_GameObject.push_back(boss2);

    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_IsRunning=true;
}

void Engine::Clean()
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
    float dt=Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    for(unsigned int i=0;i!=m_GameObject.size();i++){m_GameObject[i]->Update(dt);}
    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer,230, 230, 255, 130);
    SDL_RenderClear(m_Renderer);
    TextureManager::GetInstance()->Draw("Ice",GetScreenWidth()*0,1*GetScreenHeight(),6400,GetScreenHeight());
    TextureManager::GetInstance()->Draw("Sky",GetScreenWidth()*0,2*GetScreenHeight(),6400,GetScreenHeight());
    TextureManager::GetInstance()->Draw("SatanBg",0,0,6400,GetScreenHeight());
    TextureManager::GetInstance()->Draw("Tutorial",0,5200,1280,720);
    TextureManager::GetInstance()->Draw("D",50,5400,1280,720);
    TextureManager::GetInstance()->Draw("A",1280,5100,1280,720);
    TextureManager::GetInstance()->Draw("P",100,5000,1280,720);
    TextureManager::GetInstance()->Draw("J",1280*2+100,6200,1280,720);
    TextureManager::GetInstance()->Draw("K",1280*3,6200,1280,720);
    TextureManager::GetInstance()->Draw("L",1280*4+100,6150,1280,720);
    TextureManager::GetInstance()->Draw("Space",1280*2,5200,1280,720);
    TextureManager::GetInstance()->Draw("Go",1280,6400,1280,720);
    TextureManager::GetInstance()->Draw("Win",1280*4,5200,1280,720);
    TextureManager::GetInstance()->Draw("PS",1280*3,5200,1280,720);
    TextureManager::GetInstance()->Draw("Esc",40,6050,1280,720);
    TextureManager::GetInstance()->Draw("Skill",1280*2,6000,1280,720);
    TextureManager::GetInstance()->Draw("Skill",1280*3,6000,1280,720);
    TextureManager::GetInstance()->Draw("Skill",1280*4,6000,1280,720);
    for(int i=0;i<=3;i++){
    TextureManager::GetInstance()->Draw("Castle",2000*i,3*GetScreenHeight(),2000,GetScreenHeight());}
    m_LevelMap->Render();
    for(unsigned int i=0;i!=m_GameObject.size();i++){m_GameObject[i]->Draw();}
    SDL_RenderPresent(m_Renderer);

}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
int Engine::GetScreenWidth()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return DM.w;
}
int Engine::GetScreenHeight()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    return DM.h;
}


