#include "Gerenciador_Grafico.h"
#include "../Ente.h"
#include "../Entidades/Entidade.h"
/*implementar singleton*/
namespace Gerenciadores {

    Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

    Gerenciador_Grafico::Gerenciador_Grafico() {
        window = new sf::RenderWindow(sf::VideoMode(800, 600), "Clash++");
        window->setFramerateLimit(60);
        
        instancia = this; 
        Ente::setGG(this);
    }

    Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
        return instancia;
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

    sf::RenderWindow* Gerenciador_Grafico::getWindow() const { return window; }
    void Gerenciador_Grafico::limparJanela() { window->clear(sf::Color::Black); }
    void Gerenciador_Grafico::mostrarElementos() { window->display(); }
    
    void Gerenciador_Grafico::fecharJanela() {
        if (window->isOpen()) {
            window->close();
        }
    }

    bool Gerenciador_Grafico::verificaJanelaAberta() { return window->isOpen(); }
    void Gerenciador_Grafico::desenharEnte(Ente* pE) {
        if (!pE) return;

        
        Entidades::Entidade* pEntidade = dynamic_cast<Entidades::Entidade*>(pE);
        
    
        if (pEntidade && pEntidade->getAtivo()) {
            if (pEntidade->getSprite().getTexture() != nullptr) {
                window->draw(pEntidade->getSprite());
            } 
            else {
                window->draw(pEntidade->getCorpo());
            }
        }
        
        //A parte a seguir é para a implementação do desenho de textos necessário para o menu
        std::vector<sf::Text*> textos = pE->getTextos();
        for (unsigned int i = 0; i < textos.size(); i++){
            if (textos[i] != nullptr){
                window->draw(*textos[i]);
                }
            }
        textos.clear();
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
        texturas[caminho] = novaTextura;
        return novaTextura;
    }

}