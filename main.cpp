#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Inimigo.h"

using namespace Personagens;


class Hog : public Inimigo {
public:
    Hog() {}

    void executar() override {
        mover(); 
    }

    void danificar(Jogador* p) override {
    }

   
    void salva() override {
    }

    
    void salvar() override {
    }
};

int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste Jogador e Inimigo - Clash++");
    window.setFramerateLimit(60);

    // Instancia o jogador
    Jogador jogador;

    
    Hog inimigoTeste;
    inimigoTeste.setJogador(&jogador); // Passamos a referência do jogador para o inimigo saber quem perseguir

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
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