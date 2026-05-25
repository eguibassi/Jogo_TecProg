#include "Inimigo.h"

#define VELOCIDADE_X_INIMIGO 2.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Inimigo::Inimigo() : nivel_maldade(1), pJogador(nullptr) {
        num_vidas = 3; 
        
        x = 600; 
        y = 100; 
        
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition((float)x, (float)y); 
        corpo.setFillColor(sf::Color::Red); 
    }

    Inimigo::~Inimigo() {
    }

    void Inimigo::mover() {
        velocidade.x = 0.f; /*Zera a velocidade horizontal a cada frame, para ele parar se não tiver um alvo */

        if (pJogador != nullptr) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();/*pegando a posição do jogador*/
            
            if (posJogador.x < x) { /*se o jogador está na esquerda vai para esquerda*/
                velocidade.x = -VELOCIDADE_X_INIMIGO; 
            } else if (posJogador.x > x) { /*se está na direita vai para direita*/
                velocidade.x = VELOCIDADE_X_INIMIGO;
            }
        }

        velocidade.y += GRAVIDADE; /*fica puxando ele para baixo*/
        
        corpo.move(velocidade); /*aplica as velocidades no corpo*/

        x = static_cast<int>(corpo.getPosition().x);  /*atualizando as variaveis*/
        y = static_cast<int>(corpo.getPosition().y);
        
      
    }

} 