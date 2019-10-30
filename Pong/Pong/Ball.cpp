#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
//#include "Paddle.cpp"
using namespace sf;

class Ball {
public:
	Vector2f position, direction;
	float speed, radius;
	CircleShape ball;

	Ball(Vector2f position, Vector2f direction, float radius, float speed) {
		this->position = position;
		this->direction = direction;
		this->radius = radius;
		this->speed = speed;
	}

	void Update(float dt) {
		position = position + speed * direction * dt;
	}

	//bool CollideWithPaddle(Paddle p) {
	//	//Vector2f p1(p.position.x - p.size.x / 2, p.position.y - p.size.y / 2), 
	//	//	p2(p.position.x + p.size.x / 2, p.position.y - p.size.y / 2),
	//	//	p3(p.position.x - p.size.x / 2, p.position.y + p.size.y / 2),
	//	//	p4(p.position.x + p.size.x / 2, p.position.y + p.size.y / 2);
	//	if (abs(position.x - p.position.x) < radius + p.size.x / 2 
	//		&& abs(position.y - p.position.y) < radius + p.size.y / 2) {
	//		return true;
	//	}
	//	return false;
	//}

	void Draw(RenderWindow& win) {
		ball.setRadius(radius);
		ball.setOrigin(radius, radius);
		ball.setPosition(position);
		win.draw(ball);
	}
};