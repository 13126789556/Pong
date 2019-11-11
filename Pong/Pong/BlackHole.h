#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
class BlackHole
{
public:
	Vector2f position;
	float radius;
	CircleShape circle;

	BlackHole(Vector2f position, float radius);
	void Draw(RenderWindow& win);
};

