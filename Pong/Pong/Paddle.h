#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
//#include "Ball.h"
using namespace sf;
class Paddle {
public:
	Vector2f size, originSize, position, direction;
	float speed;
	RectangleShape paddle;
	bool isAI = false; 
	Texture texture;
	Sprite sprite;

	Paddle(Vector2f position, Vector2f size, float speed, Color color);
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void UpdateByAI(float dt, Vector2f bPos);
	void Draw(RenderWindow& win);
	void Collide(RectangleShape r);
};
