#include "Waifu.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Camera.h"
#include "Collision.h"
#include "Collider.h"
#include "SoundManager.h"
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
    m_IsWalling=false;
    m_IsDeath=false;
    m_JumpTime=JUMP_TIME;
    m_JumpForce=JUMP_FORCE;
    m_RunSound1=RUN_SOUND;
    m_RunSound2=RUN_SOUND;
    m_AttackSound=ATTACK_SOUND;
    m_DashAttackSound=DASH_ATTACK_SOUND;
    m_Collider=new Collider();
    m_Animation=new Animation();
    m_Rigidbody=new Rigidbody();
    SoundManager::GetInstance()->PlayMusic("track");
    m_IsMusic=true;
    m_IsSoundEffect=false;
    m_Flip=SDL_FLIP_NONE;
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
    m_IsSoundEffect=false;
    m_Rigidbody->UnSetForce();
    //Vector2D cam=Camera::GetInstance()->GetPosition();
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==BACKWARD&&!m_IsWalling&&m_RunSound1<=0){
        m_Rigidbody->ApplyForceX(2*BACKWARD);
        m_Flip=SDL_FLIP_HORIZONTAL;
        m_IsRunning=true;
        if(!m_IsSoundEffect) {SoundManager::GetInstance()->PlayEffect("Running");m_IsSoundEffect=true;}
        m_RunSound1=RUN_SOUND;
    }
     if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==BACKWARD&&!m_IsWalling&&m_RunSound1>0){
        m_Rigidbody->ApplyForceX(2*BACKWARD);
        m_Flip=SDL_FLIP_HORIZONTAL;
        m_IsRunning=true;
        m_RunSound1-=1.0;

    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==FORWARD&&!m_IsWalling&&m_RunSound2<=0){
        m_Rigidbody->ApplyForceX(2*FORWARD);
        m_Flip=SDL_FLIP_NONE;
        m_IsRunning=true;
        if(!m_IsSoundEffect&&m_IsGrounded) {SoundManager::GetInstance()->PlayEffect("Running");m_IsSoundEffect=true;}
        m_RunSound2=RUN_SOUND;
    }
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL)==FORWARD&&!m_IsWalling&&m_RunSound2>0){
        m_Rigidbody->ApplyForceX(2*FORWARD);
        m_Flip=SDL_FLIP_NONE;
        m_IsRunning=true;
        m_RunSound2-=1.0;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)&&!m_IsWalling&&m_AttackSound<=0){
        m_IsAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
        if(!m_IsSoundEffect&&m_IsGrounded) {SoundManager::GetInstance()->PlayEffect("Attack");m_IsSoundEffect=true;}
        m_AttackSound=ATTACK_SOUND;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)&&!m_IsWalling&&m_AttackSound>0){
        m_IsAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
        m_AttackSound-=1.0;
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)&&!m_IsWalling&&m_DashAttackSound<=0){
        m_IsDashAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
        if(!m_IsSoundEffect) {SoundManager::GetInstance()->PlayEffect("DashAttack");m_IsSoundEffect=true;}
        m_DashAttackSound=DASH_ATTACK_SOUND;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)&&!m_IsWalling&&m_DashAttackSound>0){
        m_IsDashAttacking=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
        m_DashAttackSound-=dt;
    }
    /*if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)&&!m_IsWalling&&!m_IsJumping&&!m_IsFalling){
        m_IsCrouching=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(2.5*FORWARD);
        else  m_Rigidbody->ApplyForceX(2.5*BACKWARD);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)&&!m_IsWalling&&!m_IsJumping&&!m_IsFalling){
        m_IsDashing=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(1*FORWARD);
        else  m_Rigidbody->ApplyForceX(1*BACKWARD);
    }*/
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_L)&&!m_IsWalling&&!m_IsJumping&&!m_IsFalling){
        m_IsSliding=true;
        if(m_Flip==SDL_FLIP_NONE) m_Rigidbody->ApplyForceX(2.5*FORWARD);
        else  m_Rigidbody->ApplyForceX(2.5*BACKWARD);
        if(!m_IsSoundEffect) {SoundManager::GetInstance()->PlayEffect("Sliding");m_IsSoundEffect=true;}
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&m_IsGrounded){
        m_IsJumping=true;
        m_IsGrounded=false;
        m_Rigidbody->ApplyForceY(UPWARD*m_JumpForce);
        if(!m_IsSoundEffect) {SoundManager::GetInstance()->PlayEffect("Jumping");m_IsSoundEffect=true;}
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)&&m_IsJumping&&m_JumpTime>=0&&!m_IsGrounded){
        m_JumpTime-=1.0;
        m_Rigidbody->ApplyForceY(UPWARD*m_JumpForce);
    }

    else{m_IsJumping=false;
         m_JumpTime=JUMP_TIME;
        }
    if(m_Transform->X>=6350&&m_Transform->Y>=5800) {m_Transform->X=50;m_Transform->Y=6600;}

    if(m_Transform->X>=900&&m_Transform->X<=930&&m_Transform->Y<=3120&&m_Transform->Y>=3110) {m_Transform->X=5500;m_Transform->Y=6600;}

    if(m_Transform->X>=1760&&m_Transform->X<=1800&&m_Transform->Y<=3140&&m_Transform->Y>=3130) {m_Transform->X=4000;m_Transform->Y=6600;}

    if(m_Transform->X<=-20&&m_Transform->Y<=2600&&m_Transform->Y>=2550) {m_Transform->X=3000;m_Transform->Y=6600;}

    if(m_Transform->X>=3000&&m_Transform->X<=4000&&m_Transform->Y>=6820) {m_Transform->X=0;m_Transform->Y=2600;}

    if(m_Transform->X>=4000&&m_Transform->X<=5000&&m_Transform->Y>=6820) {m_Transform->X=1760;m_Transform->Y=3180;}

    if(m_Transform->X>=5500&&m_Transform->X<=6500&&m_Transform->Y>=6820) {m_Transform->X=900;m_Transform->Y=3150;}

    if(m_Transform->X>=1000&&m_Transform->X<=3000&&m_Transform->Y>=6820) {m_Transform->X=40;m_Transform->Y=3000;}

    if(m_Transform->X>=6350&&m_Transform->Y>=3*Engine::GetInstance()->GetScreenHeight()-200&&m_Transform->Y<=4*Engine::GetInstance()->GetScreenHeight()-200) {m_Transform->X=50;m_Transform->Y=2*Engine::GetInstance()->GetScreenHeight()-500;}

    if(m_Transform->X>=6350&&m_Transform->Y>=2*Engine::GetInstance()->GetScreenHeight()-200&&m_Transform->Y<=3*Engine::GetInstance()->GetScreenHeight()-200) {m_Transform->X=50;m_Transform->Y=1*Engine::GetInstance()->GetScreenHeight()-200;}

    if(m_Transform->Y>=2*Engine::GetInstance()->GetScreenHeight()+600&&m_Transform->Y<=3*Engine::GetInstance()->GetScreenHeight()-300)
        {m_Transform->X=50;m_Transform->Y=2*Engine::GetInstance()->GetScreenHeight()-500;}
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_P)||(m_Transform->Y>=4*Engine::GetInstance()->GetScreenHeight()-150&&m_Transform->Y<=5*Engine::GetInstance()->GetScreenHeight()-600)) {m_Transform->X=40;m_Transform->Y=3000;}


    m_LastSafePosition.X=m_Transform->X;
    m_Transform->X+=m_Rigidbody->Position().X;
    m_Collider->Set(m_Transform->X,m_Transform->Y,40,40);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_Transform->X=m_LastSafePosition.X;}
    /*if(!m_IsGrounded && m_Rigidbody->Veclocity().Y>0 &&m_Transform->X==m_LastSafePosition.X){
        m_IsWalling=true;
        m_Rigidbody->ApplyForceY(2*UPWARD);
    }
    else m_IsWalling=false;
    */
    if(!m_IsGrounded && m_Rigidbody->Veclocity().Y>0&&!m_IsWalling&&!m_IsJumping) m_IsFalling=true;
    else m_IsFalling=false;
    m_Rigidbody->Update(dt);
    m_LastSafePosition.Y=m_Transform->Y;
    m_Transform->Y+=m_Rigidbody->Position().Y;
    m_Collider->Set(m_Transform->X,m_Transform->Y,40,40);
    if(Collision::GetInstance()->MapCollision(m_Collider->Get())) {m_IsGrounded=true;m_Transform->Y=m_LastSafePosition.Y;if(m_JumpTime!=JUMP_TIME||m_IsJumping){m_IsGrounded=false;}}
    else m_IsGrounded=false;
    State();
    m_Origin->X=m_Transform->X+m_Width/2;
    m_Origin->Y=m_Transform->Y+m_Height/2;
    m_Animation->Update();

}

void Waifu::State()
{
    m_Animation->SetProps("Idle",768/6,88,1,6,175);
    if(m_IsRunning&&m_IsGrounded&&!m_IsJumping&&!m_IsFalling) {m_Animation->SetProps("Run",1024/8,88,1,8,125);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsJumping) {m_Animation->SetProps("Jump",384/3,88,1,3,150);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsAttacking) {m_Animation->SetProps("Attack",1536/12,88,1,12,100);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsDashAttacking) {m_Animation->SetProps("DashAttack",1380/10,88,1,10,100);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsDashing) {m_Animation->SetProps("Dash",966/7,88,1,7,125);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsFalling) {m_Animation->SetProps("Fall",384/3,88,1,3,150);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsHurting) {m_Animation->SetProps("Hurt",512/4,88,1,4,100);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsSliding) {m_Animation->SetProps("Slide",690/5,88,1,5,200);m_Collider->SetBuffer(-40,-79,-20,40);}
    if(m_IsCrouching) {m_Animation->SetProps("Crouch",828/6,88,1,6,75);m_Collider->SetBuffer(-45,-20,0,-19);}
    if(m_IsWalling) {m_Animation->SetProps("WallSlide",414/3,88,1,3,125);m_Collider->SetBuffer(-70,-20,40,-19);}


}

void Waifu::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}


