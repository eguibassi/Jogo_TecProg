#include "ObstaculoLento.h"

namespace Entidades {

    ObstaculoLento::ObstaculoLento() : largura(150.f) {
        danoso = false; 
        x = 150; 
        y = 490; 
        corpo.setSize(sf::Vector2f(largura, 10.f)); 
        corpo.setPosition((float)x, (float)y);
        
        
        corpo.setFillColor(sf::Color(139, 69, 19)); 
    }

    ObstaculoLento::~ObstaculoLento() {
    }

    void ObstaculoLento::executar() {
       
    }

    void ObstaculoLento::salvar() {
     
    }

void ObstaculoLento::obstaculizar(Personagens::Jogador* p) {
        if (p != nullptr) {
           
            p->setLento(true);
        }
    }

} 