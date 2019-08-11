#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
class Player;
class Dorayaki;
class Magnet;
class Text;
class Enermy;
class ExplosiveEffect;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override;
	
	static int m_score;
	static float m_timeleft;
	static int current_level;
private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_scoreText;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>	m_listText;
	std::shared_ptr<GameButton> button; 
	std::shared_ptr<GameButton> button_exit;


	std::shared_ptr<Text>  m_playerTimeLeftText;
	std::shared_ptr<Text>  m_defeat;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Magnet> m_Magnet;
	std::vector<std::shared_ptr<Dorayaki>> m_listDorayaki;
	std::vector<std::shared_ptr<Enermy>> m_listEnemy;
	std::vector<std::shared_ptr<ExplosiveEffect>> m_listExplosiveEffect;

	//float m_SpawnCooldown;
	void CreateRandomDorayaki();
	void SpawnExplosive(Vector2 pos);
};

