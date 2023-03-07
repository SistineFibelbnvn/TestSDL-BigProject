#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include"Collider.h"
#ifndef WAIFU_H
#define WAIFU_H
#define JUMP_TIME 10.0f
#define JUMP_FORCE 10.0f
#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f
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

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;
};

#endif // WAIFU_H
