#include "Ente.h"


Gerenciadores::Gerenciador_Grafico* Ente::pGG = nullptr;

Ente::Ente() : id(0), pFig(nullptr) {
}

Ente::~Ente() {
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {
    pGG = pG;
}

void Ente::desenhar() {
    
    if (pGG) {
        pGG->desenharEnte(this);
    }
}