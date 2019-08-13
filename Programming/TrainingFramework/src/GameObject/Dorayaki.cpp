
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
#include "Dorayaki.h"
Dorayaki::Dorayaki(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_active = true;
	m_MaxCooldown = 0.3;
	m_Cooldown = 0.0;
	m_speedX = 0;
	m_speedY = 0;
	m_MaxSpeed = 500;
	m_Heal = 5;
	m_Value = 10;
	m_Explosive = false;
	m_SizeCollider = 45;
	m_isPull = false;
}void Dorayaki::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}
void Dorayaki::Follow(Vector2 vector)
{
	m_speedX = vector.x;
	m_speedY = vector.y;
}
Dorayaki::~Dorayaki()
{
}


void Dorayaki::Update(float deltaTime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	if (true)
	{
		pos.x += m_speedX * deltaTime;
		/*if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;*/
	}

	if (false)
	{
		pos.x -= m_speedX * deltaTime;
		/*if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;*/
	}

	if (true)
	{
		pos.y += m_speedY * deltaTime;
		/*if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;*/
	}

	if (false)
	{
		pos.y -= m_speedY * deltaTime;
	/*	if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;*/
	}

	Set2DPosition(pos);
	if (pos.y >= Application::screenHeight - 200 && m_speedY > 0)
	{
		SoundManager::GetInstance()->PlaySound("return");
		Explosive();
		
	}
		
	//if (m_Heal <= 0 || m_Explosive)
	//{
	//	SoundManager::GetInstance()->PlaySound("explosive");
	//	m_Explosive = true;
	//	GSPlay::m_score ++;
	//	return;
	//}

	//if (m_Cooldown > 0)
	//{
	//	m_Cooldown -= deltaTime;
	//}

	//Vector2 pos = Get2DPosition();
	//pos.y = pos.y + m_speed * deltaTime;
	//Set2DPosition(pos);

	//if (pos.y > Application::screenHeight)
	//	m_active = false;
}
bool Dorayaki::isPull()
{
	return m_isPull;
}
void Dorayaki::setIsPull(bool pull)
{
	m_isPull = pull;
}
bool Dorayaki::CanShoot()
{
	return (m_Cooldown <= 0);
}


float Dorayaki::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}


bool Dorayaki::IsActive()
{
	return m_active;
}

void Dorayaki::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
	m_Heal = 10;
}

void Dorayaki::SetValue(float damage)
{
	m_Value = damage;
}

float Dorayaki::GetValue()
{
	return m_Value;
}

void Dorayaki::Explosive()
{
	m_Explosive = true;
}

bool Dorayaki::IsExplosive()
{
	return m_Explosive;
}


void Dorayaki::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Dorayaki::GetColliderSize()
{
	return m_SizeCollider;
}