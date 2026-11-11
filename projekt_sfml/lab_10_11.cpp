#include <SFML/Graphics.hpp>
#include <iostream>


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
	float getSzerokosc() const { return szerokosc;  }
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

//klasa Pi³ka

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

//bool Pilka::collidePaddle(const Paletka& p) {
//	float p_X = p.getX();
//	float p_Y = p.getY();
//	float p_szerokosc = p.getSzerokosc();
//	float p_wysokosc = p.getWysokosc();
//
//	if ((y + radius) >= (p_Y - p_wysokosc / 2) && (y - radius) < (p_Y - p_wysokosc / 2)) {
//		vy = -std::abs(vy);
//		vy = -std::abs(vy);
//		y = (p_Y - p_wysokosc / 2) - radius; shape.setPosition({ x, y });
//		return true;
//	}
//	else return false;
//}

bool Pilka::collidePaddle(const Paletka& p) {
	float p_X = p.getX();
	float p_Y = p.getY();
	float p_szerokosc = p.getSzerokosc();
	float p_wysokosc = p.getWysokosc();

	if ((y + radius) >= (p_Y - p_wysokosc / 2) &&
		x >= (p_X - p_szerokosc / 2) &&
		x <= (p_X + p_szerokosc / 2)) {

		vy = -std::abs(vy);
		y = (p_Y - p_wysokosc / 2) - radius;
		shape.setPosition({ x, y });
		return true;
	}
	return false;
}

void Pilka::draw(sf::RenderTarget & target) {
	target.draw(shape);
}

int main() {
	const float WIDTH = 640.f;
	const float HEIGHT = 480.f;
	sf::RenderWindow window(sf::VideoMode({ (unsigned)WIDTH, (unsigned)HEIGHT }), "Arkanoid test");
	window.setFramerateLimit(60);

	Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f);
	Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			pal.moveLeft();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			pal.moveRight();
		}
		pal.clampToBounds(WIDTH);

		pilka.move();
		pilka.collideWalls(WIDTH, HEIGHT);

		if (pilka.collidePaddle(pal)) {
			std::cout << "HIT PADDLE\n";
		}

		if (pilka.getY() - pilka.getRadius() > HEIGHT) {
			std::cout << "MISS! KONIEC GRY\n";
			window.close();
		}

		window.clear(sf::Color(20, 20, 30));
		pal.draw(window);
		pilka.draw(window);
		window.display();

		//std::cout << "x=" << pilka.getX() << " y=" << pilka.getY() << " vx=" << pilka.getVx() << " vy=" << pilka.getVy() << std::endl;
	}
}
