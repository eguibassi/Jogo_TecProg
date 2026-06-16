#include "Inimigo.h"
#include <iostream>
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_INIMIGO 1.0f
#define GRAVIDADE 0.5f
#define DISTANCIA_SEGUIR_X 250.0f

namespace Personagens {

   Inimigo::Inimigo() : 
        nivel_maldade(1), 
        seguindoJogador(false), 
        direcao(1),
        pJogador(nullptr) 
    {
        num_vidas = 3; 
        
        x = 600; 
        y = 100; 
        
       
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition((float)x, (float)y);
        corpo.setFillColor(sf::Color::Transparent);  
        
        
    }

    Inimigo::~Inimigo() {
    }

    void Inimigo::mover() {
        velocidade.x = 0.f; /*Zera a velocidade horizontal a cada frame, para ele parar se não tiver um alvo */

        seguindoJogador = false;

        if (pJogador != nullptr) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();/*pegando a posição do jogador*/
            sf::Vector2f posJogador2 = pJogador2->getCorpo().getPosition();
            sf::Vector2f posInimigo = corpo.getPosition();

            float distanciaX = posJogador.x - posInimigo.x;

            if (distanciaX < 0.0f) {
                distanciaX = -distanciaX;
            }

            if (distanciaX <= DISTANCIA_SEGUIR_X && posJogador.y >= posInimigo.y) {
                seguindoJogador = true;

                if (posJogador.x < posInimigo.x) { /*se o jogador está na esquerda vai para esquerda*/
                    velocidade.x = -VELOCIDADE_X_INIMIGO; 
                } 
                else if (posJogador.x > posInimigo.x) { /*se está na direita vai para direita*/
                    velocidade.x = VELOCIDADE_X_INIMIGO;
                }
            }
        }

        if (!seguindoJogador) {
            if (relogioDirecaoAleatoria.getElapsedTime().asSeconds() >= 0.5f) {
                if (rand() % 10 > 5) {
                    direcao *= -1;
                }

                relogioDirecaoAleatoria.restart();
            }

            velocidade.x = VELOCIDADE_X_INIMIGO * direcao;
        }

        velocidade.y += GRAVIDADE; /*fica puxando ele para baixo*/
        
        corpo.move(velocidade); /*aplica as velocidades no corpo*/

        x = static_cast<int>(corpo.getPosition().x);  /*atualizando as variaveis*/
        y = static_cast<int>(corpo.getPosition().y);
    }

    bool Inimigo::getSeguindoJogador() const {return seguindoJogador;}
}