#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
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
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth + 200, -screenHeight);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::WHILE, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));


	//doraemon
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("doremon");
	m_Doraemon = std::make_shared<Sprite2D>(model, shader, texture);
	m_Doraemon->Set2DPosition(screenWidth / 2, screenHeight - 200);
	m_Doraemon->SetSize(120, 150);

	//dorayaki
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("dorayaki");
	
	std::shared_ptr<Sprite2D> Reward1 = std::make_shared<Sprite2D>(model, shader, texture);
	Reward1->Set2DPosition(screenWidth / 2, 100);
	Reward1->SetSize(80, 100);
	m_RewardList.push_back(Reward1);
	
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
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	m_Doraemon->Draw();
	for (auto i : m_RewardList)
	{
		i->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}