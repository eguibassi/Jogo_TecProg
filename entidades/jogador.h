#pragma once
#include <SFML/Graphics.hpp>
namespace Personagens{
    
    class Jogador {
    private:

        int pontos;

        sf::RectangleShape corpo;
        sf::Vector2f velocidade;
        int vida;

    public:

        Jogador();
        ~Jogador();
    
        void executar();
        void mover();
        void salvar();
        void colidir(); 
    

    
        void desenhar(sf::RenderWindow* window);
    
        int getPontos() const { return pontos; }
        sf::RectangleShape getCorpo() const { return corpo; }
    };
}