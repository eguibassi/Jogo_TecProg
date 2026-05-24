#include "Plataforma.h"

namespace Entidades {

    Plataforma::Plataforma() : altura(50) {
        x = 0;   
        y = 500; 
        
        corpo.setSize(sf::Vector2f(800.f, (float)altura)); 
        corpo.setPosition((float)x, (float)y);
        corpo.setFillColor(sf::Color(150, 150, 150)); 
    }

    Plataforma::~Plataforma() {
    }

    void Plataforma::executar() {
    }

    void Plataforma::salvar() {
    }

    void Plataforma::obstaculizar(Personagens::Jogador* p) {
        if (p == nullptr) return;

       
        // p->setSobAtrito(true);
        // p->setHspd(p->getHspd() * atrito);
    }

} // namespace Entidades