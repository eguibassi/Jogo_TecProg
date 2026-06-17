#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Pekka.h"
#include "../Entidades/Personagens/Goblin.h" 


namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxPekka;
        const int maxPilha;
        
        sf::Texture texturaFundo;
        sf::Sprite spriteFundo;

    public:
        
        FasePrimeira(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2);
        ~FasePrimeira();

    protected:
        void criarInimigos();
        void criarObstaculo();
        
        void criarPekka();
        void criarPilha();
        void criarFundo();
        void desenharFundo();
    };

}