#include <SFML/Graphics.hpp>
#include "entidades/Jogador.h"
#include "entidades/Inimigo.h" 

using namespace Personagens;


class Hog : public Inimigo {
public:
    Hog() {
       
    }

    
    void executar() override {
        mover();  
    }

    
    void danificar(Jogador* p) override {
       
    }
};

int main() {
    // Atualizei o nome da janela
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste Jogador e Inimigo - Clash++");
    window.setFramerateLimit(60);

    // Instancia o jogador
    Jogador jogador;

    // Instancia o inimigo de teste (Orc)
    Hog inimigoTeste;
    inimigoTeste.setJogador(&jogador); // Passamos a referência do jogador para o inimigo saber quem perseguir

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // AGORA CHAMAMOS O MÉTODO ORIGINAL DO UML PARA AMBOS
        jogador.executar();
        inimigoTeste.executar(); 

        window.clear(sf::Color::Black);
        
        // DESENHAMOS AMBOS
        jogador.desenhar(&window);
        inimigoTeste.desenhar(&window);
        
        window.display();
    }

    return 0;
}