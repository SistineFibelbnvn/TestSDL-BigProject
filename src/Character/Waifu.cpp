#include "Waifu.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"

Waifu::Waifu(Properties* props):Character(props)
{
    m_Animation=new Animation();
    m_Animation->SetProps(m_TextureID,1,4,100);
    m_Rigidbody=new Rigidbody();

}

void Waifu::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
}

void Waifu::Update(float dt)
{
    m_Animation->SetProps("1",1,4,100);
    m_Rigidbody->UnSetForce();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_Rigidbody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps("3",1,4,100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_Rigidbody->ApplyForceX(5*FORWARD);
        m_Animation->SetProps("2",1,4,100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        m_Rigidbody->ApplyForceY(5*UPWARD);
        m_Animation->SetProps("4",1,4,100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_Rigidbody->ApplyForceY(5*DOWNWARD);
        m_Animation->SetProps("1",1,4,100);
    }
    m_Transform->TranslateX(m_Rigidbody->Position().X);
    m_Transform->TranslateY(m_Rigidbody->Position().Y);
    m_Rigidbody->Update(0.8);
    m_Animation->Update();
}

void Waifu::Clean()
{
    TextureManager::GetInstance()->Clean();
}


