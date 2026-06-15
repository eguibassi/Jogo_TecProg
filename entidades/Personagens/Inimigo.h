#pragma once
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "personagem.h"
#include "Jogador.h"

namespace Personagens {

    class Inimigo : public Personagem {
    protected:
        int nivel_maldade;
        bool seguindoJogador;
        int direcao;
        sf::Clock relogioDirecaoAleatoria;

    private:
        Jogador* pJogador; 

    public:
        Inimigo();
        ~Inimigo();
        
        virtual void executar() = 0;
        virtual void danificar(Jogador* p) = 0;
        virtual void salvar() = 0; 
        
        void setJogador(Jogador* j) { pJogador = j; }
        void mover(); /*arrumar*/
        bool getSeguindoJogador() const;

        
        
       
    };

} 