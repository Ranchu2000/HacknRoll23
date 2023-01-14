#include "IntermissionState.h"
#include "DEFINITIONS.h"

void IntermissionState::initVariables()
{
	//initialise upgradeTextures
	Texture tex; 
	tex.loadFromFile(ATTACK_FILEPATH);
	this->upgradeTextures["Attack"] = tex;
	tex.loadFromFile(HEALTH_FILEPATH);
	this->upgradeTextures["Health"] = tex;
	tex.loadFromFile(SPEED_FILEPATH);
	this->upgradeTextures["Speed"] = tex;
	tex.loadFromFile(FIRING_FILEPATH);
	this->upgradeTextures["Firing"] = tex;
	tex.loadFromFile(BURN_FILEPATH);
	this->upgradeTextures["Burn"] = tex;
	tex.loadFromFile(PIERCE_FILEPATH);
	this->upgradeTextures["Pierce"] = tex;

	//initialise upgradeIndex
	int idx = 0;
	for (auto& it : this->upgradeTextures) { //index textures according to their arrangement in the map
		idx++;
		this->upgradeIndex[it.first] = idx;
	}
	//initialise UpgradeDescription
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	Text description;
	description.setFont(this->font);
	description.setCharacterSize(gui::calcCharSize(vm, 95));
	description.setFillColor(Color::White);
	description.setStyle(Text::Regular);
	description.setString("Increase Damage");
	this->upgradeDesc["Attack"] = description;
	description.setString("Increase Health");
	this->upgradeDesc["Health"] = description;
	description.setString("Increase Speed");
	this->upgradeDesc["Speed"] = description;
	description.setString("Increase Fire Rate");
	this->upgradeDesc["Firing"] = description;
	description.setString("Flaming Projectiles");
	this->upgradeDesc["Burn"] = description;
	description.setString("Piercing Projectiles");
	this->upgradeDesc["Pierce"] = description;
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

	//upgrade content
	size_t idx = 0;
	for (auto& nameTextures : this->upgradeTextures) {
		++idx;
		Sprite spr;
		spr.setTexture(nameTextures.second);
		spr.setScale(0.2f, 0.2f);
		if (idx <= 3) {
			spr.setPosition(gui::p2pX(15.f, vm) - spr.getGlobalBounds().width / 2, gui::p2pY(25.f, vm) - spr.getGlobalBounds().height + idx * gui::p2pY(18.f, vm));
			this->upgradeDesc[nameTextures.first].setPosition(gui::p2pX(15.f, vm) - this->upgradeDesc[nameTextures.first].getGlobalBounds().width / 2, gui::p2pY(26.f, vm) + idx * gui::p2pY(18.f, vm));
		}
		else {
			spr.setPosition(gui::p2pX(58.f, vm) - spr.getGlobalBounds().width / 2, gui::p2pY(25.f, vm) - spr.getGlobalBounds().height + (idx - 3) * gui::p2pY(18.f, vm));
			this->upgradeDesc[nameTextures.first].setPosition(gui::p2pX(58.f, vm) - this->upgradeDesc[nameTextures.first].getGlobalBounds().width / 2, gui::p2pY(26.f, vm) + (idx - 3) * gui::p2pY(18.f, vm));
		}
		upgradeSprite[nameTextures.first] = spr;

	}
}

void IntermissionState::resetGui() //reset UI
{
}

IntermissionState::IntermissionState(StateData* state_data)
	: State(state_data)
{
	this->initFont();//initialise font so initvariable can use
	this->initVariables();
	
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
