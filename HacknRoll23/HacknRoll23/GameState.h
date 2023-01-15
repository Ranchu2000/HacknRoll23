#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "imports.h"
#include "Player.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "RangedBoss.h"
#include "PlayerProjectile.h"
#include "EnemyProjectile.h"
#include "LevelsSystem.h"

class GameState : public State
{
private:
	// Background
	Texture backgroundTexture;
	Sprite background;
	View view;

	// Text/GUI
	Font font;

	Texture pauseText;
	Sprite pauseButton;

	Text hp;
	Text hpText;
	RectangleShape hpMaxBar;
	RectangleShape hpCurBar;

	Text waveText;
	Text enemiesText;

	std::map<std::string, int> upgradeCur;

	// Player
	Player* player;
	Texture playerTex;
	float noDamageTimer;

	// Wave
	int waveNum;
	int spawnTimer;
	int spawnTimerMax;
	int enemiesLeft;
	LevelsSystem* levels;
	int score;
	
	std::vector<int> numMelee;
	std::vector<int> numRanged;
	int meleeSpawned;
	int rangedSpawned;
	int bossSpawned;
	std::vector<Enemy*> activeEnemies;
	sf::Texture meleeTex;
	sf::Texture rangedTex;

	//Projectiles 
	sf::Texture playerProjectileTex;
	std::vector<PlayerProjectile> playerProjectiles;
	sf::Texture enemyProjectileTex;
	std::vector<EnemyProjectile> enemyProjectiles;

	void initVariables();
	void initFonts();
	void initPlayer();
	void initGui();
	void resetGui();
	void initEnemies();
	void initProjectile();
public:
	GameState(StateData* state_data, std::map<std::string, int> upgradeCur, int waveNum);
	virtual ~GameState();

	void updateInput(const float& dt); //nothing
	void updatePlayerInput(const float& dt);
	void updateView(const float& dt);
	void updateButtons(); //handle user actions- game/setting/editor/exit
	void updatePlayer(const float& dt);
	void updatePlayerShooting(const float& dt);
	void updateEnemyShooting(const float& dt);
	void updateEnemies(const float& dt);
	void updateGameState(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);//draw stuff

};

#endif