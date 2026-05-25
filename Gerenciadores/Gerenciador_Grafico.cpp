#include "Gerenciador_Grafico.h"

namespace Gerenciadores {

    
    Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

    Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
        if (instancia == nullptr) {
            instancia = new Gerenciador_Grafico();
        }
        return instancia;
    }

    Gerenciador_Grafico::Gerenciador_Grafico() {
       
        window = new sf::RenderWindow(sf::VideoMode(800, 600), "Clash++ - Singleton");
        window->setFramerateLimit(60);
    }

    Gerenciador_Grafico::~Gerenciador_Grafico() {
        
        for (auto it = texturas.begin(); it != texturas.end(); ++it) {
            delete it->second;
        }
        texturas.clear();

        if (window) {
            delete window;
            window = nullptr;
        }
    }

    sf::RenderWindow* Gerenciador_Grafico::getWindow() const {
        return window;
    }

    void Gerenciador_Grafico::limparJanela() {
        window->clear(sf::Color::Black);
    }

    void Gerenciador_Grafico::mostrarElementos() {
        window->display();
    }

    void Gerenciador_Grafico::fecharJanela() {
        if (window->isOpen()) {
            window->close();
        }
    }

    bool Gerenciador_Grafico::verificaJanelaAberta() {
        return window->isOpen();
    }

    void Gerenciador_Grafico::desenharElemento(sf::Sprite sprite) {
        window->draw(sprite);
    }

    void Gerenciador_Grafico::desenharElemento(sf::RectangleShape corpo) {
        window->draw(corpo);
    }

    sf::Texture* Gerenciador_Grafico::carregarTextura(const char* caminho) {
        
        if (texturas.find(caminho) != texturas.end()) {
            return texturas[caminho];
        }

       
        sf::Texture* novaTextura = new sf::Texture();
        if (!novaTextura->loadFromFile(caminho)) {
            std::cout << "ERRO::Nao foi possivel carregar a textura: " << caminho << std::endl;
            delete novaTextura;
            return nullptr;
        }

        // Guarda no dicionário para a próxima vez
        texturas[caminho] = novaTextura;
        return novaTextura;
    }

} 