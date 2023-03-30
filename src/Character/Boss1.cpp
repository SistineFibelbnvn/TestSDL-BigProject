#include "Boss1.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Collision.h"
#include "Collider.h"
Boss1::Boss1(Properties* props): Character(props)
{
    m_IsWalking=false;
    m_IsAttacking=false;
    m_IsDeath=false;
    m_Collider=new Collider();
    m_Animation=new Animation();
    m_Rigidbody=new Rigidbody();
    m_Collider->SetBuffer(-110,-20,0,-20);
}

void Boss1::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Flip);
    /*Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x-=cam.X;
    Box.y-=cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(),&Box);*/
}

void Boss1::Update(float dt)
{
    m_IsWalking=false;
    m_IsAttacking=false;
    m_IsDeath=false;
    m_Rigidbody->UnSetForce();
    Vector2D cam=Camera::GetInstance()->GetPosition();
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==BACKWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(cam.X-m_Transform->X);
        else{
        m_Rigidbody->ApplyForceX(3*BACKWARD);}
        m_Flip=SDL_FLIP_NONE;
        m_IsWalking=true;
    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==FORWARD){
        if(m_Transform->X<=cam.X) m_Rigidbody->ApplyForceX(3*FORWARD+cam.X-m_Transform->X);
        if(m_Transform->X>=cam.X+Engine::GetInstance()->GetScreenWidth()-50) m_Rigidbody->ApplyForceX(0);
        else{
        m_Rigidbody->ApplyForceX(3*FORWARD);}
        m_Flip=SDL_FLIP_HORIZONTAL;
        m_IsWalking=true;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
        m_IsAttacking=true;
        if(m_Flip==SDL_FLIP_HORIZONTAL) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }
    m_Rigidbody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->m_Position.X;
    m_Collider->Set(m_Transform->X,m_Transform->Y,170,170);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}

    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->m_Position.Y;
    m_Collider->Set(m_Transform->X,m_Transform->Y,170,170);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->Y=m_LastSafePosition.Y;}
    State();
    m_Animation->Update();
}
void Boss1::State()
{
    m_Animation->SetProps("B1Idle",1152/3,256,1,6,150);
    if(m_IsDeath) m_Animation->SetProps("B1Death",6144/16,256,1,16,250);
    if(m_IsAttacking) m_Animation->SetProps("B1Attack",5376/14,256,1,14,125);
    //m_Animation->SetProps("B1Hurt",2688/7,256,1,7,100);
    if(m_IsWalking) m_Animation->SetProps("B1Walk",3840/10,256,1,10,150);
}

void Boss1::Clean()
{

}
