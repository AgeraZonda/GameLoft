#pragma once

#include "Sprite2D.h"
#include "Magnet.h"
enum class DORAYAKI_TYPE
{
	None,
	Dorayaki,
	Xuka,
	Mimi,
	StrongBuff
};

class Dorayaki : public Sprite2D
{
public:
	Dorayaki(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Dorayaki();
	bool		IsActive();
	void		SetActive(bool status);

	void		Update(float deltaTime) override;

	void		CheckCollider(std::shared_ptr<Magnet> Magnet);

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetValue(float damage);
	float		GetValue();
	void		SetType(DORAYAKI_TYPE type);
	DORAYAKI_TYPE	GetType();
	void		setIsPull(bool isPull);
	bool		isPull();

private:
	int		m_Heal;
	bool	m_active;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float	m_Value;
	float	m_SizeCollider;
	bool	m_isPull;
	DORAYAKI_TYPE m_type;
	float distance(Vector2 pos, Vector2 target);

};
