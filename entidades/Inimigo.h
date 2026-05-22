#pragma once
#include "Personagem.h"
#include "Jogador.h"

namespace Personagens {

    class Inimigo : public Personagem { // <--- INDICANDO A HERANÇA
    protected:
        int nivel_maldade;

    private:
        Jogador* pJogador; 

    public:
        Inimigo();
        virtual ~Inimigo();
        
        // Específico de Inimigo
        virtual void danificar(Jogador* p) = 0;
        void setJogador(Jogador* j) { pJogador = j; }

        // Sobrescrevendo as funções virtuais da classe pai Personagem
        // (Lembre-se que executar continua abstrata no Inimigo)
        virtual void executar() = 0; 
        void mover() override;
        void salvar() override; 
    };

}