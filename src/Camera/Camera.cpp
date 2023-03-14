#include "Camera.h"
Camera* Camera::s_Instance=nullptr;

void Camera::Update(float dt)
{
    m_Viewbox.x=m_Target->X-Engine::GetInstance()->GetScreenWidth()/2;
    if(m_Viewbox.x<0) m_Viewbox.x=0;
    if(m_Viewbox.x>(2*Engine::GetInstance()->GetScreenWidth()-m_Viewbox.w)) m_Viewbox.x=2*Engine::GetInstance()->GetScreenWidth()-m_Viewbox.w;
    m_Viewbox.y=(int)(Engine::GetInstance()->GetScreenHeight()*((int)m_Target->Y/(int)Engine::GetInstance()->GetScreenHeight()));
    //SpeedCamera=SpeedCamera+0.001;
    //if(SpeedCamera>=5){SpeedCamera=5;}
    //m_Viewbox.x+=SpeedCamera;
    m_Position=Vector2D(m_Viewbox.x,m_Viewbox.y);
}
