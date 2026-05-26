#include "Fase.h"

namespace Fases {

    Fase::Fase() : pJogador(nullptr) {
    }

    Fase::~Fase() {
    }

    void Fase::executar() {
    
        lista_ents.percorrer();

        
        GC.executar();

        //Pega a janela do Singleton e desenha todos de uma vez
        sf::RenderWindow* janela = Gerenciadores::Gerenciador_Grafico::getInstancia()->getWindow();
        lista_ents.desenhar(janela);
    }

    void Fase::criarInimFaceis() {}
    void Fase::criarPlataformas() {}

    void Fase::criarCenario() {
        criarPlataformas();
        criarObstaculo();
        criarInimigos();
    }
}