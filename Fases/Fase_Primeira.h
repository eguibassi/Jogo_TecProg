#pragma once
#include "Fase.h"

namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxInimMedios;
        sf::Texture texturaFundo;
        sf::Sprite spriteFundo;

    public:
        
        FasePrimeira(Personagens::Jogador* pJog);
        ~FasePrimeira();

    protected:
        void criarInimigos();
        void criarObstaculo();
        void criarInimMedios();
        void criarObstMedios();
        void criarFundo();
        void desenharFundo();
    };

}