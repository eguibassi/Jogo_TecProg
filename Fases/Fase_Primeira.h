#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Pekka.h"

namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxInimMedios;
        sf::Texture texturaFundo;
        sf::Sprite spriteFundo;

    public:
        
        FasePrimeira(bool segundo_Jogador);
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