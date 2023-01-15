#include "ChallengeState.h"

void ChallengeState::initVariables()
{
}

void ChallengeState::initFonts()
{
	this->font.loadFromFile(PIXEL_FONT_FILEPATH);
}

void ChallengeState::initGui()
{
	const VideoMode& vm = VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(Color::Black);
	this->background.setPosition(0.f, 0.f);

	this->titleTex.loadFromFile(TITLE_FILEPATH);
	this->title.setTexture(titleTex);
	this->title.setPosition(gui::p2pX(60.0f, vm) - this->title.getGlobalBounds().width / 2, gui::p2pY(10.0f, vm) - this->title.getGlobalBounds().height / 2);

	this->logoTex.loadFromFile(LOGO_FILEPATH);
	this->logo.setTexture(logoTex);
	this->logo.setScale(1.75f, 1.75f);
	this->logo.setPosition(gui::p2pX(30.0f, vm) - this->logo.getGlobalBounds().width / 2, gui::p2pY(10.0f, vm) - this->logo.getGlobalBounds().height / 2);

	this->challenge.setFont(this->font);
	this->challenge.setCharacterSize(gui::calcCharSize(vm, 60));
	this->challenge.setFillColor(Color(RED_COLOR));
	this->challenge.setStyle(Text::Regular);
	this->challenge.setString("Due to an unprecedented turn of global events, a global tech \nwinter has occurred, where many tech companies have been \nforced to lay off employees and slow down hiring. \n\nYet, our young and bright Computer Science graduate, Timmy, \naspires to secure an internship from sponsors of HacknRoll \n2023. Guide Timmy as he earnestly submits his resume to\nimpress various companies and improve Timmy's chance of \nsecuring an internship by learning new frameworks.\n\nWill you take on the challenge to lead Timmy past the 5 waves\nand attain victory?");
	this->challenge.setPosition(gui::p2pX(5.0f, vm), gui::p2pY(20.f, vm));


	this->acceptBtn= new gui::Button(
		gui::p2pX(43.5f, vm), gui::p2pY(87.f, vm),
		gui::p2pX(18, vm), gui::p2pY(11.f, vm),
		&this->font, "Accept", gui::calcCharSize(vm, 35),
		Color(RED_COLOR), Color::White,
		Color::Black, Color::Black, Color(RED_COLOR));
}
void ChallengeState::resetGui()
{
	delete this->acceptBtn;
	this->initGui();
}

ChallengeState::ChallengeState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initGui();
	this->resetGui();
}

ChallengeState::~ChallengeState()
{
	delete this->acceptBtn;
}

void ChallengeState::updateInput(const float& dt)
{
	this->acceptBtn->update(this->mousePosWindow);
	if (this->acceptBtn->isPressed())
	{
		this->endState();
	}
}

void ChallengeState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
}

void ChallengeState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	target->draw(this->logo);
	target->draw(this->title);
	target->draw(this->challenge);
	this->acceptBtn->render(*target);
}