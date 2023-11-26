#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

namespace GV {
	const std::string TITLE = "AABB COLLISION";
	const sf::Vector2i WINDOWSIZE = sf::Vector2i{ 800, 600 };

	constexpr int SHAPESIZE = 100;
	constexpr float VELOCITY = 100.f;
	constexpr float ACCELERATION = 5.f;

	const sf::Color SHAPECOLOR= sf::Color::White;
}