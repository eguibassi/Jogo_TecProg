#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"
#include "../Projetil.h"

namespace Personagens {

    class Jogador : public Personagem { 
    private:
        Entidades::Projetil* pProjetil;
        bool podeAtirar;

    protected:
        int pontos;
        bool lento;

    public:
        Jogador();
        ~Jogador();
        void colidir();
        void executar();
        void salvar();
        void mover();
        Entidades::Projetil* atirar();

         
        int getPontos() const { return pontos; }
        Entidades::Projetil* getProjetil() const;

        void tomarDano(int dano); 
        void setLento(bool estado) { lento = estado; }
        bool getLento() const { return lento; }

    };

}