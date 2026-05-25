#include "ObstaculoDano.h"

namespace Entidades {

    ObstaculoDano::ObstaculoDano() {
        danosidade = 1; // Tira 1 ponto de vida
        danoso = true;  

     
        x = 400; 
        y = 480; 
        
      
        corpo.setSize(sf::Vector2f(20.f, 20.f)); 
        corpo.setPosition((float)x, (float)y);
        
      
        corpo.setFillColor(sf::Color(255, 165, 0)); 
    }

    ObstaculoDano::~ObstaculoDano() {
    }

    void ObstaculoDano::salvarDataBuffer() {
        
    }

    void ObstaculoDano::executar() {
        
    }

    void ObstaculoDano::salvar() {
        // Implementação obrigatória para salvar as posições
    }

    void ObstaculoDano::obstaculizar(Personagens::Jogador* p) {
        if (p != nullptr) {
            
            
            p->tomarDano(danosidade);

            
            sf::Vector2f velKnockback = p->getVelocidade();
            velKnockback.y = -10.0f; // Joga o jogador para cima
            
           
            if (p->getPosicao().x < this->x) {
                velKnockback.x = -10.0f; 
            } else {
                velKnockback.x = 10.0f;  
            }
            
            
            p->setVelocidade(velKnockback);
        }
    }

} // namespace Entidades