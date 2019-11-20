#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Paddle.h"
#include "BlackHole.h"
using namespace sf;

class Ball
{
public:
	Vector2f position, direction;
	float velocity, radius, originRadius;
	CircleShape ball;
	Texture texture;
	Sprite sprite;
	bool isContinuousCollided;

	Ball(Vector2f position, Vector2f direction, float radius, float velocity);
	void Update(float dt);
	bool Collision(Paddle p);
	bool ContinuousCollision(Paddle p, float dt);
	void InteractWithBlackHole(BlackHole blackHole);
	void Draw(RenderWindow& win);
};

