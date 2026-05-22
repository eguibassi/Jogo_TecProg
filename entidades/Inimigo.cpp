#include "Inimigo.h"

#define VELOCIDADE_X_INIMIGO 2.0f
#define CHAO_Y 500.0f

namespace Personagens {

 Inimigo::Inimigo() : nivel_maldade(1), pJogador(nullptr) {
        num_vidas = 3; 
        
        x = 600; 
        y = 100; 
        
        corpo.setSize(sf::Vector2f(50.f, 50.f));
        corpo.setPosition((float)x, (float)y); 
        corpo.setFillColor(sf::Color::Red); 
    }
    Inimigo::~Inimigo() {
    }

  void Inimigo::mover() {
        velocidade.x = 0.f;

        if (pJogador != nullptr) {
            sf::Vector2f posJogador = pJogador->getCorpo().getPosition();
            
            // Usando as variáveis int para a IA
            if (posJogador.x < x) {
                velocidade.x = -VELOCIDADE_X_INIMIGO; 
            } else if (posJogador.x > x) {
                velocidade.x = VELOCIDADE_X_INIMIGO;
            }
        }

        velocidade.y += 0.5f; 
        
        // 1. Move de forma suave
        corpo.move(velocidade);

        // 2. SINCRONIZAMOS x e y como int (estrito ao UML)
        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);

        if (y >= CHAO_Y) {
            y = CHAO_Y;
            corpo.setPosition((float)x, (float)y);
            velocidade.y = 0.f; 
        }
    }

} // namespace Personagens