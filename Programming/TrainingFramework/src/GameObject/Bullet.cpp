#include "Bullet.h"


Bullet::Bullet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed = 500.0;
	m_active = true;
	m_type = BULLET_TYPE::None;
	m_SizeCollider = 10;
	m_Damage = 5;
	m_speedX = 0;
	m_speedY = 0;

}

Bullet::~Bullet()
{
}

void Bullet::Follow(Vector2 vector)
{
	m_speedX = vector.x;
	m_speedY = vector.y;
}

void Bullet::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y - m_speed * deltatime;
	Set2DPosition(pos);

	if (pos.y <= 0 || pos.y > Application::screenHeight)
		m_active = false;
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
}

bool Bullet::IsActive()
{
	return m_active;
}

void Bullet::SetActive(bool status)
{
	m_active = status;
}

void Bullet::SetSpeed(float speed)
{
	m_speed = speed;
}

void Bullet::SetType(BULLET_TYPE type)
{
	m_type = type;
}

BULLET_TYPE Bullet::GetType()
{
	return m_type;
}

void Bullet::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Bullet::GetColliderSize()
{
	return m_SizeCollider;
}

void Bullet::SetDamage(float damage)
{
	m_Damage = damage;
}

float Bullet::GetDamage()
{
	return m_Damage;
}

