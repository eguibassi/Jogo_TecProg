#include "Obstaculo.h"

namespace Entidades {

    Obstaculo::Obstaculo() : danoso(false) {
        
        
        x = 300; 
        y = 550; 
        
        
        corpo.setSize(sf::Vector2f(200.f, 50.f));
        corpo.setPosition((float)x, (float)y); 
        
        
        corpo.setFillColor(sf::Color::Green); 
    }

    Obstaculo::~Obstaculo() {
    }

    void Obstaculo::salvarDataBuffer() {
        
    }

    void Obstaculo::obstaculizar(Personagens::Jogador* p) {
        
    }

} 