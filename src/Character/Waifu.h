#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include"Collider.h"
#ifndef WAIFU_H
#define WAIFU_H
#define JUMP_TIME 25.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f

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
        float m_JumpTime;
        float m_JumpForce;



        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;
};

#endif // WAIFU_H
