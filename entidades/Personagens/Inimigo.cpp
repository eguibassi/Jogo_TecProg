#include "Inimigo.h"
#include <iostream>
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_INIMIGO 2.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Inimigo::Inimigo() : nivel_maldade(1), pJogador(nullptr) {
        num_vidas = 3; 
        
        x = 600; 
        y = 100; 
        
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition((float)x, (float)y);
        corpo.setFillColor(sf::Color::Transparent);  
        

        /*passando a imagem e desenhando ela*/
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Goblin.png");
        if(textura!=nullptr)
        {
            sprite.setTexture(*textura);
            sprite.setScale(0.102f,0.102f);// Ajustando a escala de 1254 para aprox 128 pixels (128 / 1254 = ~0.102)
            sprite.setPosition((float)x, (float)y);

        }
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
    void Inimigo::desenhar(sf::RenderWindow* window){
        if(textura!=nullptr)
            Gerenciadores::Gerenciador_Grafico::getInstancia()->desenharElemento(sprite);
        else
            std::cout<<"deu problema na imagem"<<std::endl;
    }
} 