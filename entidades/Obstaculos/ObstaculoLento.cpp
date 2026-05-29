#include "ObstaculoLento.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

namespace Entidades {

    ObstaculoLento::ObstaculoLento() : largura(150.f) {
        danoso = false; 
        x = 150; 
        y = 490; 
        corpo.setSize(sf::Vector2f(largura, 10.f)); 
        corpo.setPosition((float)x, (float)y);
        
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Gelo.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);
            // Ajustando a escala de 1254 para aprox 128 pixels (128 / 1254 = ~0.102)
            sprite.setScale(0.102f, 0.102f); 
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