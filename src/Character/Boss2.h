#ifndef BOSS2_H
#define BOSS2_H
#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
#include"Collider.h"

class Boss2: public Character
{
    public:
        Boss2(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);
        virtual void State();
        bool m_IsDeath1;
        bool m_IsDeath2;
        bool m_IsWalking;
        bool m_IsCleaving;
    private:
        Collider* m_Collider;
        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
        Vector2D m_LastSafePosition;

};

#endif // BOSS2_H
