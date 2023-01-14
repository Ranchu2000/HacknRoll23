#pragma once
#pragma once

#include<SFML/System.hpp>
#include<math.h>

const float vectorDistance(const float x1, const float y1, const float x2, const float y2);
const float vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2);

const sf::Vector2f vectorDirection(sf::Vector2f mousePos, sf::Vector2f entityPos);
const sf::Vector2f vectorDirection(sf::Vector2i mousePos, sf::Vector2f entityPos);
const sf::Vector2f vectorDirection(sf::Vector2f mousePos, sf::Vector2i entityPos); 