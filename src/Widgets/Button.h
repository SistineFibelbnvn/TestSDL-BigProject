#ifndef BUTTON_H
#define BUTTON_H
#include "SDL.h"
#include <string>
#include <vector>
#include "Input.h"
#include "GameObject.h"
#include "TextureManager.h"
using TextureIdlist = std::vector<std::string>;
enum ButtonState {NORMAL=0;HOVER=1;PRESSED=2};
class Button : public GameObject
{
    public:
        Button(int x,int y,void(*callback)(),TextureIdlist textrIDs) : GameObject(new Transform()){
            m_Transform->X=x;
            m_Transform->Y=y;
            m_Callback=callback;
            m_TextrIDs=textrIDs;
            m_Transform->TextureID=m_TextrIDs[NORMAL];
            TextureManager::GetInstance()->QueryTexture(m_Transform->TextureID)
        }
    private:
        SDL_Rect m_Shape;
        bool m_IsRelease;
        void (*callback)();
        TextureIdlist m_TextrIDs;
};

#endif // BUTTON_H
