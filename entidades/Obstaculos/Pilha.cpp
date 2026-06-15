#include "Pilha.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

namespace Entidades {

    Pilha::Pilha() : largura(90.f) {
        danoso = false; 
        x = 150; 
        y = 500; 
        yBase = y;

        corpo.setSize(sf::Vector2f(largura, 8.f)); 
        corpo.setPosition((float)x, (float)y);
        
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Pilha de ossos.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);

            // Recorta a pilha de ossos para remover a margem transparente da imagem
            sprite.setTextureRect(sf::IntRect(18, 186, 466, 123));

            // Ajustando a escala para manter a pilha de ossos próxima da largura do obstáculo
            sprite.setScale(largura / 466.f, largura / 466.f); 

            sprite.setOrigin(0.f, -50.f); /*fazendo ele parar de flutuar*/
            sprite.setPosition((float)x, (float)y);
        }
    }

    Pilha::~Pilha() {
    }

    void Pilha::executar() {
        aplicarGravidade();

        if (textura != nullptr) {
            sprite.setPosition((float)x, (float)y + 20.0f);
        }
    }

    void Pilha::salvar() {
     
    }

    void Pilha::obstaculizar(Personagens::Jogador* p) {
        if (p != nullptr) {
            p->setLento(true);
        }
    }
    void Pilha::setPosicao(float novoX, float novoY) {
        x = static_cast<int>(novoX);
        y = static_cast<int>(novoY);
        yBase = y;
        velocidadeY = 0.f;

        corpo.setPosition(novoX, novoY);

        if (textura != nullptr) {
            sprite.setPosition(novoX, novoY+20.0f);
        }
}
}
