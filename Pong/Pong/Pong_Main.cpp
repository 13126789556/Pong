#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;

Vector2f winSize(600, 1000);
Vector2f p1Size, p2Size, p1Pos, p2Pos;
Vector2f ballDir, ballPos;
float ballRadius, ballSpeed, p1Speed, p2Speed;
int fps, frame;

Vector2f Normalize(Vector2f v) {
	float temp = sqrt(v.x * v.x + v.y * v.y);
	return Vector2f(v.x / temp, v.y / temp);
}

void Initial() {
	winSize = Vector2f(600, 1000);
	p1Size = Vector2f(100, 20);
	p2Size = Vector2f(100, 20);
	p1Pos = Vector2f(winSize.x / 2, p1Size.y);
	p2Pos = Vector2f(winSize.x / 2, winSize.y - p1Size.y);
	ballPos = Vector2f(winSize.x / 2, winSize.y / 2);
	ballDir = Normalize(Vector2f(1.0f, -1.0f));
	ballRadius = 25.0f;
}

int main()
{
	Initial();
	RenderWindow window(VideoMode(winSize.x, winSize.y), "Pong");

	CircleShape ball(ballRadius);
	ball.setOrigin(ballRadius, ballRadius);
	ball.setPosition(ballPos);
	ball.setFillColor(Color::White);

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
		deltaTime = clock.getElapsedTime();
		time += deltaTime;
		frame++;
		if (time.asSeconds() > 0.2) {
			fps = frame * 5;
			fpsUI.setString("fps:" + std::to_string(fps));
			frame = 0;
			time = Time().Zero;
		}
		clock.restart();


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(ball);
		window.draw(fpsUI);
		window.display();
	}

	return 0;
}
