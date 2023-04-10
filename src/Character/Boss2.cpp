#include "Boss2.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Collision.h"
#include "Collider.h"
Boss2::Boss2(Properties* props): Character(props)
{
    m_IsWalking=false;
    m_IsCleaving=false;
    m_IsDeath1=false;
    m_IsDeath1=false;
    m_IsDeath2=false;
    m_Collider=new Collider();
    m_Collider->SetBuffer(-180,-20,60,-20);
    m_Animation=new Animation();
    m_Rigidbody=new Rigidbody();
    m_Flip=SDL_FLIP_NONE;
}

void Boss2::Draw()
{
    m_Animation->Draw(m_Transform->X,m_Transform->Y,m_Flip);
    /*Vector2D cam=Camera::GetInstance()->GetPosition();
    SDL_Rect Box = m_Collider->Get();
    Box.x-=cam.X;
    Box.y-=cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(),&Box);*/
}

void Boss2::Update(float dt)
{
    m_Rigidbody->UnSetForce();
    m_IsWalking=false;
    m_IsCleaving=false;
    m_IsDeath1=false;
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
        m_IsCleaving=true;
        if(m_Flip==SDL_FLIP_HORIZONTAL) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }
    m_Rigidbody->Update(dt);
    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->m_Position.X;
    m_Collider->Set(m_Transform->X,m_Transform->Y,270,270);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}

    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->m_Position.Y;
    m_Collider->Set(m_Transform->X,m_Transform->Y,270,270);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->Y=m_LastSafePosition.Y;}
    State();
    m_Animation->Update();
}
void Boss2::State()
{
    m_Animation->SetProps("B2Idle",1728/3,320,1,6,150);

    if(m_IsDeath1) m_Animation->SetProps("B2Death1",8064/14,320,1,14,200);
    //if(m_IsDeath2) m_Animation->SetProps("B2Death2",4608/8,320,1,8,200);
    //m_Animation->SetProps("B2Hurt",2880/5,320,1,5,100);
    if(m_IsWalking) m_Animation->SetProps("B2Walk",6912/12,320,1,12,150);
    if(m_IsCleaving) m_Animation->SetProps("B2Cleave",8064/14,320,1,14,125);
}

void Boss2::Clean()
{

}
