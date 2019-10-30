#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Ball.cpp"
#include "Paddle.cpp"
using namespace sf;

Vector2f winSize(600, 1000);
Vector2f p1Size, p2Size, p1Pos, p2Pos;
Vector2f ballDir, ballPos;
float ballRadius, ballSpeed, p1Speed, p2Speed;
int fps, frameCount;

Vector2f Normalize(Vector2f v) {
	float temp = sqrt(v.x * v.x + v.y * v.y);
	return Vector2f(v.x / temp, v.y / temp);
}

float Magnitude(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

void Initial() {
	winSize = Vector2f(600, 900);
	p1Size = Vector2f(160, 30);
	p2Size = Vector2f(160, 30);
	p1Pos = Vector2f(winSize.x / 2, p1Size.y * 1.5);
	p2Pos = Vector2f(winSize.x / 2, winSize.y - p1Size.y * 1.5);
	ballPos = Vector2f(winSize.x / 2, winSize.y / 2);
	ballDir = Normalize(Vector2f(1.0f, -1.0f));
	ballSpeed = 450;
	p1Speed = 400;
	p2Speed = 400;
	ballRadius = 25.0f;
}

bool Collide(Ball b, Paddle p) {
	Vector2f p1(p.position.x - p.size.x / 2, p.position.y - p.size.y / 2),
		p2(p.position.x + p.size.x / 2, p.position.y - p.size.y / 2),
		p3(p.position.x - p.size.x / 2, p.position.y + p.size.y / 2),
		p4(p.position.x + p.size.x / 2, p.position.y + p.size.y / 2);
	if (abs(b.position.x - p.position.x) < b.radius + p.size.x / 2
		&& abs(b.position.y - p.position.y) < b.radius + p.size.y / 2) {
		return true;
	}
	else if (Magnitude(b.position - p1) < b.radius
		|| Magnitude(b.position - p2) < b.radius
		|| Magnitude(b.position - p3) < b.radius
		|| Magnitude(b.position - p4) < b.radius) {
		return true;
	}
	return false;
}

int main()
{
	//Initial();
	RenderWindow window(VideoMode(winSize.x, winSize.y), "Pong");

	Ball ball(Vector2f(winSize.x / 2, winSize.y / 2), 
		Normalize(Vector2f(1.0f, -1.0f)), 
		25.0f, 450.f);
	Paddle player1(Vector2f(winSize.x / 2, 40.0f), 
		Vector2f(160.f, 30.f), 
		400.f);
	Paddle player2(Vector2f(winSize.x / 2, winSize.y - 40.0f), 
		Vector2f(160.0f, 30.0f), 
		400.f);


	Font font;
	font.loadFromFile("arial.ttf");

	Text fpsUI;
	fpsUI.setFont(font);
	fpsUI.setCharacterSize(20);
	fpsUI.setPosition(winSize.x - 70, 0);

	Time time, deltaTime;
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.getElapsedTime();	//time between two frame
		time += deltaTime;
		frameCount++;
		if (time.asSeconds() > 0.25) {	//cauculate fps
			fps = frameCount * 4;
			fpsUI.setString("fps:" + std::to_string(fps));
			frameCount = 0;
			time = Time().Zero;
		}
		clock.restart();


		if (winSize.x < ball.position.x + ball.radius) {
			ball.position.x = winSize.x - ball.radius;
			ball.direction.x *= -1;
		}		
		if (ball.position.x - ball.radius < 0) {
			ball.position.x = ball.radius;
			ball.direction.x *= -1;
		}
		//if (winSize.y < ball.position.y + ball.radius) {
		//	ball.position.y = winSize.y - ball.radius;
		//	ball.direction.y *= -1;
		//}
		//if (ball.position.y - ball.radius < 0) {
		//	ball.position.y = ball.radius;
		//	ball.direction.y *= -1;
		//}
		if (Collide(ball, player1)) {
			if (abs(ball.position.x - player1.position.x) < player1.size.x / 2) {
				//ball.position.y = player1.size.y / 2 + player1.position.y;
				ball.direction.y *= -1;
			}
			else if (abs(ball.position.y - player1.position.y) < player1.size.y / 2) {
				ball.direction.x *= -1;
			}
			else {
				ball.direction.x *= -1;
				ball.direction.y *= -1;
			}
		}
		if (Collide(ball, player2)) {
			if (abs(ball.position.x - player2.position.x) < player2.size.x / 2) {
				ball.direction.y *= -1;
			}
			else if (abs(ball.position.y - player2.position.y) < player2.size.y / 2) {
				ball.direction.x *= -1;
			}
			else {
				ball.direction.x *= -1;
				ball.direction.y *= -1;
			}
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::A) && player1.size.x / 2 < player1.position.x) {
			player1.MoveLeft(deltaTime.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && player1.position.x < winSize.x - player1.size.x / 2) {
			player1.MoveRight(deltaTime.asSeconds());
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && player2.size.x / 2 < player2.position.x) {
			player2.MoveLeft(deltaTime.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && player2.position.x < winSize.x - player2.size.x / 2) {
			player2.MoveRight(deltaTime.asSeconds());
		}
		//for (float i = 0; i < 0.2; i += deltaTime.asSeconds()) {
		//	ball.speed += 1;
		//}
		ball.Update(deltaTime.asSeconds());

		window.clear();
		ball.Draw(window);
		player1.Draw(window);
		player2.Draw(window);
		window.draw(fpsUI);
		window.display();
	}

	return 0;
}
