#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    private:
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

         
        int getPontos() const { return pontos; }

        
        void setLento(bool estado) { lento = estado; }
        bool getLento() const { return lento; }
     

    };

}