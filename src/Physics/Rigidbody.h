#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "Vector2D.h"
#define UNI_MASS 0.8f
#define GRAVITY 5.0f
#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class Rigidbody
{
    public:
        Rigidbody()
        {
            m_Mass=UNI_MASS;
            m_Gravity=GRAVITY;
        }
        inline void SetMass(float Mass){m_Mass=Mass;}
        inline void SetGravity(float Gravity){m_Gravity=Gravity;}

        inline float GetMass(){return m_Mass;}
        inline Vector2D Position(){return m_Position;}
        inline Vector2D Veclocity(){return m_Velocity;}
        inline Vector2D Accelaration(){return m_Accelaration;}

        inline void ApplyForce(Vector2D Force){m_Force=Force;}
        inline void ApplyForceX(float ForceX){m_Force.X=ForceX;}
        inline void ApplyForceY(float ForceY){m_Force.Y=ForceY;}
        inline void UnSetForce(){m_Force=Vector2D(0,0);}

        inline void ApplyFricition(Vector2D Friction){m_Friciton=Friction;}
        inline void UnSetFriction(){m_Friciton=Vector2D(0,0);}
        void Update(float dt){
            m_Accelaration.X=(m_Force.X+m_Friciton.X)/m_Mass;
            m_Accelaration.Y=(m_Gravity+m_Force.Y/m_Mass);
            m_Velocity=m_Accelaration*dt;
            m_Position=m_Velocity*dt;}


    public:
        float m_Mass;
        float m_Gravity;
        Vector2D m_Force;
        Vector2D m_Friciton;
        Vector2D m_Position;
        Vector2D m_Velocity;
        Vector2D m_Accelaration;

};

#endif // RIGIDBODY_H
