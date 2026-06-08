#include "Personagem.h"

namespace Personagens {

    Personagem::Personagem() : num_vidas(1) {
        // Inicializa a velocidade zerada 
        velocidade = sf::Vector2f(0.f, 0.f);
    }

    Personagem::~Personagem() {
    }

    void Personagem::tomarDano(int dano) {
        if (!ativo) return; // Se já está morto/inativo, ignora o dano

        num_vidas -= dano;
        std::cout << "Vidas restantes: " << num_vidas << std::endl;

        if (num_vidas <= 0) {
            ativo = false; // Desativa a entidade
            setPosicao(-9999, -9999); // Joga para fora da tela
            std::cout << "Personagem eliminado!" << std::endl;
        }
    }
    

}