#include "imports.h"
#include "DEFINITIONS.h"
#include "GameState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include "Player.h"
#include "SpawningLogic.h"

void GameState::initVariables()
{
	this->noDamageTimer = 500.f;
	this->meleeSpawned = 0;
	this->rangedSpawned = 0;
	this->bossSpawned = 0;
	this->waveNum += 1;
	this->spawnTimerMax = 200 * 1 / this->waveNum;
	this->levels = new LevelsSystem();
	this->numMelee = this->levels->getNumMeleeEnemies();
	this->numRanged = this->levels->getNumRangedEnemies();
	this->score = 0;
	this->gamesound = new GameSounds();
	this->gamesound->gameStateMusic.play();
	for (int i = 0; i < this->waveNum - 1; i++)
	{
		this->score += this->numMelee[i] + this->numRanged[i];
	}
}

void GameState::initFonts()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void GameState::initPlayer()
{
	this->playerTex.loadFromFile(PLAYER_TEXTURE_SHEET);
	this->player = new Player(this->mapSize / 2 * this->gridSize, this->mapSize / 2 * this->gridSize, this->playerTex, this->upgradeCur);
}

void GameState::initGui()
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Background
	this->backgroundTexture.loadFromFile(GAME_BACKGROUND_FILEPATH);
	this->background.setTexture(this->backgroundTexture);
	this->background.setPosition(0.f, 0.f);


	// View
	this->view.setSize((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT));
	this->view.setCenter((int)(this->mapSize / 2) * this->gridSize, (int)(this->mapSize / 2) * this->gridSize);


	//png are 128 pixels
	this->pauseText.loadFromFile(PAUSE_ICON_FILEPATH);
	this->pauseButton.setTexture(this->pauseText);
	this->pauseButton.setScale(Vector2f(1.f, 1.f));
	this->pauseButton.setPosition(gui::p2pX(95.f, vm) - this->pauseButton.getGlobalBounds().width / 2, gui::p2pY(0.f, vm));


	//hp
	this->hp.setFont(this->font);
	this->hp.setCharacterSize(gui::calcCharSize(vm, 45));
	this->hp.setFillColor(Color(DARK_GREY_COLOR));
	this->hp.setStyle(Text::Bold);
	this->hp.setString("HP");
	this->hp.setPosition(gui::p2pX(1.f, vm), gui::p2pY(0.f, vm));



	this->hpMaxBar.setPosition(gui::p2pX(2.f, vm) + this->hp.getGlobalBounds().width, gui::p2pY(1.f, vm));
	this->hpMaxBar.setFillColor(Color::White);
	this->hpMaxBar.setSize(Vector2f((gui::p2pX(1.25f, vm) * this->player->getAttributeComponent()->getMaxHealth()) + gui::p2pX(.5f, vm), gui::p2pY(5.5f, vm)));

	this->hpCurBar.setPosition(gui::p2pX(2.25f, vm) + this->hp.getGlobalBounds().width, gui::p2pY(1.25f, vm));
	this->hpCurBar.setFillColor(Color(GREEN_COLOR));

	this->hpText.setFont(this->font);
	this->hpText.setCharacterSize(gui::calcCharSize(vm, 45));
	this->hpText.setFillColor(Color(DARK_GREY_COLOR));
	this->hpText.setStyle(Text::Bold);
	this->hpText.setPosition(gui::p2pX(7.5f, vm) + this->hpMaxBar.getGlobalBounds().width, gui::p2pY(0.f, vm));

	//Wave
	this->waveText.setFont(this->font);
	this->waveText.setCharacterSize(gui::calcCharSize(vm, 45));
	this->waveText.setFillColor(Color(DARK_GREY_COLOR));
	this->waveText.setStyle(Text::Bold);
	this->waveText.setString("Wave " + std::to_string(this->waveNum));
	this->waveText.setPosition(gui::p2pX(75.f, vm) - this->waveText.getGlobalBounds().width / 2, gui::p2pY(0.f, vm));
	
	//enemies
	this->enemiesText.setFont(this->font);
	this->enemiesText.setCharacterSize(gui::calcCharSize(vm, 45));
	this->enemiesText.setFillColor(Color(DARK_GREY_COLOR));
	this->enemiesText.setStyle(Text::Bold);
	this->enemiesText.setString("Enemies Left: " + std::to_string(this->enemiesLeft));
	this->enemiesText.setPosition(gui::p2pX(1.f, vm), gui::p2pY(93.f, vm));
}

void GameState::resetGui()
{
}

void GameState::initEnemies()
{
	if (!this->meleeTex.loadFromFile(MELEE_ENEMY_TEXTURE_SHEET))
		throw("ERROR: Failed to load Enemy texture");

	if (!this->rangedTex.loadFromFile(RANGED_ENEMY_TEXTURE_SHEET))
		throw("ERROR: Failed to load Player texture");
	if (!this->bossTex.loadFromFile(BOSS_ENEMY_TEXTURE_SHEET))
		throw("ERROR: Failed to load Player texture");
}

void GameState::initProjectile()
{
	if (!this->playerProjectileTex.loadFromFile(PLAYER_PROJECTILE))
		throw("ERROR: Failed to load projectile texture");

	if (!this->enemyProjectileTex.loadFromFile(ENEMY_PROJECTILE))
		throw("ERROR: Failed to load projectile texture");
}

GameState::GameState(StateData* state_data, std::map<std::string,int> upgradeCur,  int waveNum) : State(state_data), upgradeCur(upgradeCur), waveNum(waveNum)
{
	this->initVariables();
	this->initFonts();
	this->initPlayer();
	this->initGui();
	this->resetGui();
	this->initEnemies();
	this->initProjectile();
}

GameState::~GameState()
{
}

void GameState::updateInput(const float& dt)
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->hpCurBar.setSize(Vector2f((gui::p2pX(1.25f, vm) * this->player->getAttributeComponent()->getCurHealth()), gui::p2pY(5.f, vm)));
	this->hpText.setString(std::to_string(this->player->getAttributeComponent()->getCurHealth()) + "/" + std::to_string(this->player->getAttributeComponent()->getMaxHealth()));
	this->enemiesText.setString("Enemies Left: " + std::to_string(this->enemiesLeft));
}


void GameState::updatePlayerInput(const float& dt)
{
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		this->player->getMovementComponent()->stopVelocity();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
	{
		this->player->move(-1000.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
	{
		this->player->move(1000.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
	{
		this->player->move(0.f, -1000.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Down
	{
		this->player->move(0.f, 1000.f, dt);
	}
}

void GameState::updatePlayer(const float& dt)
{
	this->player->update(dt, this->mousePosView, this->view);
	this->player->checkCollision(dt);
}

void GameState::updatePlayerShooting(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->getDamageTimer() >= this->player->getDamageInterval())
	{
		this->gamesound->shootSound.play();
		sf::Vector2f playerPos = this->player->getCenter();//world coord
		sf::Vector2i playerPosView = this->window->mapCoordsToPixel(playerPos, this->view);
		sf::Vector2f mousePos = this->mousePosView;
		sf::Vector2f normDir = vectorDirection(mousePos, playerPosView);

		int damage = this->player->getDamage();
		int pierceCount = 1 + this->player->getSkillList()->getPiercingSkill().getSkillStackCount();
		int burnCount = this->player->getSkillList()->getBurnSkill().getSkillStackCount();

		PlayerProjectile* newProj;
		if (burnCount > 0)
		{

			newProj = new PlayerProjectile(playerPos, normDir, damage, pierceCount, burnCount, this->playerProjectileTex);
		}
		else
			newProj = new PlayerProjectile(playerPos, normDir, damage, pierceCount, this->playerProjectileTex);


		this->playerProjectiles.push_back(*newProj);

		this->player->resetDamageTimer();
	}

	for (auto& tempProjectile : this->playerProjectiles)
	{
		tempProjectile.move(dt);
	}
}

void GameState::updateEnemies(const float& dt)
{
	std::srand(time(0));


	if (this->meleeSpawned == 0 && this->rangedSpawned == 0)
	{
		this->enemiesLeft = this->numMelee[this->waveNum - 1] + this->numRanged[this->waveNum - 1];
		if (this->waveNum == 5)
			this->enemiesLeft++;
	}

	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer++;

	if (this->waveNum == 5 && this->enemiesLeft == 1 && this->bossSpawned == 0)
	{
		sf::Vector2f randomPos = RandomSpawning(this->player->getCenter().x, this->player->getCenter().y, this->player->getGlobalBounds());
		this->activeEnemies.push_back(new RangedBoss(randomPos.x, randomPos.y, this->bossTex, *(this->player)));
		this->bossSpawned = 1;
		this->spawnTimer = 0;
	}

	if (this->spawnTimer >= this->spawnTimerMax && this->meleeSpawned < this->numMelee[this->waveNum - 1]) //change to total number of enemies spawned per wave
	{
		sf::Vector2f randomPos = RandomSpawning(this->player->getCenter().x, this->player->getCenter().y, this->player->getGlobalBounds());
		this->activeEnemies.push_back(new MeleeEnemy(randomPos.x, randomPos.y, this->meleeTex, *(this->player)));
		this->spawnTimer = 0;
		this->meleeSpawned++;
	}

	if (this->spawnTimer >= this->spawnTimerMax && this->rangedSpawned < this->numRanged[this->waveNum - 1]) //change to total number of enemies spawned per wave
	{
		sf::Vector2f randomPos = RandomSpawning(this->player->getCenter().x, this->player->getCenter().y, this->player->getGlobalBounds());
		this->activeEnemies.push_back(new RangedEnemy(randomPos.x, randomPos.y, this->rangedTex, *(this->player)));
		this->spawnTimer = 0;
		this->rangedSpawned++;
	}

	for (int i = 0; i < this->activeEnemies.size(); i++)
	{
		this->activeEnemies[i]->update(dt, this->mousePosView, this->view);
		this->activeEnemies[i]->updateBurn();
		this->activeEnemies[i]->checkCollision(dt);

		if (this->noDamageTimer < 500.f)
			this->noDamageTimer++;

		if (this->activeEnemies[i]->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->noDamageTimer >= 500.f)
		{
			this->gamesound->playerTakeDamageSound.play();
			this->player->loseHP(this->activeEnemies[i]->getAttributeComp()->damageMax);
			this->noDamageTimer = 0;
		}

		for (int j = 0; j < this->playerProjectiles.size(); j++)
		{

			if (!this->playerProjectiles[j].isInEntity() && this->activeEnemies[i]->getGlobalBounds().intersects(this->playerProjectiles[j].getSprite().getGlobalBounds()))
			{
				this->gamesound->enemyTakeDamageSound.play();
				this->activeEnemies[i]->loseHP(this->playerProjectiles[j].getDamage(), this->playerProjectiles[j].getNormDir(), dt);

				if (this->playerProjectiles[j].getBurnLevel() > 0)
				{
					this->activeEnemies[i]->setTotalBurnDamage(this->playerProjectiles[j].getBurnLevel());
					this->activeEnemies[i]->resetBurnTimer();
				}


				if (this->playerProjectiles[j].reduceHealth() == 0)
				{
					this->playerProjectiles.erase(this->playerProjectiles.begin() + j);
				}
				break;
			}

		}

		for (std::size_t i = 0; i < this->playerProjectiles.size(); ++i)
		{
			this->playerProjectiles[i].setPiercingEntity(false);
			for (std::size_t j = 0; j < this->activeEnemies.size(); ++j)
			{
				if (this->playerProjectiles[i].getSprite().getGlobalBounds().intersects(this->activeEnemies[j]->getGlobalBounds()))
				{
					this->playerProjectiles[i].setPiercingEntity(true);
				}
				break;
			}
		}

		if (this->activeEnemies[i]->getAttributeComp()->hp <= 0)
		{
			this->score++;
			this->activeEnemies.erase(this->activeEnemies.begin() + i);
			this->enemiesLeft--;
		}
	}

	// Implement enemies losing hp due to player damage and increase score
	for (int j = 0; j < this->enemyProjectiles.size(); j++)
	{
		if (this->player->getGlobalBounds().intersects(this->enemyProjectiles[j].getSprite().getGlobalBounds()))
		{
			this->player->loseHP(this->enemyProjectiles[j].getDamage());
			//this->playerProjectiles[j].
			if (this->enemyProjectiles[j].reduceHealth() == 0)
			{
				this->enemyProjectiles.erase(this->enemyProjectiles.begin() + j);
			}
			break;
		}
	}
	// Boss proj
	for (int j = 0; j < this->bossProjectiles.size(); j++)
	{
		if (this->player->getGlobalBounds().intersects(this->bossProjectiles[j].getSprite().getGlobalBounds()))
		{
			this->player->loseHP(this->bossProjectiles[j].getDamage());
			//this->playerProjectiles[j].
			if (this->bossProjectiles[j].reduceHealth() == 0)
			{
				this->bossProjectiles.erase(this->bossProjectiles.begin() + j);
			}
			break;
		}
	}
}

void GameState::updateEnemyShooting(const float& dt)
{
	for (auto i : activeEnemies)
	{
		if (this->bossSpawned)
		{
			RangedBoss* rb = dynamic_cast<RangedBoss*>(i);
			if (rb != nullptr)
			{
				if (rb->isAttacking && rb->clock.getElapsedTime().asMilliseconds() > rb->attackInterval)
				{
					sf::Vector2f playerPos = this->player->getCenter();//world coord
					sf::Vector2f normDir = vectorDirection(playerPos, rb->getPosition());

					int damage = rb->getAttributeComp()->damageMax;

					BossProjectile* newProj = new BossProjectile(rb->getPosition(), normDir, damage, 1, this->enemyProjectileTex);
					this->bossProjectiles.push_back(*newProj);

					rb->resetDamageTimer();
					rb->clock.restart();
				}
			}
		
		}
		else if (RangedEnemy* re = dynamic_cast<RangedEnemy*>(i))
		{
			if (re != nullptr)
			{
				if (re->isAttacking && re->clock.getElapsedTime().asMilliseconds() > re->attackInterval)
				{
					sf::Vector2f playerPos = this->player->getCenter();//world coord
					sf::Vector2f normDir = vectorDirection(playerPos, re->getPosition());

					int damage = re->getAttributeComp()->damageMax;

					EnemyProjectile* newProj = new EnemyProjectile(re->getPosition(), normDir, damage, 1, this->enemyProjectileTex);

					this->enemyProjectiles.push_back(*newProj);

					re->resetDamageTimer();
					re->clock.restart();
				}
			}
			
		}

	}

	for (auto& tempProjectile : this->enemyProjectiles)
	{
		tempProjectile.move(dt);
	}
	for (auto& tempProjectile : this->bossProjectiles)
	{
		tempProjectile.move(dt);
	}
}

void GameState::updateView(const float& dt)
{
	// Setting the view to be at the player
	this->view.setCenter(this->player->getPosition().x + this->player->getGlobalBounds().width / 2, this->player->getPosition().y + this->player->getGlobalBounds().height / 2);
	
	// View Collision
	//Left collision
	if (this->view.getCenter().x - this->view.getSize().x / 2 < 0.f)
		this->view.setCenter(this->view.getSize().x / 2, this->view.getCenter().y);
	//Top collision
	if (this->view.getCenter().y - this->view.getSize().y / 2 < 0.f)
		this->view.setCenter(this->view.getCenter().x, this->view.getSize().y / 2);
	//Right collision
	if (this->view.getCenter().x + this->view.getSize().x / 2 > ((this->mapSize) * this->gridSize))
		this->view.setCenter(((this->mapSize) * this->gridSize) - (this->view.getSize().x / 2), this->view.getCenter().y);
	//Bottom collision
	if (this->view.getCenter().y + this->view.getSize().y / 2 > ((this->mapSize) * this->gridSize))
		this->view.setCenter(this->view.getCenter().x, ((this->mapSize) * this->gridSize) - (this->view.getSize().y / 2));
}

void GameState::updateButtons()
{
	if (gui::isSpriteClicked(this->pauseButton, sf::Mouse::Left, *this->window)) {
		this->gamesound->gameStateMusic.stop();
		this->states->push(new PauseState(this->stateData));
	}
}

void GameState::updateGameState(const float& dt)
{
	if (this->player->getAttributeComponent()->getCurHealth() <= 0)
	{
		this->gamesound->gameStateMusic.stop();
		this->states->push(new GameOverState(this->stateData, this->score, this->waveNum));
		this->endState();
	}
	if (this->enemiesLeft == 0 && this->waveNum != 5 && this->waveNum != 0)
	{
		this->gamesound->gameStateMusic.stop();
		this->states->push(new IntermissionState(this->stateData, this->upgradeCur, this->waveNum));
		this->endState();
	}
	if (this->enemiesLeft == 0 && this->waveNum == 5)
	{
		this->gamesound->gameStateMusic.stop();
		this->states->push(new VictoryState(this->stateData));
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateButtons();
	this->updateInput(dt);
	if (!this->paused)
	{
		this->updatePlayerInput(dt);
		this->updatePlayer(dt);
		this->updateView(dt);
		this->updatePlayerShooting(dt);
		this->updateEnemies(dt);
		this->updateEnemyShooting(dt);
		this->updateGameState(dt);
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	// DRAWING GAME
	target->setView(this->view);
	target->draw(this->background);

	this->player->render(*target);

	for (auto& tempProjectile : this->playerProjectiles)
	{
		tempProjectile.render(*target);
	}
	for (auto& tempProjectile : this->enemyProjectiles)
	{
		tempProjectile.render(*target);
	}
	for (auto& tempProjectile : this->bossProjectiles)
	{
		tempProjectile.render(*target);
	}
	for (int i = 0; i < activeEnemies.size(); i++)
	{
		this->activeEnemies[i]->render(*target);
	}

	// DRAWING UI
	target->setView(target->getDefaultView());
	target->draw(this->hp);
	target->draw(this->hpMaxBar);
	target->draw(this->hpCurBar);
	target->draw(this->hpText);
	target->draw(this->waveText);
	target->draw(this->enemiesText);
	target->draw(this->pauseButton);

}
