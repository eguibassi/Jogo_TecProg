#include "Jogo.h"

Jogo::Jogo() : estadoAtual(FASE_TESTE) {
    
    inimigoTeste.setJogador(&pJog1);

    gerenciadorColisoes.setJogador(&pJog1);
    gerenciadorColisoes.incluirInimigo(&inimigoTeste);
    gerenciadorColisoes.incluirObstaculo(&chao);
    gerenciadorColisoes.incluirObstaculo(&espinho);
    gerenciadorColisoes.incluirObstaculo(&lama);
}

Jogo::~Jogo() {
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
                /*menu futuramente*/
                break;

            case FASE_TESTE:
                
                pJog1.executar();
                inimigoTeste.executar(); 
                chao.executar(); 
                espinho.executar(); 
                lama.executar();

    
                gerenciadorColisoes.executar();

                // Desenha na tela
                chao.desenhar(GG.getWindow());
                lama.desenhar(GG.getWindow());
                espinho.desenhar(GG.getWindow());
                inimigoTeste.desenhar(GG.getWindow());
                pJog1.desenhar(GG.getWindow());
                break;
        }

        GG.mostrarElementos();
    }
}