#include <sstream>
#include <iomanip>
#include <thread>
#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "Player.h"
#include "Dorayaki.h"
#include "Magnet.h"
#include "ExplosiveEffect.h"

int GSPlay::m_score = 0;
GSPlay::GSPlay()
{
	//m_SpawnCooldown = 0.5;
	m_score = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("doremon");
	m_Player = std::make_shared<Player >(model, shader, texture);
	m_Player->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 50);
	m_Player->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 50));
	m_Player->SetSize(130, -130);

	texture = ResourceManagers::GetInstance()->GetTexture("magnet");
	m_Magnet = std::make_shared<Magnet>(model, shader, texture);
	m_Magnet->Set2DPosition(Application::screenWidth / 2, Application::screenHeight - 150);
	m_Magnet->MoveToPossition(Vector2(Application::screenWidth / 2, Application::screenHeight - 150));
	m_Magnet->SetSize(60, 100);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_scoreText = std::make_shared< Text>(shader, font, "SCORE: ", TEXT_COLOR::RED, 1.0);
	m_scoreText->Set2DPosition(Vector2(5, 25));
	m_playerTimeLeftText = std::make_shared< Text>(shader, font, "TIMELEFT: ", TEXT_COLOR::RED, 1.0);
	m_playerTimeLeftText->Set2DPosition(Vector2(5, 50));

	//init effect
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->SetActive(false);
	//m_listExplosiveEffect.push_back(exp);

	//init sound
	//SoundManager::GetInstance()->AddSound("explosive");
	//SoundManager::GetInstance()->AddSound("explosive_2");
	//SoundManager::GetInstance()->AddSound("bground");
	//SoundManager::GetInstance()->AddSound("fire");
	//SoundManager::GetInstance()->AddSound("fire_enemy");
	//SoundManager::GetInstance()->PlaySound("bground");

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == 32 && bIsPressed == true)
	{
		m_Magnet->Grab();
	}
}

void GSPlay::HandleMouseEvents(int x, int y)
{

}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_Magnet->Update(deltaTime);
	/*if (m_SpawnCooldown > 0)
	{
		m_SpawnCooldown -= deltaTime;
	}
	if (m_SpawnCooldown <= 0)
	{
		CreateRandomDorayaki();
		m_SpawnCooldown = 0.3;
	}*/

	//update player
	//if (m_Player->IsAlive())
	//{
	//	m_Player->Update(deltaTime);

	//	if (m_Player->CanShoot())
	//		m_Player->Shoot(m_listBullet);

	//	m_Player->CheckCollider(m_listBullet, m_listEnermy);
	//}

	//update enermies
	for (auto dorayaki : m_listDorayaki)
	{
		if (dorayaki->IsActive())
		{
			
			dorayaki->Update(deltaTime);
			//dorayaki->CheckCollider(m_Magnet);
		}
	}


	/*for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}*/

	//update bullets

	//update Score
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "SCORE: " + stream.str();
	m_scoreText->setText(score);
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(0) << m_Player->GetHeal();
	std::string heal = "HEAL: " + stream2.str();
	m_playerTimeLeftText->setText("11");
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto enermy : m_listDorayaki)
		if (enermy->IsActive())
			enermy->Draw();

	if (m_Player->IsAlive())
		m_Player->Draw();
	if (m_Magnet->IsAlive())
		m_Magnet->Draw();




	/*for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}*/

	//UI
	m_scoreText->Draw();
	m_playerTimeLeftText->Draw();
}

//void GSPlay::CreateRandomDorayaki()
//{
//
//	int range = Application::screenWidth - 10 + 1;
//	int num = rand() % range + 10;
//
//	Vector2 pos;
//	pos.x = num;
//	pos.y = 10;
//
//	for (auto enermy : m_listDorayaki)
//	{
//		if (!enermy->IsActive())
//		{
//			enermy->SetActive(true);
//			enermy->Set2DPosition(pos);
//			return;
//		}
//	}
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
//	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("dorayaki");
//
//	std::shared_ptr<Dorayaki> enermy = std::make_shared<Dorayaki>(model, shader, texture);
//	enermy->Set2DPosition(pos);
//	enermy->SetSize(40, 40);
//	enermy->SetRotation(180);
//	m_listDorayaki.push_back(enermy);
//}
//
//
//void GSPlay::SpawnExplosive(Vector2 pos)
//{
//	for (auto exp : m_listExplosiveEffect)
//	{
//		if (!exp->IsActive())
//		{
//			exp->SetActive(true);
//			exp->Set2DPosition(pos);
//			return;
//		}
//	}
//
//	//animation
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
//	auto texture = ResourceManagers::GetInstance()->GetTexture("explosive");
//	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
//	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
//	exp->SetSize(100, 100);
//	exp->Set2DPosition(pos);
//	m_listExplosiveEffect.push_back(exp);
//}
