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
        void executar() ;
        void mover() ;
        void salvar() ;
        
        
        void colidir(); 
        int getPontos() const { return pontos; }
    };

}