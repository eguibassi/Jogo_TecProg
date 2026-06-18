#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidade.h"

namespace Personagens {

    
    class Personagem : public Entidades::Entidade {
    protected:
        int num_vidas;
        
        sf::Vector2f velocidade; 

    public:
        Personagem();
        ~Personagem();

    
        
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;
        
        void setVelocidade(sf::Vector2f vel) { velocidade = vel; }
        sf::Vector2f getVelocidade() const { return velocidade; }
        void tomarDano(int dano);
    };

} 