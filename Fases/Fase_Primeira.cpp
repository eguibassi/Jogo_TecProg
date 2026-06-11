#include "Fase_Primeira.h"
#include <cstdlib> 
#include <ctime>   



namespace Fases {


FasePrimeira::FasePrimeira(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2) : Fase(), maxPekka(3), maxGoblin(5) {
    
    //Vinculamos o Jogador recebido do Jogo
    pJogador = pJ1;
    pJogador2 = pJ2;

    if (pJogador != nullptr) {
        lista_ents.incluir(pJogador);
        GC.setJogador(pJogador);
    }

    if (pJogador2 != nullptr) {
        lista_ents.incluir(pJogador2);
        GC.setJogador2(pJogador2);
    }

    // Criamos o cenário
    criarCenario(); 
}

    FasePrimeira::~FasePrimeira() {}

    void FasePrimeira::criarFundo(){
        if(!texturaFundo.loadFromFile("Assets/Fundo fase 1.png"))
            return;
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setPosition(0.f, 0.f);
        sf::Vector2u tam = texturaFundo.getSize();
        if (tam.x > 0 && tam.y > 0){
            //Dimensiona a imagem para o tamanho desejado
            spriteFundo.setScale(800.f / tam.x, 600.f / tam.y);
        }
    }

    void FasePrimeira::desenharFundo(){
        Gerenciadores::Gerenciador_Grafico* pGraf = Gerenciadores::Gerenciador_Grafico::getInstancia();

        if (pGraf != nullptr && pGraf->getWindow() != nullptr)
            pGraf->getWindow()->draw(spriteFundo);
    }

    void FasePrimeira::criarObstaculo() {
        criarPilha();
    }

    void FasePrimeira::criarInimigos() {
        criarPekka();
        criarGoblin();
    }

    void FasePrimeira::criarGoblin() {
        
        int quantidade = (rand() % maxGoblin) + 2; 

        for (int i = 0; i < quantidade; i++) {
            
            Personagens::Goblin* goblin = new Personagens::Goblin();
            goblin->setPosicao(100.0f + (i * 200.0f), 400.0f);
            goblin->setJogador(pJogador);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
        }
    }

    void FasePrimeira::criarPekka() {
        int quantidade = (rand() % maxPekka) + 1; 

        for (int i = 0; i < quantidade; i++) {
            
            Personagens::Pekka* pekka = new Personagens::Pekka();

            //Posição deve ser alterada quando colocarmos as plataformas
            //e implementarmos a logística do nível
            pekka->setPosicao(150.0f +(i*150.0f), 400.0f);
            pekka->setJogador(pJogador);
            lista_ents.incluir(pekka);
            GC.incluirInimigo(pekka);
        }

    }

    void FasePrimeira::criarPilha() {
    
        for (int i = 0; i < 3; i++) {
        
            Entidades::Pilha* lama = new Entidades::Pilha();

            if (i == 0) {
                lama->setPosicao(120, 395); 
            }
            else {
                lama->setPosicao(250 + (i * 350), 500);
            }

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);
        
        }
    }
}
   