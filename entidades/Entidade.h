#pragma once
#include <SFML/Graphics.hpp>
#include <sstream> 

namespace Entidades {

    class Entidade {
    protected:
        
        int x;
        int y; 
        std::ostringstream buffer; 

        // Atributo provisório (para o teste visual)
        sf::RectangleShape corpo;

    public:
        Entidade();
        virtual ~Entidade();

        void salvarDataBuffer();
        
        virtual void executar() = 0;
        virtual void salvar() = 0;

        virtual void desenhar(sf::RenderWindow* window);
        sf::RectangleShape getCorpo() const { return corpo; }
    };

} // namespace Entidades