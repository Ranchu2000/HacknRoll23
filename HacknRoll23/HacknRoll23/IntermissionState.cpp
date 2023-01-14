#include "IntermissionState.h"
#include "DEFINITIONS.h"

void IntermissionState::initVariables()
{
}

void IntermissionState::initFont()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void IntermissionState::initGui() //init GUI
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Background
	this->background.setSize(Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->background.setFillColor(Color(NAVY_COLOR));

	//title
	this->title.setFont(this->font);
	this->title.setCharacterSize(gui::calcCharSize(vm, 25));
	this->title.setFillColor(Color(GOLD_COLOR));
	this->title.setStyle(Text::Bold);
	this->title.setString("Wave Intermission");
	this->title.setPosition(gui::p2pX(50.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(5.f, vm));
	
	//next button
	this->nextBtn= new gui::Button(
		gui::p2pX(95.f, vm) - gui::p2pX(15.f, vm), gui::p2pY(95.f, vm) - gui::p2pY(10.f, vm),
		gui::p2pX(15.f, vm), gui::p2pY(10.f, vm),
		&this->font, "Next", gui::calcCharSize(vm, 40),
		sf::Color(PINK_COLOR), sf::Color(NAVY_COLOR),
		sf::Color(PURPLE_COLOR), sf::Color(PURPLE_COLOR));

}

void IntermissionState::resetGui() //reset UI
{
}

IntermissionState::IntermissionState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFont();
	this->initGui();
	this->resetGui();
}

IntermissionState::~IntermissionState()
{
}

void IntermissionState::updateInput(const float& dt)
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->text.setFont(this->font);
	this->text.setCharacterSize(gui::calcCharSize(vm, 40));
	this->text.setFillColor(Color(GOLD_COLOR));
	this->text.setStyle(Text::Regular);
	std::string info = "Points Available: " + std::to_string(this->upgradePoints);
	this->text.setString(info);
	this->text.setPosition(gui::p2pX(50.0f, vm) - this->text.getGlobalBounds().width / 2, gui::p2pY(20.f, vm));
}

void IntermissionState::updateButtons() //map buttons to functionality
{
	this->nextBtn->update(this->mousePosWindow);
	if (nextBtn->isPressed()) {
		//start new game state
		std::cout << "new game" << "\n";
		this->endState();
	}
}

void IntermissionState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}


void IntermissionState::render(sf::RenderTarget* target) //draw stuff
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->title);
	target->draw(this->text);
	for (auto& sprite : this->upgradeSprite) {
		target->draw(sprite.second);
	}
	for (auto& desc : this->upgradeDesc) {
		target->draw(desc.second);
	}
	for (auto& outline : this->upgradeOutline) {
		for (int i = 0;i < outline.second.size(); i++) {
			target->draw(outline.second[i]);
		}
	}for (auto& indicator : this->upgradeIndicator) {
		for (int i = 0;i < indicator.second.size(); i++) {
			target->draw(indicator.second[i]);
		}
	}
	this->nextBtn->render(*target);

}
