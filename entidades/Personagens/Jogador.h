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
        

    protected:
        int pontos;
        bool lento;

    public:
        Jogador(bool segundo_jogador = false);
        ~Jogador();
        
        void executar();
        void salvar();/*fazer*/
        void mover();/*arruumar bug do pulo*/
        Entidades::Projetil* atirar();

         
        int getPontos() const { return pontos; }
        Entidades::Projetil* getProjetil() const;

        
        void setLento(bool estado) { lento = estado; }
        bool getLento() const { return lento; }
        void setJogador2(bool a);
        const bool getJogador2()const;
     

    };

}