#pragma once
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    protected:
        int pontos;

    public:
        Jogador();
        ~Jogador();
        
        // Sobrescrevendo as funções virtuais da classe pai
        void executar() override;
        void mover() override;
        void salvar() override;
        
        
        void colidir(); 
        int getPontos() const { return pontos; }
    };

}