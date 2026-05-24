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
        // Fixo no chão, apenas aguarda colisão
    }

    void ObstaculoLento::salvar() {
        // Gravará a posição da lama no futuro
    }

    void ObstaculoLento::obstaculizar(Personagens::Jogador* p) {
        // Quando o Gerenciador de Colisões avisar que o jogador pisou aqui:
        if (p != nullptr) {
            // p->aplicarAtrito(0.5f)
        }
    }

} 