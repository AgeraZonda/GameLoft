#include "GSScore.h"
#include "GameManager/FileManager.cpp"
#include <string>
GSScore::GSScore()
{

}


GSScore::~GSScore()
{
}



void GSScore::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround1->SetSize(Application::screenWidth, Application::screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button1 = std::make_shared<GameButton>(model, shader, texture);
	button1->Set2DPosition(Application::screenWidth / 2, 350);
	button1->SetSize(170, 45);
	button1->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton1.push_back(button1);

	


	std::list<int> listScore = readScore();
	int count = 0;
	for (auto score : listScore)
	{
		count++;
		shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
		std::string temp = "Top " + std::to_string(4-count) + " : " + std::to_string(score);
		m_Text_gameName1 = std::make_shared< Text>(shader, font, temp , TEXT_COLOR::WHILE, 1.3);
		m_Text_gameName1->Set2DPosition(Vector2(Application::screenWidth / 2 - 90, 580 - 50*count));
		m_listText.push_back(m_Text_gameName1);
	}
	//text game title
	
}

void GSScore::Exit()
{
}


void GSScore::Pause()
{

}

void GSScore::Resume()
{

}


void GSScore::HandleEvents()
{

}

void GSScore::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton1)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSScore::HandleMouseEvents(int x, int y)
{
}

void GSScore::Update(float deltaTime)
{
	m_BackGround1->Update(deltaTime);
	for (auto it : m_listButton1)
	{
		it->Update(deltaTime);
	}
}

void GSScore::Draw()
{
	m_BackGround1->Draw();
	for (auto it : m_listButton1)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}
