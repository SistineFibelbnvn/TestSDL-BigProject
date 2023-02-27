#ifndef WAIFU_H
#define WAIFU_H
#include "Character.h"
#include "Animation.h"
#include "Rigidbody.h"
class Waifu : public Character
{
    public:
        Waifu(Properties* props);
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    private:

        Animation* m_Animation;
        Rigidbody* m_Rigidbody;
};

#endif // WAIFU_H
