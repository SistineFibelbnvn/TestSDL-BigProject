#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "Engine.h"
#include "Timer.h"

int main(int argc, char* args[])
{
    Engine::GetInstance()->Init();
    while(Engine::GetInstance()->IsRunning()){

        Engine::GetInstance()->Update();
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();

	return 0;
}
