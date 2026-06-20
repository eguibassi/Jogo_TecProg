#include "Fase_Primeira.h"
#include <cstdlib> 
#include <ctime>   



namespace Fases {


FasePrimeira::FasePrimeira(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2, bool car) : Fase(), maxPekka(2),maxPilha(2){
    
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
    if(!car){
        // Criamos o cenário
        criarCenario();}
    else
    {
        criarFundo();
    } 
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
        criarGoblins();
    }


   void FasePrimeira::criarPekka() {
        sementear();
        int quantidade = (rand() % maxPekka) + 3;

        
        bool pekkaEmPlataforma = false;
        for (int i = 0; i < 5 && !pekkaEmPlataforma; i++) {
            if (i == 0 || i == 2) continue;         // nao criar nesses slots
            if (!platCriada[i]) continue;    // nao foi sorteada

            Personagens::Pekka* pekka = new Personagens::Pekka();

        
            float px = posPlats[i].x + 40.0f;
            float py = posPlats[i].y - 87.5f;

            pekka->setPosicao(px, py);
            pekka->setJogador(pJogador);
            pekka->setJogador2(pJogador2);
            lista_ents.incluir(pekka);
            GC.incluirInimigo(pekka);
            pekkaEmPlataforma = true;
        }

        // o resto das pekkas vai para o chao
        int inicio = pekkaEmPlataforma ? 1 : 0;
        for (int i = inicio; i < quantidade; i++) {
            Personagens::Pekka* pekka = new Personagens::Pekka();
            pekka->setPosicao(150.0f + (i * 150.0f), 400.0f);
            pekka->setJogador(pJogador);
            pekka->setJogador2(pJogador2);
            lista_ents.incluir(pekka);
            GC.incluirInimigo(pekka);
        }
    }

    void FasePrimeira::criarPilha() {
        sementear();
        int quantidade = (rand() % maxPilha) + 3;

        for (int i = 0; i < quantidade; i++) { 
            Entidades::Pilha* lama = new Entidades::Pilha();
            if (i == 0) 
                lama->setPosicao(400.f, 500.f);
            else if (i == 1) 
            lama->setPosicao(250.f, 500.f);
            else if(i == 2)
                lama->setPosicao(700.f,500.f);
            else if(i == 3)
                lama->setPosicao(600.f, 500.f);

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);
        }
    }
}
   