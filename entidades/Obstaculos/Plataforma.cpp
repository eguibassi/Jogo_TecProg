#include "Plataforma.h"

namespace Entidades {

    Plataforma::Plataforma() : altura(500), offset(0), pisadaFrame(false) {
        x = 0;   
        y = 500; 
        
        corpo.setSize(sf::Vector2f(150.f, 15.f)); 
        corpo.setPosition((float)x, (float)y);
        corpo.setFillColor(sf::Color(139, 0, 0));
    }

    Plataforma::~Plataforma() {
    }

    void Plataforma::setPosicao(int novoX, int novoY) {
        x = novoX;
        y = novoY;
        altura = novoY; /*salva o y original na altura*/
        offset = 0;
        corpo.setPosition((float)x, (float)y);
        sprite.setPosition((float)x, (float)y);
    }

    void Plataforma::setPisada() {
        pisadaFrame = true;
    }

    void Plataforma::executar() {
         
        if (pisadaFrame) {
            /*acumula o offset ate o limite de 30 pixels*/
            if (offset < 30) offset += 1;
        } else {
            /*sobe de volta quando ninguem estiver em cima*/
            if (offset > 0) offset -= 1;
        }

        pisadaFrame = false;

        y = altura + offset;
        corpo.setPosition((float)x, (float)y);
        sprite.setPosition((float)x, (float)y);
    }

    void Plataforma::salvar() {
    }

    void Plataforma::obstaculizar(Personagens::Jogador* pJog) {
        if (pJog == nullptr) return;

        sf::FloatRect rectJog  = pJog->getCorpo().getGlobalBounds();
        sf::FloatRect rectPlat = corpo.getGlobalBounds(); 

        float centroJogY  = rectJog.top  + rectJog.height  / 2.0f;
        float centroPlatY = rectPlat.top + rectPlat.height / 2.0f;

        /*ve se ta em baixo, esse eh o knockback*/
        if (centroJogY > centroPlatY) {
            sf::Vector2f velJog = pJog->getVelocidade();
            velJog.y = 4.0f; 
            pJog->setVelocidade(velJog);
        }
        /*colisao de cima eh tratada pelo gerenciador via setPisada()*/
    }
}