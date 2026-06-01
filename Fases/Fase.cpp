#include "Fase.h"

#include "../Entidades/Projetil.h" 

namespace Fases {

    Fase::Fase() : pJogador(nullptr), pJogador2(nullptr) {}

    Fase::~Fase() {
    }

    void Fase::executar() {

    if (pJogador != nullptr) {
        Entidades::Projetil* tiro = pJogador->atirar();

        if (tiro != nullptr) {
            lista_ents.incluir(tiro);
            GC.incluirProjetil(tiro);
        }
    }

    if (pJogador2 != nullptr) {
        Entidades::Projetil* tiro2 = pJogador2->atirar();

        if (tiro2 != nullptr) {
            lista_ents.incluir(tiro2);
            GC.incluirProjetil(tiro2);
        }
    }
    //Atualiza a lógica de todas as entidades
    lista_ents.percorrer();

    GC.executar();

    desenharFundo();

    lista_ents.desenhar();
}

    void Fase::criarInimFaceis() {}
    void Fase::criarPlataformas() {}

    void Fase::criarCenario() {
        criarFundo();
        criarPlataformas();
        criarObstaculo();
        criarInimigos();
    }
}