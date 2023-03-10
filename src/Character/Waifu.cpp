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
    m_AttackTime1=ATTACK_TIME1;
    m_AttackTime2=ATTACK_TIME2;

    m_Collider=new Collider();
    m_Collider->SetBuffer(0,0,0,0);
    m_Animation=new Animation();
    m_Animation->SetProps("Idle",1024/6,109,1,6,100);
    m_Rigidbody=new Rigidbody();

}

void Waifu::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Flip);
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
    m_Animation->SetProps("Idle",1024/6,109,1,8,100);
    m_IsRunning=false;
    m_IsCrouching=false;
    m_Rigidbody->UnSetForce();
    Vector2D cam=Camera::GetInstance()->GetPosition();

    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==BACKWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(cam.X-m_Transform->X);
        else{
        m_Rigidbody->ApplyForceX(5*BACKWARD);}
        m_Flip=SDL_FLIP_HORIZONTAL;
        m_IsRunning= true;
    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==FORWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(2*FORWARD+cam.X-m_Transform->X);
        if(m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Rigidbody->ApplyForceX(0);
        else{
        m_Rigidbody->ApplyForceX(5*FORWARD);}
        m_Flip=SDL_FLIP_NONE;
        m_IsRunning=true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_IsAttacking=true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        m_IsCrouching=true;}

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_IsHolding=true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_IsPower=true;
    }
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
         m_JumpTime=JUMP_TIME;
        }

    if(m_Rigidbody->Veclocity().Y>0&&!m_IsGrounded) m_IsFalling=true;
    else m_IsFalling=false;
    if(m_IsAttacking&&m_AttackTime1>0){
        m_AttackTime1-=dt;
    }
    else{
        m_IsAttacking=false;
        m_AttackTime1=ATTACK_TIME1;
    }
    if(m_IsPower&&m_AttackTime2>0){
        m_AttackTime2-=dt;
    }
    else{
        m_IsPower=false;
        m_AttackTime2=ATTACK_TIME2;
    }

    m_Rigidbody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->Position().X;
    if(m_Transform->X<=cam.X) m_Collider->Set(cam.X,m_Transform->Y,96,96);
    if (m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Collider->Set(cam.X+Engine::GetInstance()->GetScreenWidth()-55,m_Transform->Y,96,96);
    else m_Collider->Set(m_Transform->X,m_Transform->Y,96,96);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}

    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->Position().Y;
    if(m_Transform->X<=cam.X) m_Collider->Set(cam.X,m_Transform->Y,96,96);
    if (m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Collider->Set(cam.X+Engine::GetInstance()->GetScreenWidth()-55,m_Transform->Y,96,96);
    else m_Collider->Set(m_Transform->X,m_Transform->Y,96,96);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_IsGrounded=true;m_Transform->Y=m_LastSafePosition.Y;}
    else m_IsGrounded=false;
    State();
    m_Origin->X=m_Transform->X+m_Width/2;
    m_Origin->Y=m_Transform->Y+m_Height/2;
    m_Animation->Update();

}

void Waifu::State()
{
    m_Animation->SetProps("Idle",1024/6,109,1,6,100);
    if(m_IsHolding) m_Animation->SetProps("Idle",1024/6,109,1,6,100);
    if(m_IsRunning) m_Animation->SetProps("Run",1024/6,109,1,6,100);
    if(m_IsJumping) m_Animation->SetProps("Jump",1024/6,109,1,6,100);
    if(m_IsFalling) m_Animation->SetProps("Fall",1024/6,109,1,6,100);
    if(m_IsCrouching) m_Animation->SetProps("Dash",1024/6,109,1,6,100);
    if(m_IsAttacking) m_Animation->SetProps("Attack",1024/6,109,1,6,100);
    if(m_IsPower) m_Animation->SetProps("Power",1040/6,109,1,6,100);
}

void Waifu::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}


