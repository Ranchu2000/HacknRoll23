#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

void MainMenuState::initVariables()
{
	this->initialStats["Attack"] = 0;
	this->initialStats["Health"] = 0;
	this->initialStats["Speed"] = 0;
	this->initialStats["Firing"] = 0;
	this->initialStats["Burn"] = 0;
	this->initialStats["Pierce"] = 0;
	this->initialWave = 0;
	this->gamesound = new GameSounds();
	this->gamesound->startGameMusic.play();
}

void MainMenuState::initFont()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void MainMenuState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Background
	this->background.setSize(Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
	this->background.setFillColor(Color(DARK_BLUE_COLOR));

	this->logoTexture.loadFromFile(TITLE_FILEPATH);
	this->logo.setTexture(this->logoTexture);
	this->logo.setPosition(gui::p2pX(8.f, vm), gui::p2pY(16.f, vm));

	this->instructionBackground.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->instructionBackground.setFillColor(Color(BROWN_COLOR));
	this->instructionBackground.setPosition(Vector2f(gui::p2pX(60.f,vm), 0.f));

	this->keyboardIconTexture.loadFromFile(KEYBOARD_ICON_FILEPATH);
	this->keyboardIcon.setTexture(this->keyboardIconTexture);
	this->keyboardIcon.setScale(1.5f, 1.5f);
	this->keyboardIcon.setPosition(gui::p2pX(62.f, vm), gui::p2pY(20.f, vm));

	this->mouseIconTexture.loadFromFile(MOUSE_ICON_FILEPATH);
	this->mouseIcon.setTexture(this->mouseIconTexture);
	this->mouseIcon.setScale(1.5f, 1.5f);
	this->mouseIcon.setPosition(gui::p2pX(62.f, vm), gui::p2pY(37.f, vm));

	//how2play
	this->how2play.setFont(this->font);
	this->how2play.setCharacterSize(gui::calcCharSize(vm, 38));
	this->how2play.setFillColor(Color(RED_COLOR));
	this->how2play.setStyle(Text::Bold);
	this->how2play.setString("How to Play:");
	this->how2play.setPosition(gui::p2pX(63.0f, vm), gui::p2pY(10.f, vm));

	this->how2playInstructions.setFont(this->font);
	this->how2playInstructions.setCharacterSize(gui::calcCharSize(vm, 70));
	this->how2playInstructions.setFillColor(Color(GREY_COLOR));
	this->how2playInstructions.setStyle(Text::Regular);
	this->how2playInstructions.setString("WASD keys are used \nto control character\n\nLeft mouse click to \nfire projectiles \nat enemies");
	this->how2playInstructions.setPosition(gui::p2pX(73.0f, vm), gui::p2pY(23.f, vm));

	//how2win
	this->how2win.setFont(this->font);
	this->how2win.setCharacterSize(gui::calcCharSize(vm, 38));
	this->how2win.setFillColor(Color(RED_COLOR));
	this->how2win.setStyle(Text::Bold);
	this->how2win.setString("How to Win:");
	this->how2win.setPosition(gui::p2pX(63.0f, vm), gui::p2pY(65.f, vm));

	this->how2winInstruction.setFont(this->font);
	this->how2winInstruction.setCharacterSize(gui::calcCharSize(vm, 70));
	this->how2winInstruction.setFillColor(Color(GREY_COLOR));
	this->how2winInstruction.setStyle(Text::Regular);
	this->how2winInstruction.setString("- Defeat enemies\n- Upgrade character\n- Survive 5 Waves\n- Get employed!");
	this->how2winInstruction.setPosition(gui::p2pX(62.0f, vm), gui::p2pY(75.f, vm));

	//Buttons
	float buttonWidth = 19.f;
	float buttonHeight = 10.f;

	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(20.f, vm), gui::p2pY(45.f, vm),
		gui::p2pX(buttonWidth, vm), gui::p2pY(buttonHeight, vm),
		&this->font, "Start", gui::calcCharSize(vm, 30),
		Color(GOLD_COLOR), Color(NAVY_COLOR), Color(GREY_COLOR), Color(GREY_COLOR));

	this->btnBG1.setSize(Vector2f(gui::p2pX(buttonWidth + 1.f, vm), gui::p2pY(buttonHeight + 1.2f, vm)));
	this->btnBG1.setPosition(gui::p2pX(20.f, vm), gui::p2pY(45.f, vm));
	this->btnBG1.setFillColor(Color(DARK_NAVY_COLOR));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(20.f, vm), gui::p2pY(70.f, vm),
		gui::p2pX(buttonWidth, vm), gui::p2pY(buttonHeight, vm),
		&this->font, "Quit", gui::calcCharSize(vm, 30),
		Color(GOLD_COLOR), Color(NAVY_COLOR),Color(GREY_COLOR), Color(GREY_COLOR));
	this->btnBG2.setSize(Vector2f(gui::p2pX(buttonWidth + 1.f, vm), gui::p2pY(buttonHeight + 1.2f, vm)));
	this->btnBG2.setPosition(gui::p2pX(20.f, vm), gui::p2pY(70.f, vm));
	this->btnBG2.setFillColor(Color(DARK_NAVY_COLOR));
}

void MainMenuState::resetGui() //reset UI
{
}

MainMenuState::MainMenuState(StateData* state_data) 
	: State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initGui();
	this->resetGui();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons() //map buttons to functionality
{
	for (auto& btn : this->buttons)
		btn.second->update(this->mousePosWindow);

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		//test
		this->gamesound->startGameMusic.stop();
		this->states->push(new GameState(this->stateData, this->initialStats, 0));
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		//test
		//this->states->push(new IntermissionState(this->stateData));
		this->gamesound->startGameMusic.stop();
		this->window->close();
		this->endState();// ensure everything ends
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& btn : this->buttons) {
		btn.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->logo);
	target->draw(this->instructionBackground);
	target->draw(this->btnBG1);
	target->draw(this->btnBG2);
	target->draw(this->how2play);
	target->draw(this->how2playInstructions);
	target->draw(this->how2win);
	target->draw(this->how2winInstruction);
	target->draw(this->mouseIcon);
	target->draw(this->keyboardIcon);
	this->renderButtons(*target);
}
