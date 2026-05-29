#include "Fase.h"

#include "../Entidades/Projetil.h" 

namespace Fases {

    Fase::Fase() : pJogador(nullptr) {
    }

    Fase::~Fase() {
    }

    void Fase::executar() {

    if (pJogador != nullptr) {
        Entidades::Projetil* tiro = pJogador->atirar();
        
        
        if (tiro != nullptr) {
            lista_ents.incluir(tiro); //atualizado e desenhado
            GC.incluirProjetil(tiro); //colidir com os inimigos
        }
    }

    //  Atualiza a lógica de TODAS as entidades (
    lista_ents.percorrer();

    //  Resolve colisões
    GC.executar();

    //  Desenha todo mundo
    lista_ents.desenhar();
}

    void Fase::criarInimFaceis() {}
    void Fase::criarPlataformas() {}

    void Fase::criarCenario() {
        criarPlataformas();
        criarObstaculo();
        criarInimigos();
    }
}