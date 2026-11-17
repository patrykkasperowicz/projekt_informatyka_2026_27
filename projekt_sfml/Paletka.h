#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float predkosc;
	sf::RectangleShape shape;

public:
	Paletka(float s_x, float s_y, float s_szerokosc, float s_wysokosc, float s_predkosc);
	void moveLeft();
	void moveRight();
	void clampToBounds(float width);
	void draw(sf::RenderTarget& target);
	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
};

Paletka::Paletka(float s_x, float s_y, float s_szerokosc, float s_wysokosc, float s_predkosc) {
	if (s_x >= 0 && s_x <= 640) {
		x = s_x;
	}
	else x = 100;

	if (s_y >= 0 && s_y <= 480) {
		y = s_y;
	}
	else y = 100;

	if (s_szerokosc > 0 && s_szerokosc <= 320) {
		szerokosc = s_szerokosc;
	}
	else szerokosc = 100;

	if (s_wysokosc > 0 && s_wysokosc <= 240) {
		wysokosc = s_wysokosc;
	}
	else wysokosc = 50;

	predkosc = s_predkosc;

	shape.setSize({ szerokosc, wysokosc });
	shape.setOrigin({ szerokosc / 2.f, wysokosc / 2.f });
	shape.setPosition({ x, y });
	shape.setFillColor(sf::Color::Green);
}

void Paletka::moveLeft() {
	x -= predkosc;
	shape.setPosition({ x, y });
}

void Paletka::moveRight() {
	x += predkosc;
	shape.setPosition({ x, y });
}

void Paletka::clampToBounds(float width) {
	if (x - szerokosc / 2 < 0) {
		x = szerokosc / 2;
	}

	if (x + szerokosc / 2 > width) {
		x = width - szerokosc / 2;
	}
	shape.setPosition({ x, y });
}

void Paletka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}