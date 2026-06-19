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
        
        FasePrimeira(Personagens::Jogador* j1, Personagens::Jogador* j2, bool car = false);
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