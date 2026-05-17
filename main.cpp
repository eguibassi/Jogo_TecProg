#include <SFML/Graphics.hpp>

int main()
{
    // Cria a janela
    sf::RenderWindow window(sf::VideoMode(400, 400), "Meu Primeiro Jogo SFML!");

    // Cria um circulo verde
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100.f, 100.f);

    // Mantém a janela aberta até o usuário fechar
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}