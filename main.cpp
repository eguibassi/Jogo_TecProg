#include <SFML/Graphics.hpp>
#include "entidades/Jogador.h"
using namespace Personagens;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste Jogador - Clash++");
    window.setFramerateLimit(60);

    Jogador jogador;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // AGORA CHAMAMOS O MÉTODO ORIGINAL DO UML
        jogador.executar();

        window.clear(sf::Color::Black);
        jogador.desenhar(&window);
        window.display();
    }

    return 0;
}