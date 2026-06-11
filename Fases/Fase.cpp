#include "Fase.h"
#include "../Entidades/Projetil.h" 
#include "../Entidades/Personagens/Goblin.h"
//Função retirada da resolução de provas do professor Jean Simão, 
//https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/Provas/Provas.htm
static void sementear() {
    rand(); 
    Sleep(100); 
    time_t t;
    srand((unsigned) time(&t)); 
    rand();
}

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

        int quantidadePlataformas = 1 + rand() % 5;

        std::vector<bool> plataformaJaCriada;

        for (int i = 0; i < 5; i++) {
            plataformaJaCriada.push_back(false);
        }

        // A plataforma da posição 0 sempre é criada
        Entidades::Plataforma* plat = new Entidades::Plataforma();

        plat->setPosicao(
            posicoesPlataformas[0].x,
            posicoesPlataformas[0].y
        );

        lista_ents.incluir(plat);
        GC.incluirObstaculo(plat);

        plataformaJaCriada[0] = true;

        int plataformasCriadas = 1;

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
    void Fase::criarCenario() {
        criarFundo();
        criarPlataformas();
        criarObstaculo();
        criarInimigos();
    }
}
