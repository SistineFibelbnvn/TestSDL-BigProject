#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include "Collider.h"
#ifndef WAIFU_H
#define WAIFU_H
#define JUMP_TIME 22.0f
#define JUMP_FORCE 9.0f
#define RUN_FORCE 4.0f
#define RUN_SOUND 30.0f
#define ATTACK_SOUND 35.0f
#define DASH_ATTACK_SOUND 50.0f

class Waifu : public Character
{
    public:
        Waifu(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        virtual void State();
    private:
        bool m_IsJumping;
        bool m_IsGrounded;
        bool m_IsRunning;
        bool m_IsCrouching;
        bool m_IsFalling;
        bool m_IsAttacking;
        bool m_IsDashing;
        bool m_IsDashAttacking;
        bool m_IsDeath;
        bool m_IsHurting;
        bool m_IsLaddering;
        bool m_IsSliding;
        bool m_IsWalling;
        bool m_IsMusic;
        bool m_IsSoundEffect;
        float m_RunSound1;
        float m_RunSound2;
        float m_AttackSound;
        float m_DashAttackSound;
        float m_JumpTime;
        float m_JumpForce;



        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;
};

#endif // WAIFU_H
