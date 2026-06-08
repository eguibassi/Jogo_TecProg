#include "Gerenciador_Grafico.h"
#include "../Ente.h"
#include "../Entidades/Entidade.h"
/*singleton implementado, as classes nao criam gerenciadores_graficos novos, usam o mesmo através da instancia,isso permite que personagens consigam carregar suas imagens sem que eu precise passar o ponteiro do gerenciador por parâmetro em todas as classes*/
namespace Gerenciadores {

    Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

    Gerenciador_Grafico::Gerenciador_Grafico() {
        window = new sf::RenderWindow(sf::VideoMode(800, 600), "Clash++");
        window->setFramerateLimit(60);
        
        instancia = this; /*avisa a todos que esse eh o gerenciador grafico oficial*/
        Ente::setGG(this);/*passa o ponteiro do gerenciador para ela, para todos saberem que o gerenciador gráfico eh o responsavel por desenhar na tela*/
    }

    Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
        return instancia;
    }

    Gerenciador_Grafico::~Gerenciador_Grafico() {
        for (auto it = texturas.begin(); it != texturas.end(); ++it) {
            delete it->second; /*deleta o segundo(ponteiro da textura)*/
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
        /*converte para entidade*/
    
        if (pEntidade && pEntidade->getAtivo()) {
            if (pEntidade->getSprite().getTexture() != nullptr) {
                window->draw(pEntidade->getSprite());
            } 
            else {/*se nao tiver imagem*/
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

    sf::Texture* Gerenciador_Grafico::carregarTextura(const char* caminho) {/*recebe o texto do endereco da imagem*/
        if (texturas.find(caminho) != texturas.end()) {/*ve se ja achou a imagem*/
            return texturas[caminho]; /*devolve o ponteiro de texturas*/
        }
        sf::Texture* novaTextura = new sf::Texture(); /*se falhou o if de cima a imagem é nova*/
        if (!novaTextura->loadFromFile(caminho)) {/*se digitou errado ou nao existe*/
            std::cout << "ERRO::Nao foi possivel carregar a textura: " << caminho << std::endl;
            delete novaTextura; /*se nao encontrou deleta*/
            return nullptr;
        }
        texturas[caminho] = novaTextura; /*se deu certo pega o map comeca a guardar o nome do caminho  e guarda o ponteiro nova textura*/
        return novaTextura; /*devolve a textura */
    }

    void Gerenciador_Grafico::desenharForma(sf::RectangleShape& forma) {
    if (window) {
        window->draw(forma);
    }
}

}
