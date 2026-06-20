#include "Fase_Segunda.h"
#include "../Entidades/Projetil.h"
#include "../Entidades/Obstaculos/Jaula.h"

namespace Fases {

    FaseSegunda::FaseSegunda(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2, bool car) : 
    Fase(), 
    maxHogs(3),
    maxJaula(2)
    {   
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

    FaseSegunda::~FaseSegunda() {lisHogs.clear();}

    void FaseSegunda::executar() {
        lista_ents.percorrer();/*faz todos se moverem*/

        criarProjetil();

        GC.executar();

        desenharFundo();
        
        if (pGG) {
            pGG->desenharForma(chaoFase);
        }

        lista_ents.desenhar();
    }

    void FaseSegunda::criarFundo() {
        if (!texturaFundo.loadFromFile("Assets/Fundo fase 2.png")) {
            return;
        }

        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setPosition(0.f, 0.f);

        sf::Vector2u tam = texturaFundo.getSize();

        if (tam.x > 0 && tam.y > 0) {
            //Dimensiona a imagem para o tamanho desejado
            spriteFundo.setScale(800.f / tam.x, 600.f / tam.y);
        }
    }

    void FaseSegunda::desenharFundo() {
        Gerenciadores::Gerenciador_Grafico* pGraf = Gerenciadores::Gerenciador_Grafico::getInstancia();

        if (pGraf != nullptr && pGraf->getWindow() != nullptr) {
            pGraf->getWindow()->draw(spriteFundo);
        }
    }

    void FaseSegunda::criarObstaculo() {
        criarJaulas();
    }

    void FaseSegunda::criarInimigos() {
        criarHogs();
        criarGoblins();
    }

    void FaseSegunda::criarHogs() {
        sementear();
        int quantidade = (rand() % maxHogs) + 3; // 3 a 4 Hogs

        int hogsNaFase = 0;

        
        for (int i = 0; i < 5 && hogsNaFase < 2; i++) {
            if (i == 0 || i == 2) continue;        // nao criar nesses slots
            if (!plataformaJaCriada[i]) continue;  // nao foi sorteada

            Personagens::Hog* hog = new Personagens::Hog();

            float hx = posicoesPlataformas[i].x + 35.0f;
            float hy = posicoesPlataformas[i].y - 80.0f;

            hog->setPosicao(hx, hy);
            hog->setJogador(pJogador);
            hog->setJogador2(pJogador2);
            lista_ents.incluir(hog);
            GC.incluirInimigo(hog);
            hogsNaFase++;
        }

        // resto pro chao
        for (int i = hogsNaFase; i < quantidade; i++) {
            Personagens::Hog* hog = new Personagens::Hog();
            hog->setPosicao(500.0f + (i * 100.0f), 400.0f);
            hog->setJogador(pJogador);
            hog->setJogador2(pJogador2);

            lista_ents.incluir(hog);
            GC.incluirInimigo(hog);
        }
    }

    void FaseSegunda::criarJaulas() {
        sementear();
        int quantidade = (rand() % maxJaula) + 3;

        for (int i = 0; i < quantidade; i++) { 
            Entidades::Jaula* jaula = new Entidades::Jaula();
            if (i == 0) 
                jaula->setPosicao(400.f, 500.f);
            else if (i == 1) 
                jaula->setPosicao(250.f, 500.f);
            else 
                jaula->setPosicao(600.f, 500.f);

           

            lista_ents.incluir(jaula);
            GC.incluirObstaculo(jaula);
        }
    }
    
    void FaseSegunda::criarProjetil() {
    if (relogioProjetil.getElapsedTime().asSeconds() < 3.0f) {
        return;
    }

    relogioProjetil.restart();

    std::list<Personagens::Hog*>::iterator it;

    for (it = lisHogs.begin(); it != lisHogs.end(); it++) {
        Personagens::Hog* hog = *it;

        if (hog == nullptr) {
            continue;
        }

        if (!hog->getAtivo()) {
            continue;
        }

        if (!hog->getSeguindoJogador()) {
            continue;
        }

        Entidades::Projetil* projetil = hog->arremessar();

        if (projetil == nullptr) {
            continue;
        }

        lista_ents.incluir(projetil);
        GC.incluirProjetil(projetil);
    }
}
    void FaseSegunda::incInimGC(Personagens::Hog* hog) {
        if (hog == nullptr) {
            return;
        }

        Fase::incInimGC(hog);
        lisHogs.push_back(hog);
    }
}