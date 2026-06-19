#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Hog.h"

namespace Fases {

    class FaseSegunda : public Fase {
        private:
            const int maxJaula;
            const int maxHogs; // usado apenas na fórmula de quantidade aleatória

            sf::Texture texturaFundo;
            sf::Sprite spriteFundo;

            sf::Clock relogioProjetil;
            Personagens::Hog* pHogs[4];

        public:
        
            FaseSegunda(Personagens::Jogador* j1, Personagens::Jogador* j2, bool car = false);
            ~FaseSegunda();

            void executar();
            void incHogCar(Personagens::Hog* hog);

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