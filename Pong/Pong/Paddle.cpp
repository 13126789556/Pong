#pragma once

#include "Paddle.h"


	Paddle::Paddle(Vector2f position, Vector2f size, float velocity, Color color) {
		this->position = position;
		direction = Vector2f(0, 0);
		this->size = size;
		this->originSize = size;
		this->velocity = velocity;
		paddle.setOrigin(size.x / 2, size.y / 2);
		texture.loadFromFile("Paddle_Texture.png");
		sprite.setTexture(texture);
		sprite.setOrigin(90, 25);
		sprite.setColor(color);
	}

	void Paddle::MoveLeft(float dt) {
		position = position + Vector2f(-1, 0) * velocity * dt;
	}
	void Paddle::MoveRight(float dt) {
		position = position + Vector2f(1, 0) * velocity * dt;
	}

	void Paddle::UpdateByAI(float dt, Vector2f bPos) {
		if (bPos.x < position.x) {
			MoveLeft(dt);
		}
		else
		{
			MoveRight(dt);
		}
	}

	void Paddle::Draw(RenderWindow& win) {
		paddle.setSize(size);
		paddle.setPosition(position);
		sprite.setScale(size.x / 160, size.y / 30);
		sprite.setPosition(position);
		//win.draw(paddle);
		win.draw(sprite);
	}

	void Paddle::Collide(RectangleShape r) {

	}