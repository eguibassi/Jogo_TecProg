#include "ObstaculoLento.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

namespace Entidades {

    ObstaculoLento::ObstaculoLento() : largura(150.f) {
        danoso = false; 
        x = 150; 
        y = 550; 
        corpo.setSize(sf::Vector2f(largura, 10.f)); 
        corpo.setPosition((float)x, (float)y);
        
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Pilha de ossos.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);
            // Recorta a pilha de ossos para remover a margem transparente da imagem
            sprite.setTextureRect(sf::IntRect(18, 186, 466, 123));
            // Ajustando a escala para manter a pilha de ossos próxima da largura do obstáculo
            sprite.setScale(largura / 466.f, largura / 466.f); 
            sprite.setOrigin(0.f, -50.f);/*fazendo ele parar de flutuar*/
            sprite.setPosition((float)x, (float)y);
        }
        
        
    }

    ObstaculoLento::~ObstaculoLento() {
    }

    void ObstaculoLento::executar() {
       
    }

    void ObstaculoLento::salvar() {
     
    }

    void ObstaculoLento::obstaculizar(Personagens::Jogador* p) {
        if (p != nullptr) {
           
            p->setLento(true);
        }
    }


}