#include <SFML/Graphics.hpp>
#include "jogador.h"

int main() {
    // Cria a janela de teste
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste Jogador - Clash++");
    window.setFramerateLimit(60);

    // Instancia o nosso jogador no meio da tela
    Jogador jogador(400.f, 300.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 1. Atualiza a lógica do jogador (física e input)
        jogador.atualiza();

        // 2. Limpa a tela
        window.clear(sf::Color::Black);
        
        // 3. Desenha o jogador
        jogador.desenhar(&window);
        
        // 4. Mostra na tela
        window.display();
    }

    return 0;
}