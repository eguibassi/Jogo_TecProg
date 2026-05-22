#include "Jogador.h"

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define CHAO_Y 500.0f


namespace Personagens {

    Jogador::Jogador() : pontos(0), vida(5) {
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition(100.f, 100.f); 
        corpo.setFillColor(sf::Color::Blue); 
        velocidade = sf::Vector2f(0.f, 0.f);
    }

    Jogador::~Jogador() {
    }

    void Jogador::mover() {
        velocidade.x = 0.f;

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocidade.x = -VELOCIDADE_X_JOGADOR; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocidade.x = VELOCIDADE_X_JOGADOR;  
        }

        // Aplica a gravidade constante
        velocidade.y += 0.5f; 

        
        // O jogador só pode pular se o y dele for maior ou igual ao chão.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && corpo.getPosition().y >= CHAO_Y) {
            velocidade.y = FORCA_PULO; 
        }

        // Move o corpo depois de calcular tudo
        corpo.move(velocidade);

        // Se passar do chão ou estiver nele zera a velocidade de queda
        if (corpo.getPosition().y >= CHAO_Y) {
            corpo.setPosition(corpo.getPosition().x, CHAO_Y);
            velocidade.y = 0.f; 
        }
    }

    void Jogador::executar() {
        mover();
    }

    void Jogador::salvar() {
    }

    void Jogador::colidir() {
    }

    void Jogador::desenhar(sf::RenderWindow* window) {
        if (window) {
            window->draw(corpo);
        }
    }

} // namespace Personagens