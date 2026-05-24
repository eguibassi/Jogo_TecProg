#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    protected:
        int pontos;

    public:
        Jogador();
        ~Jogador();
        
        void executar() override;
        void mover() override;
        void salvar() override;
        
        void colidir(); 
        int getPontos() const { return pontos; }
    };

}