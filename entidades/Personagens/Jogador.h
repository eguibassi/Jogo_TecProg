#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"
#include "../Projetil.h"

namespace Personagens {

    class Jogador : public Personagem { 
    private:
        Entidades::Projetil* pProjetil;
        bool podeAtirar;
        bool jogador2;
        bool vivo;

    protected:
        int pontos;
        bool lento;

    public:
        Jogador(bool segundo_jogador = false);
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
        void setJogador2(bool a);
        const bool getJogador2()const;
        bool getVivo() const;

    };

}