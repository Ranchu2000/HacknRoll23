#include "Gui.h"
#include "imports.h"

const float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

bool gui::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(button)) {
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempRect.contains(sf::Mouse::getPosition(window))) {
			return true;
		}
	}
	return false;
}

gui::Button::Button(float x, float y, float width, float height,
	Font* font, std::string text, unsigned character_size,
	Color text_idle_color, Color text_hover_color,
	Color idle_color, Color hover_color,
	Color outline_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height * 3 / 5.f) - this->text.getGlobalBounds().height);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;

	this->outlineColor = outline_color;
}

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_color, sf::Color text_hover_color, sf::Color box_color, short unsigned id)
{//selection of the button is determined by the height and width
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(box_color);
	this->shape.setOutlineThickness(1.f);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_color);
	this->text.setCharacterSize(character_size);


	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f - 1.f,
		this->shape.getPosition().y - this->text.getGlobalBounds().height + 25.5f);
	this->textIdleColor = text_color;
	this->textHoverColor = text_hover_color;
	this->idleColor = box_color;
	this->hoverColor = box_color;
	this->outlineColor = box_color;;
}


gui::Button::~Button()
{

}

//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

