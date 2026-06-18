#include "Entidade.h"

using namespace Entidades; 

    // Inicializa x e y com o número inteiro 0
    Entidade::Entidade() : x(0), y(0),ativo(true),textura(nullptr) {
    }

    Entidade::~Entidade() {
    }

    void Entidade::salvarDataBuffer() {
        buffer.str("");
        buffer.clear();

        buffer << ativo << " "
           << x << " "
           << y << " ";
    }

   

