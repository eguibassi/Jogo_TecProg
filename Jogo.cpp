#include "Jogo.h"
#include "Menu.h"
#include "Ente.h"

Jogo::Jogo() :
    estadoAtual(MENU),
    pJog1(nullptr), pJog2(nullptr),
    fasePrimeira(nullptr),
    menu(nullptr)
{
    Ente::setGG(&GG);

    menu = new Menu();
    menu->setJogo(this);
}

Jogo::~Jogo()
{
    if (menu != nullptr)
    {
        delete menu;
        menu = nullptr;
    }

    if (fasePrimeira != nullptr)
    {
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }
    if (pJog1 != nullptr)
    {
        delete pJog1;
        pJog1 = nullptr;
    }

    if (pJog2 != nullptr){
        delete pJog2;
        pJog2 = nullptr;
    }
}

void Jogo::executar()
{
    while (GG.verificaJanelaAberta())
    {
        sf::Event evento;

        while (GG.getWindow()->pollEvent(evento))/*poolEvent pega as mensagens da fila do window    */
        {
            if (evento.type == sf::Event::Closed)
            {
                GG.fecharJanela();
            }
        }

        GG.limparJanela();

        switch (estadoAtual)
        {
            case MENU:
                if (menu != nullptr)
                {
                    menu->executar();
                }
                break;

            case FASE1:
                if (fasePrimeira != nullptr)
                {
                    fasePrimeira->executar();
                }
                break;
        }

        GG.mostrarElementos();
    }
}

void Jogo::entrarFase1(bool segundoJogador)
{
    if (fasePrimeira != nullptr)
    {
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (pJog1 != nullptr)
    {
        delete pJog1;
        pJog1 = nullptr;
    }

    if (pJog2 != nullptr)
    {
        delete pJog2;
        pJog2 = nullptr;
    }

    pJog1 = new Personagens::Jogador(false);

    // Posiciona o jogador 1 em cima da primeira plataforma
    pJog1->setPosicao(110.0f, 250.0f);

    if (segundoJogador)
    {
        pJog2 = new Personagens::Jogador(true);

        // Posiciona o jogador 2 em cima da primeira plataforma
        pJog2->setPosicao(170.0f, 250.0f);

        fasePrimeira = new Fases::FasePrimeira(pJog1, pJog2);
    }
    else
    {
        pJog2 = nullptr;

        fasePrimeira = new Fases::FasePrimeira(pJog1, nullptr);
    }

    estadoAtual = FASE1;
}