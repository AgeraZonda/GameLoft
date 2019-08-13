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
#include "GameManager/FileManager.cpp"
int GSPlay::m_score = 0;
float GSPlay::m_timeleft = 30;
int GSPlay::current_level = 4;
int isDefeat;
GSPlay::GSPlay()
{
	//m_SpawnCooldown = 0.5;
	isDefeat = false;
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
	m_scoreText = std::make_shared< Text>(shader, font, "SCORE: ", TEXT_COLOR::WHILE, 1.0);
	m_scoreText->Set2DPosition(Vector2(5, 25));
	m_playerTimeLeftText = std::make_shared< Text>(shader, font, "TIMELEFT: ", TEXT_COLOR::WHILE, 1.0);
	m_playerTimeLeftText->Set2DPosition(Vector2(5, 50));

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("dora_blink");
	shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 7, 0.7);
	exp->SetSize(-75, 75);
	exp->SetActive(false);
	m_listExplosiveEffect.push_back(exp);

	for (int i = 0; i < current_level; i++)
	{
		CreateRandomDorayaki();
	}
	


	

	//init sound
	SoundManager::GetInstance()->AddSound("colide");
	SoundManager::GetInstance()->AddSound("return");
    if(current_level==4)SoundManager::GetInstance()->PlaySound("bground");

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
		if(m_Magnet->isPull() == false)
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
	
	if (isDefeat) return;  // defeat k the choi dc
	m_Magnet->Update(deltaTime);
	m_Magnet->CheckCollider(m_listDorayaki);
	//update enermies
	int dorayaki_count = 0; 
	for (auto dorayaki : m_listDorayaki)
	{
		if (dorayaki->IsActive())
		{
			if (dorayaki->IsExplosive())
			{
				dorayaki->SetActive(false);
				SpawnExplosive(dorayaki->Get2DPosition());
			}
			dorayaki_count++;
			dorayaki->Update(deltaTime);
			
		}
	}
		for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Update(deltaTime);
		}
	}
	if (dorayaki_count == 0 && m_timeleft > 1) // tang man choi
	{
		current_level++;
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	}
	if (m_timeleft <= 1)	//thua
	{
		writeScore(m_score);
		isDefeat = true;

		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto texture = ResourceManagers::GetInstance()->GetTexture("defeat");
		m_timeleft = 5 + current_level * 5;
		//BackGround
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		m_defeat = std::make_shared<Sprite2D>(model, shader, texture);
		m_defeat->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
		m_defeat->SetSize(Application::screenWidth, Application::screenHeight);

		model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		texture = ResourceManagers::GetInstance()->GetTexture("button_restart");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(100, 270);
		button->SetSize(160, 40);
		button->SetOnClick([]() {
			m_score = 0;
			current_level = 4;
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
			SoundManager::GetInstance()->PauseSound("bground");
			});
		m_listButton.push_back(button);
		texture = ResourceManagers::GetInstance()->GetTexture("button_menu");
		button_exit = std::make_shared<GameButton>(model, shader, texture);
		button_exit->Set2DPosition(Application::screenWidth -100, 270);
		button_exit->SetSize(160, 40);
		button_exit->SetOnClick([]() {
			m_score = 0;
			current_level = 4;
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
			SoundManager::GetInstance()->PauseSound("bground");
			});
		m_listButton.push_back(button_exit);

	}

	//update Score
	m_timeleft -= deltaTime;
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
	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}
	if (m_Player->IsAlive())
		m_Player->Draw();
	if (m_Magnet->IsAlive())
		m_Magnet->Draw();

	if (isDefeat)m_defeat->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}


	

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

void GSPlay::SpawnExplosive(Vector2 pos)
{
	for (auto exp : m_listExplosiveEffect)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}

	//animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("dora_blink");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, Vector2(960, 768), Vector2(192, 192), 0, 7, 0.7);
	exp->SetSize(80, 80);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}
