#pragma once
#include <SFML/Graphics.hpp>
#include <sstream> 

namespace Entidades {

    class Entidade {
    protected:
        int x;
        int y; 
        std::ostringstream buffer; 

       
        sf::Sprite sprite;
        sf::Texture* textura;

      
        sf::RectangleShape corpo;

    public:
        Entidade();
        virtual ~Entidade();

        void salvarDataBuffer();
        virtual void executar() = 0;
        virtual void salvar() = 0;

        virtual void desenhar(sf::RenderWindow* window);
        sf::RectangleShape getCorpo() const { return corpo; }
        
        void setPosicao(int novoX, int novoY) {
            x = novoX;
            y = novoY;
            corpo.setPosition((float)x, (float)y);
            // O Sprite acompanha o corpo
            sprite.setPosition((float)x, (float)y);
        }
        
        sf::Vector2f getPosicao() const { 
            return corpo.getPosition(); 
        }
    };

}