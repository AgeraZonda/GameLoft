#include "Dorayaki.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
Dorayaki::Dorayaki(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.3;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500;
	m_Heal = 5;
	m_Value = 10;
	m_SizeCollider = 20;
	m_type = DORAYAKI_TYPE::None;
	m_isPull = false;
}


Dorayaki::~Dorayaki()
{
}


void Dorayaki::Update(float deltaTime)
{
	if (!m_active)
		return;




	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight)
		m_active = false;
}



float Dorayaki::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Dorayaki::SetType(DORAYAKI_TYPE type)
{
	m_type = type;
}

DORAYAKI_TYPE Dorayaki::GetType()
{
	return m_type;
}
//void Dorayaki::CheckCollider(std::shared_ptr<Magnet> Magnet)
//{
//	Vector2 pos = Get2DPosition();
//	if (distance(pos, Magnet->Get2DPosition()) < m_SizeCollider + Magnet->GetColliderSize())
//	{
//		m_isPull = true;
//	}
//}


bool Dorayaki::IsActive()
{
	return m_active;
}

void Dorayaki::SetActive(bool status)
{
	m_active = status;
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






void Dorayaki::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Dorayaki::GetColliderSize()
{
	return m_SizeCollider;
}