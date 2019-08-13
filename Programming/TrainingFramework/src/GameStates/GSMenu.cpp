#include "GSMenu.h"

GSMenu::GSMenu()
{
	m_time = 0;
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 270);
	button->SetSize(170, 45);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("button_credit");
	std::shared_ptr<GameButton> button1 = std::make_shared<GameButton>(model, shader, texture);
	button1->Set2DPosition(Application::screenWidth / 2, 350);
	button1->SetSize(170, 45);
	button1->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);

		});
	m_listButton.push_back(button1);


	texture = ResourceManagers::GetInstance()->GetTexture("button_score");
	std::shared_ptr<GameButton> button2 = std::make_shared<GameButton>(model, shader, texture);
	button2->Set2DPosition(Application::screenWidth / 2, 430);
	button2->SetSize(170, 45);
	button2->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Score);
		});
	m_listButton.push_back(button2);


	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_exit");
	std::shared_ptr<GameButton> button3 = std::make_shared<GameButton>(model, shader, texture);
	button3->Set2DPosition(Application::screenWidth / 2, 510);
	button3->SetSize(170, 45);
	button3->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button3);



	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "", TEXT_COLOR::WHILE, 1.3);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 140, 80));
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (m_time < 0.2) return;
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::HandleMouseEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_time += deltaTime;
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
