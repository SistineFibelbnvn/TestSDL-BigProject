#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include"Collider.h"
#ifndef WAIFU_H
#define WAIFU_H
#define JUMP_TIME 30.0f
#define JUMP_FORCE 8.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME1 20.0f
#define ATTACK_TIME2 15.0f
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
        bool m_IsHolding;
        bool m_IsPower;
        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime1;
        float m_AttackTime2;


        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;
};

#endif // WAIFU_H
