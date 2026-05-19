/*#pragma once
#include <SFML/Graphics.hpp>
namespace Personagens{
    class Personagem{
        protected:
            int num_vidas;
            sf::Sprite sprite;
        public:
            Personagem();
            ~Personagem();
            void salvarDataBuffer();
            virtual void executar() = 0;
            virtual void salvar() = 0;
            virtual void mover() = 0;
            void setPosicao(float x, float y);
            sf::Vector2f getPosicao() const;
        private:
            sf::Vector2f posicao;
    };
}*/