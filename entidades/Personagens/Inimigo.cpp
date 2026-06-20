#include "Inimigo.h"
#include <iostream>
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_INIMIGO 1.0f
#define GRAVIDADE 0.5f
#define DISTANCIA_SEGUIR_X 250.0f
#define DISTANCIA_SEGUIR_Y 100.0f

namespace Personagens {

   Inimigo::Inimigo() : 
        nivel_maldade(1), 
        seguindoJogador(false), 
        direcao(1),
        pJogador(nullptr),
        pJogador2(nullptr)
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
        velocidade.x = 0.f;

        seguindoJogador = false;

        Jogador* alvo = nullptr;

        sf::Vector2f posInimigo = corpo.getPosition();

        float menorDistancia = DISTANCIA_SEGUIR_X + 1.0f;

        if (pJogador != nullptr && pJogador->getAtivo()) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();

            float distanciaX = posJogador.x - posInimigo.x;

            if (distanciaX < 0.0f) {
                distanciaX = -distanciaX;
            }

            float baseJogador = posJogador.y + pJogador->getCorpo().getSize().y;
            float baseInimigo = posInimigo.y + corpo.getSize().y;

            float distanciaY = baseJogador - baseInimigo;

            if (distanciaY < 0.0f) {
                distanciaY = -distanciaY;
            }

            if (distanciaX <= DISTANCIA_SEGUIR_X && distanciaY <= DISTANCIA_SEGUIR_Y) {
                alvo = pJogador;
                menorDistancia = distanciaX;
            }
        }

        if (pJogador2 != nullptr && pJogador2->getAtivo()) {
            sf::Vector2f posJogador2 = pJogador2->getCorpo().getPosition();

            float distanciaX = posJogador2.x - posInimigo.x;

            if (distanciaX < 0.0f) {
                distanciaX = -distanciaX;
            }

            float baseJogador2 = posJogador2.y + pJogador2->getCorpo().getSize().y;
            float baseInimigo = posInimigo.y + corpo.getSize().y;

            float distanciaY = baseJogador2 - baseInimigo;

            if (distanciaY < 0.0f) {
                distanciaY = -distanciaY;
            }

            if (distanciaX <= DISTANCIA_SEGUIR_X && distanciaY <= DISTANCIA_SEGUIR_Y && distanciaX < menorDistancia) {
                alvo = pJogador2;
                menorDistancia = distanciaX;
            }
        }

        if (alvo != nullptr) {
            sf::Vector2f posAlvo = alvo->getCorpo().getPosition();

            if (posAlvo.x < posInimigo.x) {
                velocidade.x = -VELOCIDADE_X_INIMIGO;
                seguindoJogador = true;
            } 
            else if (posAlvo.x > posInimigo.x) {
                velocidade.x = VELOCIDADE_X_INIMIGO;
                seguindoJogador = true;
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

        velocidade.y += GRAVIDADE;
        
        corpo.move(velocidade);

        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);
    }

    bool Inimigo::getSeguindoJogador() const {return seguindoJogador;}
    
    void Inimigo::salvarDataBuffer() {
        Personagem::salvarDataBuffer();

        buffer << nivel_maldade << " "
            << direcao << " ";
    }   
}