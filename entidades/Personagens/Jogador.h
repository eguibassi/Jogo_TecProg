#pragma once
#include <SFML/Graphics.hpp>
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    protected:
        int pontos;
        bool lento;

    public:
        Jogador();
        ~Jogador();
        
        void executar();
        void mover() ;
        void salvar() ;
        
        void colidir(); 
        int getPontos() const { return pontos; }
        
      
        void tomarDano(int dano); 
        void setLento(bool estado) { lento = estado; }
        bool getLento() const { return lento; }
        void desenhar(sf::RenderWindow* window);
    };

}