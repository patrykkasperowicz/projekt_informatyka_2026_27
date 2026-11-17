#pragma once
#include <SFML/Graphics.hpp>

class Pilka {
private:
	float x;
	float y;
	float vx;
	float vy;
	float radius;
	sf::CircleShape shape;

public:
	Pilka(float p_x, float p_y, float p_vx, float p_vy, float p_radius);
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	bool collidePaddle(const Paletka& p);
	void draw(sf::RenderTarget& target);
	float getX() const { return x; }
	float getY() const { return y; }
	float getVx() const { return vx; }
	float getVy() const { return vy; }
	float getRadius() const { return radius; }
};

Pilka::Pilka(float p_x, float p_y, float p_vx, float p_vy, float p_radius) {
	if (p_x >= 0 && p_x <= 640) {
		x = p_x;
	}
	else x = 100;

	if (p_y >= 0 && p_y <= 480) {
		y = p_y;
	}
	else y = 100;
	vx = p_vx;
	vy = p_vy;
	radius = p_radius;
	shape.setRadius(radius);
	shape.setOrigin({ radius, radius });
	shape.setPosition({ x, y });
	shape.setFillColor(sf::Color::White);
}

void Pilka::move() {
	x += vx;
	y += vy;
	shape.setPosition({ x, y });
}

void Pilka::bounceX() {
	vx = -vx;
}

void Pilka::bounceY() {
	vy = -vy;
}

void Pilka::collideWalls(float width, float height) {
	if (x - radius <= 0 || x + radius >= width) {
		bounceX();
	}
	if (y - radius <= 0) {
		bounceY();
	}
}

bool Pilka::collidePaddle(const Paletka& p) {
	float p_X = p.getX();
	float p_Y = p.getY();
	float p_szerokosc = p.getSzerokosc();
	float p_wysokosc = p.getWysokosc();

	if ((y + radius) >= (p_Y - p_wysokosc / 2) && x >= (p_X - p_szerokosc / 2) && x <= (p_X + p_szerokosc / 2)) {
		vy = -std::abs(vy);
		y = (p_Y - p_wysokosc / 2) - radius;
		shape.setPosition({ x, y });
		return true;
	}
	return false;
}

void Pilka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}
