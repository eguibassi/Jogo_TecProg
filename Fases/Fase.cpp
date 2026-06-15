#include "Fase.h"
#include "../Entidades/Projetil.h" 
#include "../Entidades/Personagens/Goblin.h"

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

        
        
        lista_ents.percorrer();/*faz todos se moverem*/

        GC.executar();

        desenharFundo();
        
        
        if (pGG) {
            pGG->desenharForma(chaoFase);
        }

        lista_ents.desenhar();
    }

    const Listas::ListaEntidades& Fase::getLisEnt() const
    {
        return lista_ents;
    }

    void Fase::criarCenario()
    {
        criarFundo();
        criarPlataformas();
        criarObstaculo();
        criarInimigos();
    }

    void Fase::criarGoblins() {
        int quantidade = (rand() % 3) + 2; 

        for (int i = 0; i < quantidade; i++) {
            Personagens::Goblin* goblin = new Personagens::Goblin();
            
            // Dica: A posição X agora é relativa ao loop, como você já tinha feito
            goblin->setPosicao(100.0f + (i * 200.0f), 400.0f);
            
            // O pJogador e GC já existem na classe Fase, então funciona direto!
            goblin->setJogador(pJogador);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
        }
    }

    void Fase::criarPlataformas() {
    
        sementear();

        std::vector<sf::Vector2f> posicoesPlataformas;

        // Primeira posição: plataforma de cima na esquerda.
        // Essa plataforma sempre estará na fase.
        posicoesPlataformas.push_back(sf::Vector2f(87.0f, 300.0f));

        posicoesPlataformas.push_back(sf::Vector2f(325.0f, 300.0f));
        posicoesPlataformas.push_back(sf::Vector2f(563.0f, 300.0f));
        posicoesPlataformas.push_back(sf::Vector2f(206.0f, 430.0f));
        posicoesPlataformas.push_back(sf::Vector2f(444.0f, 430.0f));

        int quantidadePlataformas = 2 + rand() % 4;

        std::vector<bool> plataformaJaCriada;

        for (int i = 0; i < 5; i++) {
            plataformaJaCriada.push_back(false);
        }

        // A plataforma da posição 0 sempre é criada
        Entidades::Plataforma* plat1 = new Entidades::Plataforma();
        Entidades::Plataforma* plat2 = new Entidades::Plataforma();

        plat1->setPosicao(
            posicoesPlataformas[0].x,
            posicoesPlataformas[0].y
        );
         plat2->setPosicao(
            posicoesPlataformas[1].x,
            posicoesPlataformas[1].y
        );

        lista_ents.incluir(plat1);
        GC.incluirObstaculo(plat1);
        lista_ents.incluir(plat2);
        GC.incluirObstaculo(plat2);

        plataformaJaCriada[0] = true;
        plataformaJaCriada[1] = true;

        int plataformasCriadas = 2;

        while (plataformasCriadas < quantidadePlataformas) {
        
            int indiceSorteado = rand() % 5;

            if (!plataformaJaCriada[indiceSorteado]) {
            
                Entidades::Plataforma* plat = new Entidades::Plataforma();

                plat->setPosicao(
                    posicoesPlataformas[indiceSorteado].x,
                    posicoesPlataformas[indiceSorteado].y);

                lista_ents.incluir(plat);
                GC.incluirObstaculo(plat);

                plataformaJaCriada[indiceSorteado] = true;
                plataformasCriadas++;
            }
        }
    }
}