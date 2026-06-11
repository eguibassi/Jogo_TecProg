#include "Jogador.h"
#include <iostream>

#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Jogador::Jogador(bool segundo_jogador) : pontos(0), lento(false), jogador2(segundo_jogador)
     {/*lento só é true quando estiver em contato com o Pilha*/
        num_vidas = 5; 
        corpo.setSize(sf::Vector2f(25.f, 50.f)); 
        corpo.setFillColor(sf::Color::Transparent);
        if(!jogador2){ 
            x = 100; /*posicoes iniciais*/
            y = 100;    
            textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Rei Azul.png");
        }
        else{
            x = 200; /*posicoes iniciais*/
            y = 100; 
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Rei Vermelho.png");
        }
        corpo.setPosition((float)x, (float)y);     
        if (textura != nullptr) {
                sprite.setTexture(*textura);
                sprite.setScale(0.1f, 0.1f); 
                sprite.setOrigin(0.0f,-75.0f);
                sprite.setPosition((float)x, (float)y);

            }
    }

    Jogador::~Jogador() {}
   
    /* sempre adiciono a gravidade ao jogador para que fique puxando ele pra baixo, se a velocidadeY for zero(está pisando em algo) pula no W adicionando um impulso negativo (pra cima)*/
    void Jogador::mover() {
        velocidade.x = 0.f;

        float velAtualX = VELOCIDADE_X_JOGADOR;
        if (lento) velAtualX = VELOCIDADE_X_JOGADOR * 0.3f; /*se tiver no obstaculo lento vai devagar*/

        if(!jogador2){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocidade.x = -velAtualX; /*esquerda*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocidade.x = velAtualX;  /*direita*/

            /* aqui o que comentei em cima da classe*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && velocidade.y == 0.f) {
            velocidade.y = FORCA_PULO; 
            }
        }
        else{
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) velocidade.x = -velAtualX; /*esquerda*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocidade.x = velAtualX;  /*direita*/

            /* aqui o que comentei em cima da classe*/
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && velocidade.y == 0.f) {
            velocidade.y = FORCA_PULO;     
            }
        }

        velocidade.y += GRAVIDADE; /*sempre atualizando Vy para puxar ele*/

        corpo.move(velocidade);/*move ele com base nas velocidades*/

        x = static_cast<int>(corpo.getPosition().x);   /*pegam as novas posicoes e salvam*/
        y = static_cast<int>(corpo.getPosition().y);

        sprite.setPosition((float)x, (float)y); /*atualiza posiçao da imagem*/

        lento = false;
    }   

    
    void Jogador::executar() {
        if (!ativo) return;
        mover();
    }

    void Jogador::salvar() {}


} 