#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Pekka.h"
#include "../Entidades/Personagens/Goblin.h" 


namespace Fases {

    class FasePrimeira : public Fase {
    private:
        const int maxInimMedios;
        const int maxInimFaceis;
        sf::Texture texturaFundo;
        sf::Sprite spriteFundo;

    public:
        
        FasePrimeira(Personagens::Jogador* pJog);
        ~FasePrimeira();

    protected:
        void criarInimigos();
        void criarObstaculo();
        void criarInimFaceis();
        void criarInimMedios();
        void criarObstMedios();
        void criarFundo();
        void desenharFundo();
    };

}