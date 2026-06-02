#include "Fase.h"
#include "../Entidades/Projetil.h" 

namespace Fases {

    
    Fase::Fase() : Ente(), pJogador(nullptr), pJogador2(nullptr) {
        
        chaoFase.setSize(sf::Vector2f(2000.f, 50.f));
        

        chaoFase.setPosition(0.f, 550.f);
        
        chaoFase.setFillColor(sf::Color(139, 69, 19)); 

        GC.setChao(&chaoFase);
    }

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
        
        
        lista_ents.percorrer();

        GC.executar();

        desenharFundo();
        
        
        if (pGG) {
            pGG->desenharForma(chaoFase);
        }

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