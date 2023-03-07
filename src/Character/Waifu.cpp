#include "Waifu.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Collision.h"
#include "Collider.h"
Collision* Collision::s_Instance=nullptr;
Waifu::Waifu(Properties* props):Character(props)
{
    m_IsJumping=false;
    m_IsGrounded=false;
    m_IsRunning=false;
    m_IsCrouching=false;
    m_IsFalling=false;
    m_IsAttacking=false;

    m_JumpTime=JUMP_TIME;
    m_JumpForce=JUMP_FORCE;
    m_AttackTime=ATTACK_TIME;

    m_Collider=new Collider();
    m_Collider->SetBuffer(0,0,30,30);
    m_Animation=new Animation();
    m_Animation->SetProps(m_TextureID,1,4,100);
    m_Rigidbody=new Rigidbody();
    m_Rigidbody->SetGravity(4.0f);

}

void Waifu::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Width,m_Height);
    Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x-=cam.X;
    Box.y-=cam.Y;
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(),&Box);
}

void Waifu::Update(float dt)
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){
        Engine::GetInstance()->Quit();
    }
    m_Animation->SetProps("1",1,4,100);
    m_IsRunning=false;
    m_IsCrouching=false;
    m_Rigidbody->UnSetForce();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_Rigidbody->ApplyForceX(5*BACKWARD);
        m_Animation->SetProps("3",1,4,100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_Rigidbody->ApplyForceX(5*FORWARD);
        m_Animation->SetProps("2",1,4,100);
    }
    /*if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        m_Rigidbody->ApplyForceY(5*UPWARD);
        m_Animation->SetProps("4",1,4,100);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_Rigidbody->ApplyForceY(5*DOWNWARD);
        m_Animation->SetProps("1",1,4,100);
    }*/
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&m_IsGrounded){
        m_IsJumping=true;
        m_IsGrounded=false;
        m_Rigidbody->ApplyForceY(UPWARD*m_JumpForce);
    }
     if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&m_IsJumping&&m_JumpTime>0){
        m_JumpTime-=dt;
        m_Rigidbody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{m_IsJumping=false;
         m_JumpTime=JUMP_TIME;}
    m_Rigidbody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->Position().X;
    m_Collider->Set(m_Transform->X,m_Transform->Y,96,96);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}

    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->Position().Y;
    m_Collider->Set(m_Transform->X,m_Transform->Y,96,96);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_IsGrounded=true;m_Transform->Y=m_LastSafePosition.Y;}
    else {m_IsGrounded=false;}
    m_Origin->X=m_Transform->X+m_Width/2;
    m_Origin->Y=m_Transform->Y+m_Height/2;
    m_Animation->Update();

}

void Waifu::State()
{
    m_Animation->SetProps("1",1,4,100);
    /*if(m_IsRunning) m_Animation->SetProps()
    if(m_IsJumping) m_Animation->SetProps()
    if(m_IsFalling) m_Animation->SetProps()
    if(m_IsCrouching) m_Animation->SetProps()
    if(m_IsAttacking) m_Animation->SetProps()*/
}

void Waifu::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}


