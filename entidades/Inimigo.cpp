#include "Inimigo.h"

#define VELOCIDADE_X_INIMIGO 2.0f
#define GRAVIDADE 0.5f
#define CHAO_Y 500.0f


namespace Personagens {

    Inimigo::Inimigo() : nivel_maldade(1), pJogador(nullptr) {
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition(600.f, 100.f); 
        corpo.setFillColor(sf::Color::Red); 
        velocidade = sf::Vector2f(0.f, 0.f);
    }

    Inimigo::~Inimigo() {
    }

    void Inimigo::salvarDataBuffer() {
    }

    void Inimigo::salva() {
    }

    void Inimigo::mover() {
        velocidade.x = 0.f;

        //perseguicao
        if (pJogador != nullptr) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();
            sf::Vector2f posInimigo = corpo.getPosition();

            // Usa as macros de velocidade para a movimentação
            if (posJogador.x < posInimigo.x) {
                velocidade.x = -VELOCIDADE_X_INIMIGO; 
            } else if (posJogador.x > posInimigo.x) {
                velocidade.x = VELOCIDADE_X_INIMIGO;
            }
        }

        // aplica a gravidade e move
        velocidade.y += GRAVIDADE; 
        corpo.move(velocidade);

        // colisão chão
        if (corpo.getPosition().y >= CHAO_Y) {
            corpo.setPosition(corpo.getPosition().x, CHAO_Y);
            velocidade.y = 0.f; 
        }
    }

    void Inimigo::desenhar(sf::RenderWindow* window) {
        if (window) {
            window->draw(corpo);
        }
    }

} // namespace Personagens