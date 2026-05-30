#include "Jogo.h"
#include "Menu.h"
#include "Ente.h"

Jogo::Jogo() :
    estadoAtual(MENU),
    fasePrimeira(nullptr),
    menu(nullptr)
{
    Ente::setGG(&GG);

    fasePrimeira = new Fases::FasePrimeira(&pJog1);
    menu = new Menu(this);
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
}

void Jogo::executar()
{
    while (GG.verificaJanelaAberta())
    {
        sf::Event evento;

        while (GG.getWindow()->pollEvent(evento))
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

void Jogo::entrarFase1()
{
    estadoAtual = FASE1;
}