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
    m_IsDashAttacking=false;
    m_IsDashing=false;
    m_IsFalling=false;
    m_IsHurting=false;
    m_IsSliding=false;
    m_JumpTime=JUMP_TIME;
    m_JumpForce=JUMP_FORCE;

    m_Collider=new Collider();
    m_Collider->SetBuffer(-30,-20,0,-20);
    m_Animation=new Animation();
    m_Rigidbody=new Rigidbody();

}

void Waifu::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Flip);
    /*Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x-=cam.X;
    Box.y-=cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(),&Box);*/
}

void Waifu::Update(float dt)
{
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){
        Engine::GetInstance()->Quit();
    }
    m_IsRunning=false;
    m_IsCrouching=false;
    m_IsAttacking=false;
    m_IsDashAttacking=false;
    m_IsDashing=false;
    m_IsSliding=false;
    m_Rigidbody->UnSetForce();
    Vector2D cam=Camera::GetInstance()->GetPosition();

    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==BACKWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(cam.X-m_Transform->X);
        else{
        m_Rigidbody->ApplyForceX(3*BACKWARD);}
        m_Flip=SDL_FLIP_HORIZONTAL;
        m_IsRunning=true;
    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==FORWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(3*FORWARD+cam.X-m_Transform->X);
        if(m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Rigidbody->ApplyForceX(0);
        else{
        m_Rigidbody->ApplyForceX(3*FORWARD);}
        m_Flip=SDL_FLIP_NONE;
        m_IsRunning=true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_IsAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_IsDashAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
        m_IsCrouching=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(2*FORWARD);
        else  m_Rigidbody->ApplyForceX(2*BACKWARD);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_IsDashing=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_L)){
        m_IsSliding=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(3*FORWARD);
        else  m_Rigidbody->ApplyForceX(3*BACKWARD);
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
    if(!m_IsGrounded && m_Rigidbody->Veclocity().Y>0) m_IsFalling=true;
    else m_IsFalling=false;

    m_Rigidbody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->Position().X;
    if(m_Transform->X<=cam.X) m_Collider->Set(cam.X,m_Transform->Y,60,60);
    if (m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Collider->Set(cam.X+Engine::GetInstance()->GetScreenWidth()-55,m_Transform->Y,96,96);
    else m_Collider->Set(m_Transform->X,m_Transform->Y,60,60);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}

    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->Position().Y;
    if(m_Transform->X<=cam.X) m_Collider->Set(cam.X,m_Transform->Y,60,60);
    if (m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Collider->Set(cam.X+Engine::GetInstance()->GetScreenWidth()-55,m_Transform->Y,96,96);
    else m_Collider->Set(m_Transform->X,m_Transform->Y,60,60);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_IsGrounded=true;m_Transform->Y=m_LastSafePosition.Y;}
    else m_IsGrounded=false;
    State();
    m_Origin->X=m_Transform->X+m_Width/2;
    m_Origin->Y=m_Transform->Y+m_Height/2;
    m_Animation->Update();

}

void Waifu::State()
{
    m_Animation->SetProps("Idle",768/6,88,1,6,175);
    if(m_IsRunning) m_Animation->SetProps("Run",1024/8,88,1,8,125);
    if(m_IsJumping) m_Animation->SetProps("Jump",384/3,88,1,3,125);
    if(m_IsAttacking) m_Animation->SetProps("Attack",1536/12,88,1,12,100);
    if(m_IsDashAttacking) m_Animation->SetProps("DashAttack",1380/10,88,1,10,100);
    if(m_IsDashing) m_Animation->SetProps("Dash",966/7,88,1,7,150);
    if(m_IsFalling) m_Animation->SetProps("Fall",384/3,88,1,3,150);
    if(m_IsHurting) m_Animation->SetProps("Hurt",512/4,88,1,4,100);
    if(m_IsSliding) m_Animation->SetProps("Slide",690/5,88,1,5,100);
    if(m_IsCrouching) m_Animation->SetProps("Crouch",828/6,88,1,6,100);


}

void Waifu::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}


