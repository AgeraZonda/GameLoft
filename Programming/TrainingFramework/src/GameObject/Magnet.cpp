#include "Magnet.h"
#include <math.h> 
#include "GameManager/ResourceManagers.h"
Vector2 oriPos;
Magnet::Magnet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{

	m_TargetPosition = Vector2(0, 0);
	m_CurrentDirection = 50;
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_Cooldown2 = 0.0;
	m_speed = 0;

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
int Magnet::getCurrentPoint()
{
	return m_CurrentPoint;
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
			m_speed = -m_speed;
	}


	
	


	if (true)
	{
		pos.x += m_speed * sin(m_angle * PI / 180) * deltatime;
		//if (pos.x > m_TargetPosition.x)
		//	pos.x = m_TargetPosition.x;
	}

	if (false)
	{
		pos.x -= m_speed * sin(m_angle * PI / 180) * deltatime;
		//if (pos.x < m_TargetPosition.x)
		//	pos.x = m_TargetPosition.x;
	}

	if (true)
	{
		pos.y += m_speed * cos(m_angle * PI / 180) * deltatime;
		//if (pos.y > m_TargetPosition.y)
		//	pos.y = m_TargetPosition.y;
	}

	if (false)
	{
		pos.y -= m_speed * cos(m_angle * PI / 180) * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
	if (Application::screenHeight - 150 -pos.y<= 3 && m_speed == 250)
		
	{
		m_isPull = false;
		m_speed = 0;
	}
}

void Magnet::setCurrentPoint(int point)
{
	m_CurrentPoint = point;
}
void Magnet::Grab()
{
	oriPos = Get2DPosition();
	m_speed = -250;
	m_isPull = true;
}
float Magnet::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Magnet::CheckCollider(std::vector<std::shared_ptr<Dorayaki>>& listDorayaki)
{
	Vector2 pos = Get2DPosition();


	for (auto dorayaki : listDorayaki)
	{
		if (dorayaki->IsActive())
		{
			if (distance(pos, dorayaki->Get2DPosition()) < m_SizeCollider + dorayaki->GetColliderSize() && !dorayaki->isPull())
			{
				MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 150));
				m_speed = -m_speed;
				dorayaki->Follow(Vector2(m_speed*sin(m_angle * PI / 180),m_speed*cos(m_angle * PI / 180)));
				m_CurrentPoint += dorayaki->GetValue();
				dorayaki->setIsPull(true);
				SoundManager::GetInstance()->PlaySound("colide");
			}
		}
	}
}

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
