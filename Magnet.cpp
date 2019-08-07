#include "Magnet.h"
#include "GameManager/ResourceManagers.h"

Magnet::Magnet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_TargetPosition = Vector2(0, 0);
	m_CurrentDirection = Vector2(0, 0);
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500;
	m_TimeLeft = 100;
	m_SizeCollider = 15;
	m_isAlive = true;
	m_CurrentPoint = 0;

}

Magnet::~Magnet()
{
}
Vector2 Magnet::getDirection()
{
	return m_CurrentDirection;
}
void Magnet::setDirection(Vector2 direction)
{
	m_CurrentDirection = direction;
}
void Magnet::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}

void Magnet::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

	if (m_TimeLeft <= 0)
	{
		SoundManager::GetInstance()->PlaySound("explosive_2");
		m_isAlive = false;
		return;
	}
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x)
	{
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		pos.x -= m_speed * deltatime;
		if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.y < m_TargetPosition.y)
	{
		pos.y += m_speed * deltatime;
		if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	if (pos.y > m_TargetPosition.y)
	{
		pos.y -= m_speed * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
}



float Magnet::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Magnet::CheckCollider(std::vector<std::shared_ptr<Dorayaki>>& listBullet)
{
	Vector2 pos = Get2DPosition();


	for (auto bullet : listBullet)
	{
		if (bullet->IsActive())
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_CurrentPoint -= bullet->GetValue();
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
