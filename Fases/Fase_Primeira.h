#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Pekka.h"
#include "../Entidades/Personagens/Goblin.h" 


namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxPekka;
        const int maxGoblin;
        sf::Texture texturaFundo;
        sf::Sprite spriteFundo;

    public:
        
        FasePrimeira(bool Jog2);
        ~FasePrimeira();

    protected:
        void criarInimigos();
        void criarObstaculo();
        void criarGoblin();
        void criarPekka();
        void criarPilha();
        void criarFundo();
        void desenharFundo();
        void criarPlataformas();
    };

}