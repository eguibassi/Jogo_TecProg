#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

namespace Gerenciadores {

    class Gerenciador_Grafico {
    private:
        sf::RenderWindow* window;
        
        
        std::map<std::string, sf::Texture*> texturas;
        
        
        static Gerenciador_Grafico* instancia;

        
        Gerenciador_Grafico();

    public:
        ~Gerenciador_Grafico();
        
        // Ponto de acesso global
        static Gerenciador_Grafico* getInstancia();

        
        sf::RenderWindow* getWindow() const;
        void limparJanela();
        void mostrarElementos();
        void fecharJanela();
        bool verificaJanelaAberta();

        
        void desenharElemento(sf::Sprite sprite);
        void desenharElemento(sf::RectangleShape corpo); 

        
        sf::Texture* carregarTextura(const char* caminho);
    };

} 