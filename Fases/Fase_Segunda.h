#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Hog.h"

namespace Fases {

    class FaseSegunda : public Fase {
            const int maxJaula;
            const int maxHogs; // usado apenas na fórmula de quantidade aleatória

            sf::Texture texturaFundo;
            sf::Sprite spriteFundo;

            sf::Clock relogioProjetil;
            Personagens::Hog* pHogs[4];

        public:
        
            FaseSegunda(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2);
            ~FaseSegunda();

            void executar();

        protected:
            void criarInimigos();
            void criarObstaculo();
            void criarHogs();
            void criarJaulas();
            void criarProjetil();

            void criarFundo();
            void desenharFundo();
    };

}