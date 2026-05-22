#include "Personagem.h"

namespace Personagens {

    Personagem::Personagem() : num_vidas(1) {
        // Inicializa a velocidade zerada 
        velocidade = sf::Vector2f(0.f, 0.f);
    }

    Personagem::~Personagem() {
    }

    void Personagem::salvarDataBuffer() {
        // TODO futuramente
    }

}