#include "ObstaculoDano.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

namespace Entidades {

    ObstaculoDano::ObstaculoDano() {
        danosidade = 1; // Tira 1 ponto de vida
        danoso = true;  

     
        x = 400; 
        y = 480; 
        
      
        corpo.setSize(sf::Vector2f(20.f, 20.f)); 
        corpo.setPosition((float)x, (float)y);
        
     textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Lapide.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);
            // Ajustando a escala de 1254 para aprox 128 pixels (128 / 1254 = ~0.102)
            sprite.setScale(0.102f, 0.102f); 
            sprite.setPosition((float)x, (float)y);
        }
        
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
            
            
            p->tomarDano(danosidade);/*chama o metodo do jogador para diminuir a vida*/

            
            sf::Vector2f velKnockback = p->getVelocidade();/*velocidade do jogador*/
            velKnockback.y = -10.0f; /*joga ele pra cima*/
            
           
            if (p->getPosicao().x < this->x) { /*se o jogador estiver a esquerda joga ele mais pra esquerda*/
                velKnockback.x = -10.0f; 
            } else {
                velKnockback.x = 10.0f;  /* se estiver para direita joga ele mais para direita*/
            }
            
            
            p->setVelocidade(velKnockback); /*aplica a nova velocidade no jogador*/
        }
    }


} 