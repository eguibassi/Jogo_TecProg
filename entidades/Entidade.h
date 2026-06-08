#pragma once
#include <SFML/Graphics.hpp>
#include <sstream> 
#include "../Ente.h"
namespace Entidades {

    class Entidade : public Ente {
    protected:
        int x;
        int y; 
        std::ostringstream buffer; 

        sf::Sprite sprite;
        sf::Texture* textura;      
        sf::RectangleShape corpo;

        bool ativo;
    protected:
        void salvarDataBuffer();/*fazer,tirar duvida se passa pras outras*/
    public:
        Entidade();
        virtual ~Entidade();
        virtual void executar() = 0;
        virtual void salvar() = 0;
        
        bool getAtivo() const { return ativo; }
        void setAtivo(bool a) { ativo = a; }

        
        sf::RectangleShape& getCorpo()  { return corpo; }
        sf::Sprite& getSprite()  { return sprite; }

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