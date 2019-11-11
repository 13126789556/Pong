#include "BlackHole.h"
using namespace sf;

BlackHole::BlackHole(Vector2f position, float radius) {
	this->position = position;
	this->radius = radius;
	circle.setOrigin(radius, radius);
}

void BlackHole::Draw(RenderWindow& win) {
	circle.setRadius(radius);
	circle.setPosition(position);
	win.draw(circle);
}