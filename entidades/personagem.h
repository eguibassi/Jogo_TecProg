#pragma once
#include <SFML/Graphics.hpp>

namespace Personagens {

    class Personagem {
    protected:
        // Original do seu esboço
        int num_vidas;

        // Movido das classes filhas para cá
        sf::RectangleShape corpo;
        sf::Vector2f velocidade;

    public:
        Personagem();
        virtual ~Personagem();

        void salvarDataBuffer();
        
        // Virtuais puras
        virtual void executar() = 0;
        virtual void salvar() = 0;
        virtual void mover() = 0;

        void desenhar(sf::RenderWindow* window);
        sf::RectangleShape getCorpo() const { return corpo; }
    };

} // namespace Personagens