#ifndef BOSS1_H
#define BOSS1_H
#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include"Collider.h"

class Boss1: public Character
{
    public:
        Boss1(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);
        virtual void State();
        bool m_IsWalking;
        bool m_IsAttacking;
        bool m_IsDeath;
    private:
        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;
};

#endif // BOSS1_H
