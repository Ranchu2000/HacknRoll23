#include "imports.h"
#include "VectorMath.h"

const float vectorDistance(const float x1, const float y1, const float x2, const float y2)
{
	const float dx = x2 - x1;
	const float dy = y2 - y1;

	return sqrt(pow(dx, 2) + pow(dy, 2));
}

const float vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2)
{
	const sf::Vector2f dVec = vec2 - vec1;

	return sqrt(pow(dVec.x, 2) + pow(dVec.y, 2));
}

const sf::Vector2f vectorDirection(sf::Vector2f A, sf::Vector2f B)
{
	sf::Vector2f vec;
	vec.x = A.x - B.x;
	vec.y = A.y - B.y;

	float length = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return vec / length;
}

const sf::Vector2f vectorDirection(sf::Vector2i A, sf::Vector2f B)
{
	sf::Vector2f vec;

	vec.x = (A.x - B.x);
	vec.y = (A.y - B.y);

	float length = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return vec / length;
}

const sf::Vector2f vectorDirection(sf::Vector2f A, sf::Vector2i B)
{
	sf::Vector2f vec;
	vec.x = (A.x - B.x);
	vec.y = (A.y - B.y);

	float length = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return vec / length;
}

