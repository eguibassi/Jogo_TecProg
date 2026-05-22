#pragma once
#include <SFML/Graphics.hpp>
#include "Jogador.h"

namespace Personagens {

    class Inimigo {
    protected:
        
        int nivel_maldade;

    private:
        // === ATRIBUTOS PROVISÓRIOS (Para podermos ver o inimigo na tela) ===
        sf::RectangleShape corpo;
        sf::Vector2f velocidade;
        Jogador* pJogador; 

    public:
        
        Inimigo();
        virtual ~Inimigo();
        
        void salvarDataBuffer();
        virtual void salva();
        void mover();

        
        virtual void executar() = 0;
        virtual void danificar(Jogador* p) = 0;

        //MÉTODOS PROVISÓRIOS (Para ajudar no teste) ===
        void desenhar(sf::RenderWindow* window);
        sf::RectangleShape getCorpo() const { return corpo; }
        
        // Método para passarmos a referência do jogador depois que o inimigo nascer
        void setJogador(Jogador* j) { pJogador = j; }
    };

} // namespace Personagens