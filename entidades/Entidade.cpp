#include "Entidade.h"

namespace Entidades {

    // Inicializa x e y com o número inteiro 0
    Entidade::Entidade() : x(0), y(0) {
    }

    Entidade::~Entidade() {
    }

    void Entidade::salvarDataBuffer() {
    }

    void Entidade::desenhar(sf::RenderWindow* window) {
        if (window) {
            window->draw(corpo);
        }
    }

} // namespace Entidades