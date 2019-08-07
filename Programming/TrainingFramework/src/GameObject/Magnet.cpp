#include "Magnet.h"
#include <math.h> 
#include "GameManager/ResourceManagers.h"
Magnet::Magnet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_CurrentDirection = 50;
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_Cooldown2 = 0.0;
	m_speedX = 250;
	m_speedY = 250;
	m_MaxSpeed = 500;
	m_TimeLeft = 100;
	m_SizeCollider = 15;
	m_isAlive = true;
	m_CurrentPoint = 0;
	m_angle = 0.0;
	m_isPull = false;

}

Magnet::~Magnet()
{
}
int Magnet::getDirection()
{
	return m_CurrentDirection;
}
void Magnet::setDirection(int angle)
{
	m_CurrentDirection = angle;
}
void Magnet::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
	
}

void Magnet::Update(GLfloat deltatime)
{
	if (m_angle > 70 && m_Cooldown <= 0)
	{
		m_CurrentDirection = m_CurrentDirection *-1;
		m_Cooldown = m_MaxCooldown;
	}
	if (m_angle < -70 && m_Cooldown <= 0)
	{
		m_CurrentDirection = m_CurrentDirection * -1;
		m_Cooldown = m_MaxCooldown;
	}
	if (m_Cooldown > 0) m_Cooldown -= deltatime;

	if(!m_isPull)m_angle += deltatime * m_CurrentDirection;
	this->SetRotation(m_angle);
	


	if (!m_isAlive)
		return;

	if (m_TimeLeft <= 0)
	{
		SoundManager::GetInstance()->PlaySound("explosive_2");
		m_isAlive = false;
		return;
	}


	if(m_CurrentDirection )
	{

	}
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();


	if ((pos.y <= 50 || pos.y > Application::screenHeight-50 || pos.x <= 50 || pos.x > Application::screenWidth-50))
	{
			MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 150));
			m_speedX = fabs(m_speedX);
			m_speedY =  fabs(m_speedY);
	}
	std::cout << m_Cooldown2 << " " << pos.y << std::endl;

	
	


	if (pos.x < m_TargetPosition.x)
	{
		pos.x += m_speedX * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		pos.x -= m_speedX * deltatime;
		if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.y < m_TargetPosition.y)
	{
		pos.y += m_speedY * deltatime;
		if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	if (pos.y > m_TargetPosition.y)
	{
		pos.y -= m_speedY * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
	if (pos.y >= Application::screenHeight - 200 && m_TargetPosition.y !=-500)
		m_isPull = false;
}


void Magnet::Grab()
{
	float x, y;
	m_speedY = sqrt(125000/(1+pow(tan(m_angle * PI / 180),2)));
	m_speedX = sqrt(125000 - pow(m_speedY, 2));
	std::cout << m_speedY << " " << m_speedX << std::endl;
	MoveToPossition(Vector2(tan(m_angle * PI / 180) * -1050, -500));
	m_isPull = true;
}
float Magnet::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

//void Magnet::CheckCollider(std::vector<std::shared_ptr<Dorayaki>>& listBullet)
//{
//	Vector2 pos = Get2DPosition();
//
//
//	for (auto bullet : listBullet)
//	{
//		if (bullet->IsActive())
//		{
//			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
//			{
//				bullet->SetActive(false);
//				m_CurrentPoint -= bullet->GetValue();
//			}
//		}
//	}
//}

void Magnet::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Magnet::GetColliderSize()
{
	return m_SizeCollider;
}

int Magnet::GetTimeLeft()
{
	return m_TimeLeft;
}

bool Magnet::IsAlive()
{
	return m_isAlive;
}
