#include "Camera.h"
Camera* Camera::s_Instance=nullptr;

void Camera::Update(float dt)
{
    m_Viewbox.x=m_Target->X-Engine::GetInstance()->GetScreenWidth()/2;
    if(m_Viewbox.x<0) m_Viewbox.x=0;
    if(m_Viewbox.x>(3.33*Engine::GetInstance()->GetScreenWidth()-m_Viewbox.w)) m_Viewbox.x=3.33*Engine::GetInstance()->GetScreenWidth()-m_Viewbox.w;
    m_Viewbox.y=(int)(Engine::GetInstance()->GetScreenHeight()*((int)m_Target->Y/(int)Engine::GetInstance()->GetScreenHeight()));
    m_Position=Vector2D(m_Viewbox.x,m_Viewbox.y);
}
