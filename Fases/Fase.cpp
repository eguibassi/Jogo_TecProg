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