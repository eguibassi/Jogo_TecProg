#include "Obstaculo.h"

#define GRAVIDADE 0.5f

namespace Entidades {

    Obstaculo::Obstaculo() : danoso(false), yBase(0), velocidadeY(0.f) {
        
        
        x = 300; 
        y = 550; 
        yBase = y;
        
        corpo.setSize(sf::Vector2f(200.f, 50.f));
        corpo.setPosition((float)x, (float)y); 
        
        
        corpo.setFillColor(sf::Color::Green); 
    }

    Obstaculo::~Obstaculo() {
    }

    void Obstaculo::salvarDataBuffer() {
        Entidade::salvarDataBuffer();

        buffer << danoso << " "
           << yBase << " "
           << velocidadeY << " ";
    }

    void Obstaculo::obstaculizar(Personagens::Jogador* p) {
        
    }

    void Obstaculo::aplicarGravidade() {
        velocidadeY += GRAVIDADE; /*fica puxando ele para baixo*/

        corpo.move(0.f, velocidadeY);

        y = static_cast<int>(corpo.getPosition().y);

        /*forca normal: nao deixa o objeto passar da posicao de repouso*/
        if (y > yBase) {
            y = yBase;
            velocidadeY = 0.f;
            corpo.setPosition((float)x, (float)y);
        }
    }

} 
