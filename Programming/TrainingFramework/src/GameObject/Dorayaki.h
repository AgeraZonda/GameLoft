#pragma once

#include "Sprite2D.h"


class Dorayaki : public Sprite2D
{
public:
	Dorayaki(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Dorayaki();
	bool		IsActive();
	void		SetActive(bool status);
	void MoveToPossition(Vector2 pos);
	void		Update(float deltaTime) override;
	void		Follow(Vector2 vector);
	bool		CanShoot();

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetValue(float value);
	float		GetValue();
	bool		isPull();
	void		setIsPull(bool pull);
	void		Explosive();
	bool		IsExplosive();

private:
	int		m_Heal;
	bool	m_active;
	bool	m_Explosive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_Value;
	float	m_SizeCollider;
	float	m_speedX;
	float	m_speedY;
	bool	m_isPull;
	Vector2 m_TargetPosition;


	float distance(Vector2 pos, Vector2 target);

};
#pragma once
