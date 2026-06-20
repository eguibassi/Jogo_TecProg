#pragma once
#include "Fase.h"
#include "../Entidades/Personagens/Hog.h"
#include <list>

namespace Fases {

    class FaseSegunda : public Fase {
        private:
            const int maxJaula;
            const int maxHogs;

            sf::Texture texturaFundo;
            sf::Sprite spriteFundo;

            sf::Clock relogioProjetil;
            std::list<Personagens::Hog*> lisHogs;

        public:
        
            FaseSegunda(Personagens::Jogador* j1, Personagens::Jogador* j2, bool car = false);
            ~FaseSegunda();

            void executar();

            using Fase::incInimGC;
            void incInimGC(Personagens::Hog* hog);

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