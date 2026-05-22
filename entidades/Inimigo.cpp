#include "Inimigo.h"

#define VELOCIDADE_X_INIMIGO 2.0f
#define GRAVIDADE 0.5f
#define CHAO_Y 500.0f

namespace Personagens {

    Inimigo::Inimigo() : nivel_maldade(1), pJogador(nullptr) {
        num_vidas = 3; 
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition(600.f, 100.f); 
        corpo.setFillColor(sf::Color::Red); 
    }

    Inimigo::~Inimigo() {
    }

    void Inimigo::mover() {
        velocidade.x = 0.f;

        if (pJogador != nullptr) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();
            sf::Vector2f posInimigo = corpo.getPosition();

            if (posJogador.x < posInimigo.x) {
                velocidade.x = -VELOCIDADE_X_INIMIGO; 
            } else if (posJogador.x > posInimigo.x) {
                velocidade.x = VELOCIDADE_X_INIMIGO;
            }
        }

        velocidade.y += GRAVIDADE; 
        corpo.move(velocidade);

        if (corpo.getPosition().y >= CHAO_Y) {
            corpo.setPosition(corpo.getPosition().x, CHAO_Y);
            velocidade.y = 0.f; 
        }
    }

} // namespace Personagens