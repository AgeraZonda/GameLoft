#include "GSCredit.h"

GSCredit::GSCredit()
{

}


GSCredit::~GSCredit()
{
}



void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_credit");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround2->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround2->SetSize(Application::screenWidth, Application::screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 500);
	button->SetSize(170, 45);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);

		});
	m_listButton2.push_back(button);



	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName2 = std::make_shared< Text>(shader, font, "", TEXT_COLOR::WHILE, 1.3);
	m_Text_gameName2->Set2DPosition(Vector2(Application::screenWidth / 2 - 140, 80));
}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{

}

void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{

}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton2)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSCredit::HandleMouseEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	m_BackGround2->Update(deltaTime);
	for (auto it : m_listButton2)
	{
		it->Update(deltaTime);
	}
}

void GSCredit::Draw()
{
	m_BackGround2->Draw();
	for (auto it : m_listButton2)
	{
		it->Draw();
	}
	m_Text_gameName2->Draw();
}
