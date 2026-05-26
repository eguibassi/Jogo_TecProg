#include "Jogo.h"

Jogo::Jogo() : estadoAtual(FASE_TESTE) {
    fasePrimeira = new Fases::FasePrimeira(&pJog1);
}

Jogo::~Jogo() {
    
    if (fasePrimeira) {
        delete fasePrimeira;
    }
}

void Jogo::executar() {
    
    while (GG.verificaJanelaAberta()) {
        
        sf::Event event;
        while (GG.getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                GG.fecharJanela();
            }
        }

        GG.limparJanela();

        switch (estadoAtual) {
            case MENU:
                break;

            case FASE_TESTE:
                
                if (fasePrimeira) {
                    fasePrimeira->executar();
                }
                break;
        }

        GG.mostrarElementos();
    }
}