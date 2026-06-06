#include "Plataforma.h"

namespace Entidades {

   Plataforma::Plataforma() : altura(30) {
        x = 0;   
        y = 500; 
        
        corpo.setSize(sf::Vector2f(150.f, (float)altura)); 
        corpo.setPosition((float)x, (float)y);

        // Pode deixar transparente depois que o sprite estiver certo
        corpo.setFillColor(sf::Color::Transparent); 

        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Plataforma.png");

        if (textura != nullptr) {
            sprite.setTexture(*textura);

            // NÃO use origin aqui
            sprite.setOrigin(0.f, 0.f);

            // Coloca o sprite no mesmo lugar do corpo
            sprite.setPosition(corpo.getPosition());

            // Faz o sprite ter exatamente o tamanho do corpo
            sf::FloatRect tamanhoSprite = sprite.getLocalBounds();

            sprite.setScale(
                corpo.getSize().x / tamanhoSprite.width,
                corpo.getSize().y / tamanhoSprite.height
            );
        }
    }

    Plataforma::~Plataforma() {
    }

    void Plataforma::executar() {
    }

    void Plataforma::salvar() {
    }

    void Plataforma::obstaculizar(Personagens::Jogador* p) {
        if (p == nullptr) return;
    }

}