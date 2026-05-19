/*#pragma once
#include <SFML/Graphics.hpp>
#include "Jogador.h"

namespace Personagens
{
    class Inimigo{
        protected:
            int nivel_maldade;
        private:
            sf::RectangleShape corpo;
            sf::Vector2f velocidade;
            int vida;
        public:
            Inimigo();
            ~Inimigo();
            void salvarDataBuffer();
            virtual void executar() = 0;
            virtual void danificar(Jogador* p) = 0;
            virtual void salva();
            void mover();
            void executar();
    };
}*/