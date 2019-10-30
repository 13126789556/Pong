#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

class Paddle {
public:
	Vector2f size, position, direction;
	float speed;
	RectangleShape paddle;

	Paddle(Vector2f position, Vector2f size, float speed) {
		this->position = position;
		direction = Vector2f(0, 0);
		this->size = size;
		this->speed = speed;
	}

	void MoveLeft(float dt) {
		position = position + Vector2f(-1, 0) * speed * dt;
	}
	void MoveRight(float dt) {
		position = position + Vector2f(1, 0) * speed * dt;
	}

	void Draw(RenderWindow& win) {
		paddle.setSize(size);
		paddle.setOrigin(size.x / 2, size.y / 2);
		paddle.setPosition(position);
		win.draw(paddle);
	}
};