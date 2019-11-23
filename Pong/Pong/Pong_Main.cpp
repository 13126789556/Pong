#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
//#include "VectorCalculation.h"
#include "Ball.h"
#include "Paddle.h"
#include "UI.h"
#include "AudioResource.h"
#include "SpriteAnimation.h"
using namespace sf;

Vector2f winSize(750, 900);
Vector2f p1Size, p2Size, obSize, p1Pos, p2Pos, obPos, bhPos;
Vector2f ballDir, ballPos;
float ballRadius, ballSpeed, p1Speed, p2Speed, t, obSpeed, bhRadius;
int fps, frameCount, score1, score2;
bool isStartMenu;
bool isAIMode;
bool isTestMode;

float Magnitude(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}
	
Vector2f Normalize(Vector2f v) {
	return v / Magnitude(v);
}

Vector2f Lerp(Vector2f v1, Vector2f v2, float t) {
	if (t < 0) { t = 0; }
	if (t > 1) { t = 1; }
	return v1 * (1 - t) + v2 * t;
}


void Initial() {
	winSize = Vector2f(750, 900);
	p1Size = Vector2f(160, 25);
	p2Size = Vector2f(160, 25);
	obSize = Vector2f(130, 40);
	p1Pos = Vector2f(winSize.x / 2, p1Size.y * 1.5);
	p2Pos = Vector2f(winSize.x / 2, winSize.y - p1Size.y * 1.5);
	bhPos = Vector2f(winSize.x / 2 + 200, winSize.y / 2 + 200);
	obPos = Vector2f(obSize.x / 2, winSize.y / 2);
	ballPos = Vector2f(winSize.x / 2, winSize.y / 2);
	ballDir = Normalize(Vector2f(0, 1));
	ballSpeed = 550;
	p1Speed = 600;
	p2Speed = 600;
	obSpeed = 350;
	ballRadius = 25.0f;
	bhRadius = 100;
	score1 = 0;
	score2 = 0;
	isStartMenu = true;
	isAIMode = true;
	isTestMode = false;
}

int main()
{
	Initial();
	RenderWindow window(VideoMode(winSize.x, winSize.y), "Pong!");

	Ball ball(ballPos, ballDir, ballRadius, ballSpeed);
	Paddle player1(p1Pos, p1Size, p1Speed, Color(255, 0, 0, 255));
	Paddle player2(p2Pos, p2Size, p2Speed, Color(0, 255, 0, 255));
	Paddle obstacle(obPos, obSize, obSpeed, Color(0, 0, 255, 255));
	BlackHole blackHole(bhPos, bhRadius);
	
	SpriteAnimation anim("Sprite_Sheet_Test.png", 8, 1, 8);
	anim.speed = 0.3;
	SpriteAnimation kojima("kojima.png", 3, 3, 8);
	kojima.position = Vector2f(winSize.x / 2, winSize.y / 2);
	SpriteAnimation blackhole("blackhole.png", 5, 5, 24);
	blackhole.position = bhPos;

	AudioResource hit("Hit.wav");

	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Background_Texture.png");

	Sprite background;
	background.setTexture(backgroundTexture);

	UI fpsUI(20, Vector2f(winSize.x - 100, 0));
	UI score1UI(40, Vector2f(0, winSize.y / 2 - 60));
	score1UI.content = std::to_string(score1);
	UI score2UI(40, Vector2f(0, winSize.y / 2 + 10));
	score2UI.content = std::to_string(score2);
	UI winUI(50, Vector2f(winSize.x / 2 - 280, winSize.y / 2 - 75));
	UI menuUI(40, Vector2f(90, winSize.y / 2 - 75));
	menuUI.content = "Press a to play with AI\n\nPress b to play with human player\n\nPress t to test continuous";

	Time time, deltaTime;
	Clock fpsClock, fpsUpdate;

	while (window.isOpen())
	{
		//deltatime and fps
		deltaTime = fpsClock.getElapsedTime();	//time between two frame
		time += deltaTime;
		frameCount++;
		if (frameCount >= 10) {	//cauculate fps per 10 frame
			fps = frameCount / time.asSeconds();
			//fpsUI.setString("fps:" + std::to_string(fps));
			frameCount = 0;
			time = Time().Zero;
		}
		if (fpsUpdate.getElapsedTime().asSeconds() >= 0.1) {	//update fps per 0.1s
			fpsUI.content = "fps:" + std::to_string(fps);
			fpsUpdate.restart();
		}
		fpsClock.restart();

		//start menu
		if (isStartMenu) {
			deltaTime = Time().Zero;
			if (Keyboard::isKeyPressed(Keyboard::A) && deltaTime == Time().Zero) {
				player1.isAI = true;
				isStartMenu = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::B) && deltaTime == Time().Zero) {
				player1.isAI = false;
				isStartMenu = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::T) && deltaTime == Time().Zero) {
			player1.isAI = true;
			ballSpeed = 10000;
			ball.velocity = 10000;
			ball.direction = Vector2f(0, 1);
			obstacle.velocity = 0;
			isStartMenu = false; 
			}
		}

		//if win 
		if (score1 >= 5) {	//win detection
			deltaTime = Time().Zero;
			winUI.content = "			You Lose! \n\n press space to continue";
		}
		if (score2 >= 5) {	//win detection
			deltaTime = Time().Zero;
			winUI.content = "			You Win! \n\n press space to continue";
		}
		if (Keyboard::isKeyPressed(Keyboard::Space) && deltaTime == Time().Zero) {
			//score1 = score2 = 0;
			ball.direction = ballDir;
			player1.position = p1Pos;
			player2.position = p2Pos;
			obstacle.position = obPos;
			score1UI.content = std::to_string(score1 = 0);
			score2UI.content = std::to_string(score2 = 0);
			isStartMenu = true;
		}

		//ball collision detection
		if (winSize.x < ball.position.x + ball.radius) {	//ball hit right edge
			ball.position.x = winSize.x - ball.radius;
			ball.direction.x *= -1;
			hit.Play();
		}
		if (ball.position.x - ball.radius < 0) {	// ball hit left edge
			ball.position.x = ball.radius;
			ball.direction.x *= -1;
			hit.Play();
		}
		if (ball.Collision(player1)) {	//ball hit player1's paddle
			ball.velocity += 40.0f;
			hit.Play();
		}
		if (ball.Collision(player2)) {	//ball hit player2's paddle
			ball.velocity += 40.0f;
			hit.Play();
		}		
		if (ball.Collision(obstacle)) {	//ball hit obstacle
			hit.Play();
		}
		ball.InteractWithBlackHole(blackHole);

		//continuous collision
		if (ball.ContinuousCollision(player1, deltaTime.asSeconds())) {	//ball hit player1's paddle
			hit.Play();
		}
		if (ball.ContinuousCollision(player2, deltaTime.asSeconds())) {	//ball hit player2's paddle
			hit.Play();
		}
		
		//ball out of the table
		if (winSize.y < ball.position.y + ball.radius) {	//ball off bottom edge
			ball.position = Vector2f(winSize.x / 2, winSize.y / 2);
			ball.velocity = ballSpeed;
			obstacle.position = obPos;
			score1 += 1;
			score1UI.content = std::to_string(score1);
			//ball.position.y = winSize.y - ball.radius;
			//ball.direction.y *= -1;
		}
		if (ball.position.y - ball.radius < 0) {	//ball off top edge
			ball.position = Vector2f(winSize.x / 2, winSize.y / 2);
			ball.velocity = ballSpeed;
			obstacle.position = obPos;
			score2 += 1;
			score2UI.content = std::to_string(score2);
			//ball.position.y = ball.radius;
			//ball.direction.y *= -1;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Keyboard input
		if (player1.isAI == false) {
			if (Keyboard::isKeyPressed(Keyboard::A) && player1.size.x / 2 < player1.position.x) {
				player1.MoveLeft(deltaTime.asSeconds());
			}
			if (Keyboard::isKeyPressed(Keyboard::D) && player1.position.x < winSize.x - player1.size.x / 2) {
				player1.MoveRight(deltaTime.asSeconds());
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && player2.size.x / 2 < player2.position.x) {
			player2.MoveLeft(deltaTime.asSeconds());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && player2.position.x < winSize.x - player2.size.x / 2) {
			player2.MoveRight(deltaTime.asSeconds());
		}

		//ai behavior
		if (player1.isAI == true) {
			t += deltaTime.asSeconds();
			if (t > 1) {
				t = 0;
			}
			if (t + 0.02 > ball.position.y / winSize.y	//the ball farther, the paddle move lazier // t to controll
				&& ball.direction.y * (ball.position.y - player1.position.y) < 0	//detecte the ball move to ai's side or not
				&& abs(ball.position.x - player1.position.x) > player1.size.x / 2 - 40) {	//detecte the ball's x axis on ai's paddle or not 
				player1.UpdateByAI(deltaTime.asSeconds(), ball.position);	//ai move the paddle
				if (winSize.x - player1.size.x / 2 < player1.position.x) {	//ai hit the left edge of window
					player1.position.x = winSize.x - player1.size.x / 2;
				}
				if (player1.position.x < player1.size.x / 2) {	//ai hit the right edge of window
					player1.position.x = player1.size.x / 2;
				}
			}
		}

		//update obstacle
		if (obstacle.position.x <= obstacle.size.x / 2) {
			obstacle.direction = Vector2f(1, 0);
		}
		else if (winSize.x - obstacle.size.x / 2 <= obstacle.position.x) {
			obstacle.direction = Vector2f(-1, 0);
		}
		obstacle.position += obstacle.direction * obstacle.velocity * deltaTime.asSeconds();

		//update ball
		ball.Update(deltaTime.asSeconds());

		//test
		anim.Update(deltaTime.asSeconds());
		kojima.Update(deltaTime.asSeconds());
		blackhole.Update(deltaTime.asSeconds());

		window.clear(Color(0,0,0,0));
		//gameobject
		window.draw(background);
		blackhole.Draw(window);
		ball.Draw(window);
		player1.Draw(window);
		player2.Draw(window);
		obstacle.Draw(window);

		//test
		//anim.Draw(window);
		//kojima.Draw(window);

		//ui
		fpsUI.Draw(window);
		score1UI.Draw(window);
		score2UI.Draw(window);
		if (score1 >= 5 || score2 >= 5) {
			winUI.Draw(window);
		}
		if (isStartMenu) {
			menuUI.Draw(window);
		}
		window.display();
	}

	return 0;
}
