#include <SFML/Graphics.hpp>

int main2()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Rysunek2!");

    sf::RectangleShape dom(sf::Vector2f(200, 100));
    dom.setFillColor(sf::Color::Blue);
    dom.setPosition({ 300, 400 });

    sf::ConvexShape dach;
    dach.setPointCount(3);
    dach.setPoint(0, sf::Vector2f(300, 400));
    dach.setPoint(1, sf::Vector2f(500, 400));
    dach.setPoint(2, sf::Vector2f(400, 250));
    dach.setFillColor(sf::Color::Red);

    sf::RectangleShape drzewo(sf::Vector2f(50, 200));
    drzewo.setFillColor(sf::Color(sf::Color(139, 69, 19)));
    drzewo.setPosition({ 600, 300 });

    sf::CircleShape korona(100.f);
    korona.setFillColor(sf::Color::Green);
    korona.setPosition({ 525, 150 });

    sf::RectangleShape trawa(sf::Vector2f(800, 600));
    trawa.setFillColor(sf::Color::Green);
    trawa.setPosition({ 0, 480 });

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Cyan);
        window.draw(dach);
        window.draw(dom);
        window.draw(drzewo);
        window.draw(korona);
        window.draw(trawa);
        window.display();
    }
}