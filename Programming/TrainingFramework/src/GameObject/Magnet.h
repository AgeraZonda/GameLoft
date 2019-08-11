#pragma once
#include "Sprite2D.h"
#include "Dorayaki.h"
#include "Application.h"

class Magnet : public Sprite2D
{

public:
	Magnet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Magnet();

	void MoveToPossition(Vector2 pos);
	void Update(GLfloat deltatime) override;
	void Grab();
	bool isPull();
	int getDirection();
	void setDirection(int angle);
	int getCurrentPoint();
	void setCurrentPoint(int point);
	void CheckCollider(std::vector<std::shared_ptr<Dorayaki>>& listBullet);

	void		SetColliderSize(float size);
	float		GetColliderSize();
	int			GetTimeLeft();
	bool		IsAlive();
private:
	Vector2 m_TargetPosition;
	int		m_TimeLeft;
	bool	m_isAlive;
	float	m_speed;
	float	m_MaxSpeed;
	float	m_MaxCooldown;
	float	m_Cooldown;
	float   m_Cooldown2;
	float	m_SizeCollider;
	int   m_CurrentPoint;
	float		m_angle;
	float		m_CurrentDirection;
	bool	m_isPull;


	float distance(Vector2 pos, Vector2 target);
};
