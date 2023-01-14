#ifndef GUI_H
#define GUI_H
#include"imports.h"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	//convert between pixel and percentages
	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);

	//calculate appropriate character size
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 60);


	bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		RectangleShape shape;
		Font* font;
		Text text;

		Color textIdleColor;
		Color textHoverColor;
		Color idleColor;
		Color hoverColor;
		Color outlineColor;

	public:
		Button(float x, float y, float width, float height,
			Font* font, std::string text, unsigned character_size,
			Color text_idle_color, Color text_hover_color,
			Color idle_color, Color hover_color,
			Color outline_color = Color::Transparent,
			short unsigned id = 0);

		Button(float x, float y, float width, float height,
			Font* font, std::string text, unsigned character_size,
			Color text_color, Color text_hover_color, Color box_color, short unsigned id = 0);

		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};


};
#endif