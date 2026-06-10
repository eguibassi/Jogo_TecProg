#include "Plataforma.h"

namespace Entidades {

   Plataforma::Plataforma() : altura(15) {
        x = 0;   
        y = 500; 
        
        corpo.setSize(sf::Vector2f(150.f, (float)altura)); 
        corpo.setPosition((float)x, (float)y);

        
       corpo.setFillColor(sf::Color(139, 0, 0));

    }

    Plataforma::~Plataforma() {
    }

    void Plataforma::executar() {
    }

    void Plataforma::salvar() {
    }

    void Plataforma::obstaculizar(Personagens::Jogador* pJog) {
        if (pJog == nullptr) {
            return;
        }

       
        sf::FloatRect rectJog = pJog->getCorpo().getGlobalBounds();
        sf::FloatRect rectPlat = corpo.getGlobalBounds(); 

        float centroJogY = rectJog.top + rectJog.height / 2.0f;
        float centroPlatY = rectPlat.top + rectPlat.height / 2.0f;

        /*ve se ta em baixo*/
        if (centroJogY > centroPlatY) {
            /*joga ele pra baixo*/
            sf::Vector2f velJog = pJog->getVelocidade();
            velJog.y = 4.0f; 
        
            pJog->setVelocidade(velJog);
    }
}

}