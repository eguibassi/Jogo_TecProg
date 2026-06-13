#include "Fase_Segunda.h"
#include "../Entidades/Projetil.h"
#include "../Entidades/Obstaculos/Jaula.h"

namespace Fases {

    FaseSegunda::FaseSegunda(Personagens::Jogador* pJ1, Personagens::Jogador* pJ2) : 
        Fase(), 
        maxChefoes(3)
    {
        for (int i = 0; i < 3; i++) {
            pHogs[i] = nullptr;
        }

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

    FaseSegunda::~FaseSegunda() {
        for (int i = 0; i < 3; i++) {
            pHogs[i] = nullptr;
        }
    }

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
        criarChefes();
    }

    void FaseSegunda::criarChefes() {
        for (int i = 0; i < maxChefoes; i++) {
            
            Personagens::Hog* hog = new Personagens::Hog();

            //Posição deve ser alterada quando colocarmos as plataformas
            //e implementarmos a logística do nível
            hog->setPosicao(500.0f + (i * 100.0f), 400.0f);
            hog->setJogador(pJogador);

            pHogs[i] = hog;

            lista_ents.incluir(hog);
            GC.incluirInimigo(hog);
        }
    }

    void FaseSegunda::criarJaulas() {
    
        for (int i = 0; i < 3; i++) {
        
            Entidades::Jaula* jaula = new Entidades::Jaula();

            if (i == 0) {
                jaula->setPosicao(120, 395); 
            }
            else {
                jaula->setPosicao(250 + (i * 350), 500);
            }

            lista_ents.incluir(jaula);
            GC.incluirObstaculo(jaula);
        }
    }

    void FaseSegunda::criarProjetil() {
        if (relogioProjetil.getElapsedTime().asSeconds() < 3.0f) {
            return;
        }

        relogioProjetil.restart();

        for (int i = 0; i < maxChefoes; i++) {
            if (pHogs[i] == nullptr) {
                continue;
            }

            if (!pHogs[i]->getAtivo()) {
                continue;
            }

            if (!pHogs[i]->getSeguindoJogador()) {
                continue;
            }

            Entidades::Projetil* projetil = pHogs[i]->arremessar();

            if (projetil == nullptr) {
                continue;
            }

            lista_ents.incluir(projetil);
            GC.incluirProjetil(projetil);
        }
    }

}