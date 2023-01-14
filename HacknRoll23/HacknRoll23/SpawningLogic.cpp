#include "DEFINITIONS.h"
#include "SpawningLogic.h"
#include "Player.h"

const sf::Vector2f RandomSpawning(float x, float y, sf::FloatRect playerBounds)
{
	std::srand(time(0));
	const sf::VideoMode& vm = sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
	float xpos = (rand() % (int)(40 * playerBounds.width)) + (x - 20 * playerBounds.width);
	float ypos = (rand() % (int)(40 * playerBounds.height)) + (y - 20 * playerBounds.height);;

	if (vectorDistance(xpos, ypos, x, y)
		< vectorDistance(gui::p2pX(50.f, vm), gui::p2pY(50.f, vm), x, y))
	{
		xpos += vectorDirection(Vector2f(xpos, ypos), Vector2f(x, y)).x * 400;
		ypos += vectorDirection(Vector2f(xpos, ypos), Vector2f(x, y)).y * 400;

	}
	return sf::Vector2f(xpos, ypos);
}
