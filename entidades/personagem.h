#pragma once
#include <SFML/Graphics.hpp>
#include "Entidade.h" // Incluímos a nova classe base

namespace Personagens {

    // Personagem agora herda de Entidade!
    class Personagem : public Entidades::Entidade {
    protected:
        int num_vidas;
        
        sf::Vector2f velocidade; 

    public:
        Personagem();
        virtual ~Personagem();

        void salvarDataBuffer();
        
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
    };

} // namespace Personagens