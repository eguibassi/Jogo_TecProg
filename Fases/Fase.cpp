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

    void Fase::salvar(){
        try
        {
            lista_ents.salvar();
        }
        catch (const std::exception& erro)
        {
            throw std::runtime_error(
                std::string("Erro ao salvar fase: ") + erro.what()
            );
        }
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
        inim->setJogador2(pJogador2);
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
        criarPlataformas(); // popula posPlats e platCriada
        criarObstaculo();
        criarInimigos();    // criarGoblins consulta os membros acima
    }

    void Fase::criarGoblins() {
        sementear();
        int quantidade = (rand() % maxGoblins) + 4;

        int goblinsNaFase = 0;

        for (int i = 0; i < 5 && goblinsNaFase < quantidade; i++) {
            if (i == 0 || i == 2) continue;          // slot proibidos
            if (!platCriada[i]) continue;     // plataforma nao foi sorteada

            Personagens::Goblin* goblin = new Personagens::Goblin();

            // centralizado na plataforma (150px largura, goblin 30px): offset +60
            // encostado em cima da plataforma (goblin 30px de altura): offset -30
            float gx = posPlats[i].x + 60.0f;
            float gy = posPlats[i].y - 30.0f;

            goblin->setPosicao(gx, gy);
            goblin->setJogador(pJogador);
            goblin->setJogador2(pJogador2);
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
            goblin->setJogador2(pJogador2);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
        }
    }

    void Fase::criarPlataformas() {
        sementear();

        // populamos os membros para que criarGoblins possa consultar depois
        posPlats.clear();
        posPlats.push_back(sf::Vector2f(87.0f,  300.0f)); // slot 0 - spawn jogadores, proibido p/ goblins
        posPlats.push_back(sf::Vector2f(325.0f, 300.0f)); // slot 1
        posPlats.push_back(sf::Vector2f(206.0f, 380.0f)); // slot 2 - proibido p/ goblins (precaucao j2)
        posPlats.push_back(sf::Vector2f(563.0f, 300.0f)); // slot 3
        posPlats.push_back(sf::Vector2f(444.0f, 380.0f)); // slot 4

        int quantidadePlataformas = (rand() % maxPlat) + 4;

        platCriada.clear();
        for (int i = 0; i < 5; i++) {
            platCriada.push_back(false);
        }

        // slots 0, 1 e 2 sempre sao criados
        Entidades::Plataforma* plat1 = new Entidades::Plataforma();
        Entidades::Plataforma* plat2 = new Entidades::Plataforma();
        Entidades::Plataforma* plat3 = new Entidades::Plataforma();

        plat1->setPosicao(
            posPlats[0].x,
            posPlats[0].y
        );
        plat2->setPosicao(
            posPlats[1].x,
            posPlats[1].y
        );
        plat3->setPosicao(
            posPlats[2].x,
            posPlats[2].y
        );

        lista_ents.incluir(plat1);
        GC.incluirObstaculo(plat1);
        lista_ents.incluir(plat2);
        GC.incluirObstaculo(plat2);
        lista_ents.incluir(plat3);
        GC.incluirObstaculo(plat3);

        platCriada[0] = true;
        platCriada[1] = true;
        platCriada[2] = true;

        int plataformasCriadas = 3;

        // percorre apenas os slots restantes (3 e 4), sem depender de sorte
        for (int i = 3; i < 5 && plataformasCriadas < quantidadePlataformas; i++) {
            if (!platCriada[i]) {
                Entidades::Plataforma* plat = new Entidades::Plataforma();

                plat->setPosicao(
                    posPlats[i].x,
                    posPlats[i].y);

                lista_ents.incluir(plat);
                GC.incluirObstaculo(plat);

                platCriada[i] = true;
                plataformasCriadas++;
            }
        }
    }
}