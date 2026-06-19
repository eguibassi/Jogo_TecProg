#include "Fase.h"
#include "../Entidades/Projetil.h" 
#include "../Entidades/Personagens/Goblin.h"

namespace Fases {

    Fase::Fase() : Ente(), pJogador(nullptr), pJogador2(nullptr), maxGoblins(4), maxPlat(3) {
        
        chaoFase.setSize(sf::Vector2f(2000.f, 50.f));
        chaoFase.setPosition(0.f, 550.f);
        chaoFase.setFillColor(sf::Color(139, 69, 19)); 
        GC.setChao(&chaoFase);
    }

    Fase::~Fase() {}

    void Fase::pausaFase() {
        desenharFundo();

        if (pGG) 
            pGG->desenharForma(chaoFase);

        lista_ents.desenhar();
    }
    void Fase::executar() {
        lista_ents.percorrer(); /*faz todos se moverem*/

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

    void Fase::salvar()
    {
        if (pJogador != nullptr)
            pJogador->salvar();

        if (pJogador2 != nullptr)
            pJogador2->salvar();

        lista_ents.salvar();
    }

    void Fase::incEntCar(Entidades::Entidade* ent){
    if (ent == nullptr)
    {
        return;
    }

    lista_ents.incluir(ent);
}
    void Fase::incInimGC(Personagens::Inimigo* inim){
        if (inim == nullptr)
        {
            return;
        }

        inim->setJogador(pJogador);
        GC.incluirInimigo(inim);
    }
    void Fase::incObsGC(Entidades::Obstaculo* obs){
        if (obs == nullptr){
        return;
        }

        GC.incluirObstaculo(obs);
    }
    void Fase::incProjGC(Entidades::Projetil* proj){
        if (proj == nullptr)
        {
            return;
        }

        GC.incluirProjetil(proj);
    }
    void Fase::criarCenario()
    {
        criarFundo();
        criarPlataformas(); // popula posicoesPlataformas e plataformaJaCriada
        criarObstaculo();
        criarInimigos();    // criarGoblins consulta os membros acima
    }

    void Fase::criarGoblins() {
        sementear();
        int quantidade = (rand() % maxGoblins) + 3;

        int goblinsNaFase = 0;

        for (int i = 0; i < 5 && goblinsNaFase < quantidade; i++) {
            if (i == 0 || i == 2) continue;          // slot proibidos
            if (!plataformaJaCriada[i]) continue;     // plataforma nao foi sorteada

            Personagens::Goblin* goblin = new Personagens::Goblin();

            // centralizado na plataforma (150px largura, goblin 30px): offset +60
            // encostado em cima da plataforma (goblin 30px de altura): offset -30
            float gx = posicoesPlataformas[i].x + 60.0f;
            float gy = posicoesPlataformas[i].y - 30.0f;

            goblin->setPosicao(gx, gy);
            goblin->setJogador(pJogador);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
            goblinsNaFase++;
        }

        // goblins restantes vao para o chao
        int noChao = quantidade - goblinsNaFase;
        for (int i = 0; i < noChao; i++) {
            Personagens::Goblin* goblin = new Personagens::Goblin();
            goblin->setPosicao(100.0f + (i * 200.0f), 400.0f);
            goblin->setJogador(pJogador);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
        }
    }

    void Fase::criarPlataformas() {
        sementear();

        // populamos os membros para que criarGoblins possa consultar depois
        posicoesPlataformas.clear();
        posicoesPlataformas.push_back(sf::Vector2f(87.0f,  300.0f)); // slot 0 - spawn jogadores, proibido p/ goblins
        posicoesPlataformas.push_back(sf::Vector2f(325.0f, 300.0f)); // slot 1
        posicoesPlataformas.push_back(sf::Vector2f(206.0f, 380.0f)); // slot 2 - proibido p/ goblins (precaucao j2)
        posicoesPlataformas.push_back(sf::Vector2f(563.0f, 300.0f)); // slot 3
        posicoesPlataformas.push_back(sf::Vector2f(444.0f, 380.0f)); // slot 4

        int quantidadePlataformas = (rand() % maxPlat) + 4;

        plataformaJaCriada.clear();
        for (int i = 0; i < 5; i++) {
            plataformaJaCriada.push_back(false);
        }

        // slots 0, 1 e 2 sempre sao criados
        Entidades::Plataforma* plat1 = new Entidades::Plataforma();
        Entidades::Plataforma* plat2 = new Entidades::Plataforma();
        Entidades::Plataforma* plat3 = new Entidades::Plataforma();

        plat1->setPosicao(
            posicoesPlataformas[0].x,
            posicoesPlataformas[0].y
        );
        plat2->setPosicao(
            posicoesPlataformas[1].x,
            posicoesPlataformas[1].y
        );
        plat3->setPosicao(
            posicoesPlataformas[2].x,
            posicoesPlataformas[2].y
        );

        lista_ents.incluir(plat1);
        GC.incluirObstaculo(plat1);
        lista_ents.incluir(plat2);
        GC.incluirObstaculo(plat2);
        lista_ents.incluir(plat3);
        GC.incluirObstaculo(plat3);

        plataformaJaCriada[0] = true;
        plataformaJaCriada[1] = true;
        plataformaJaCriada[2] = true;

        int plataformasCriadas = 3;

        // percorre apenas os slots restantes (3 e 4), sem depender de sorte
        for (int i = 3; i < 5 && plataformasCriadas < quantidadePlataformas; i++) {
            if (!plataformaJaCriada[i]) {
                Entidades::Plataforma* plat = new Entidades::Plataforma();

                plat->setPosicao(
                    posicoesPlataformas[i].x,
                    posicoesPlataformas[i].y);

                lista_ents.incluir(plat);
                GC.incluirObstaculo(plat);

                plataformaJaCriada[i] = true;
                plataformasCriadas++;
            }
        }
    }
}