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
        // Grava os dados do buffer
    }

    void ObstaculoDano::executar() {
        // Como é fixo no chão, não tem movimento. 
        // Ele apenas existe no game loop.
    }

    void ObstaculoDano::salvar() {
        // Implementação obrigatória para salvar as posições
    }

    void ObstaculoDano::obstaculizar(Personagens::Jogador* p) {
        
        // Quando o Gerenciador de Colisões avisar que bateu aqui, tiramos a vida do jogador.
        
        if (p != nullptr) {
            // Como a vida lá no Jogador (via Personagem) é protected, 
            // no futuro teremos que criar um "tomarDano(int)" no Jogador.
            // Para deixar a estrutura preparada, faríamos assim:
            // p->tomarDano(danosidade);
        }
    }

} // namespace Entidades