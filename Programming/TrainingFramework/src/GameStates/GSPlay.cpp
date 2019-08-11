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
#include "Magnet.h"
#include "ExplosiveEffect.h"

int GSPlay::m_score = 0;
float GSPlay::m_timeleft = 30;
int GSPlay::current_level = 4;
GSPlay::GSPlay()
{
	//m_SpawnCooldown = 0.5;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	m_timeleft = 5 + current_level* 5;
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
	m_Magnet->setCurrentPoint(m_score);
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
	for (int i = 0; i < current_level; i++)
	{
		CreateRandomDorayaki();
	}
	


	//m_listExplosiveEffect.push_back(exp);

	//init sound
	SoundManager::GetInstance()->AddSound("colide");
	//SoundManager::GetInstance()->AddSound("explosive_2");
	//SoundManager::GetInstance()->AddSound("bground");
	SoundManager::GetInstance()->AddSound("return");
	//SoundManager::GetInstance()->AddSound("fire_enemy");
	SoundManager::GetInstance()->PlaySound("bground");

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
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	

	if (m_Magnet->GetTimeLeft() > 0)
		m_Magnet->Update(deltaTime);

	m_Magnet->CheckCollider(m_listDorayaki);

	





	//update enermies
	int dorayaki_count = 0; 
	for (auto dorayaki : m_listDorayaki)
	{
		if (dorayaki->IsActive())
		{
			dorayaki_count++;
			dorayaki->Update(deltaTime);
			//dorayaki->CheckCollider(m_Magnet);
		}
	}
	if (dorayaki_count == 0 && m_timeleft > 1)
	{
		current_level++;
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);

		SoundManager::GetInstance()->PauseSound("bground");
	}
	if (m_timeleft <= 1)
	{
		auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
		m_defeat = std::make_shared< Text>(shader, font, "Defeat", TEXT_COLOR::RED,3);
		m_defeat->Set2DPosition(Vector2(Application::screenWidth / 2 - 110, 400));
		m_listText.push_back(m_defeat);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("button_restart");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(Application::screenWidth / 2, 150);
		button->SetSize(200, 50);
		button->SetOnClick([]() {
			m_score = 0;
			current_level = 4;
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
			SoundManager::GetInstance()->PauseSound("bground");
			});
		m_listButton.push_back(button);
		texture = ResourceManagers::GetInstance()->GetTexture("button_exit");
		button_exit = std::make_shared<GameButton>(model, shader, texture);
		button_exit->Set2DPosition(Application::screenWidth / 2, 250);
		button_exit->SetSize(200, 50);
		button_exit->SetOnClick([]() {
			exit(0);
			});
		m_listButton.push_back(button_exit);

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
	m_timeleft -= deltaTime;
	std::cout << (int)m_timeleft << std::endl;
	m_score = m_Magnet->getCurrentPoint();
	std::stringstream stream;
	stream << std::fixed << std::setprecision(0) << m_score;
	std::string score = "SCORE: " + stream.str();
	m_scoreText->setText(score);
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(0) << m_timeleft;
	std::string heal = "TIMELEFT: " + stream2.str();
	m_playerTimeLeftText->setText(heal);
}

void GSPlay::Draw()
{
	//ground
	m_BackGround->Draw();

	for (auto dorayaki : m_listDorayaki)
		if (dorayaki->IsActive())
			dorayaki->Draw();

	if (m_Player->IsAlive())
		m_Player->Draw();
	if (m_Magnet->IsAlive())
		m_Magnet->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}



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

void GSPlay::CreateRandomDorayaki()
{

	int rangeX = Application::screenWidth - 30;
	int rangeY = 300;
	int numX = rand() % rangeX + 10;
	int numY = rand() % rangeY +10;

	Vector2 pos;
	pos.x = numX;
	pos.y = numY;

	for (auto enermy : m_listDorayaki)
	{
		if (!enermy->IsActive())
		{
			enermy->SetActive(true);
			enermy->Set2DPosition(pos);
			return;
		}
	}
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("dorayaki");

	std::shared_ptr<Dorayaki> dorayaki = std::make_shared<Dorayaki>(model, shader, texture);
	dorayaki->Set2DPosition(pos);
	dorayaki->SetSize(100, 100);
	dorayaki->SetRotation(180);
	dorayaki->MoveToPossition(pos);
	m_listDorayaki.push_back(dorayaki);
}


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
