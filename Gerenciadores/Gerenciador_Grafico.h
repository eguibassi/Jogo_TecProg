#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
class Ente;

namespace Entidades {
    class Entidade; 
}

namespace Gerenciadores {

    class Gerenciador_Grafico {
    private:
        sf::RenderWindow* window;
        
        std::map<std::string, sf::Texture*> texturas;
        
        static Gerenciador_Grafico* instancia;

    public:
        Gerenciador_Grafico();
        ~Gerenciador_Grafico();
        void desenharEnte(Ente* pE);
        // Ponto de acesso global
        static Gerenciador_Grafico* getInstancia();

        
        sf::RenderWindow* getWindow() const;
        void limparJanela();
        void mostrarElementos();
        void fecharJanela();
        bool verificaJanelaAberta();

        void desenharForma(sf::RectangleShape& forma);
        

        
        sf::Texture* carregarTextura(const char* caminho);
    };

} 