#include "Jogador.h"
#include <iostream> 

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Jogador::Jogador() : pontos(0),lento(false) {
        num_vidas = 5; 
        
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

      
        float velAtualX = VELOCIDADE_X_JOGADOR;
        if (lento) {
            velAtualX = VELOCIDADE_X_JOGADOR * 0.3f; 
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocidade.x = -velAtualX; 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocidade.x = velAtualX;  
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && velocidade.y == 0.f) {
            velocidade.y = FORCA_PULO; 
        }

        velocidade.y += GRAVIDADE; 

        corpo.move(velocidade);

        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);

        
        lento = false;
    }

    void Jogador::executar() {
        mover();
    }

    void Jogador::salvar() {
    }

    void Jogador::colidir() {
    }

   
    void Jogador::tomarDano(int dano) {
        num_vidas -= dano;
        std::cout << "Jogador caiu na lápide Vidas restantes: " << num_vidas << std::endl;
    }

} 