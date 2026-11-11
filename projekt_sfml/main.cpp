#include <SFML/Graphics.hpp>

int main3()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rysunek!");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    sf::RectangleShape prostokat(sf::Vector2f(200, 100));
    prostokat.setFillColor(sf::Color::Red);
    prostokat.setPosition({ 300, 400 });

    sf::CircleShape kolo(50);
    kolo.setFillColor(sf::Color::Blue);
    kolo.setPosition({ 600, 50 });

    sf::ConvexShape trojkat;
    trojkat.setOutlineThickness(10.f);
    trojkat.setOutlineColor(sf::Color(250, 150, 100));
    trojkat.setPointCount(3);
    trojkat.setPoint(0, sf::Vector2f(400, 300));
    trojkat.setPoint(1, sf::Vector2f(500, 150));
    trojkat.setPoint(2, sf::Vector2f(600, 300));
    trojkat.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(prostokat);
        window.draw(kolo);
        window.draw(trojkat);
        window.display();
    }
}