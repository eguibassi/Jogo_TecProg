#include "Jogador.h"

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define CHAO_Y 500.0f

namespace Personagens {

   Jogador::Jogador() : pontos(0) {
        num_vidas = 5; 
        
        // Nascimento do jogador (inteiros)
        x = 100; 
        y = 100; 
        
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition((float)x, (float)y); 
        corpo.setFillColor(sf::Color::Blue); 
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

        velocidade.y += 0.5f; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y >= CHAO_Y) {
            velocidade.y = FORCA_PULO; 
        }

        // 1. Movemos o corpo de forma suave com os floats
        corpo.move(velocidade);

        // 2. SINCRONIZAMOS x e y como int (estrito ao UML)
        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);

        // Colisão com o chão
        if (y >= CHAO_Y) {
            y = CHAO_Y; 
            corpo.setPosition((float)x, (float)y); // Ajusta o corpo
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

}