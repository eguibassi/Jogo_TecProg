#include "Jogo.h"
#include "Menu.h"
#include "Ente.h"

Jogo::Jogo() :
    estadoAtual(TELA_MENU), // Inicializa apontando para a constante do Menu
    pJog1(nullptr), pJog2(nullptr),
    fasePrimeira(nullptr),
    faseSegunda(nullptr),
    menu(nullptr)
{
    Ente::setGG(&GG);

    if (GG.getWindow() != nullptr) /*30 fps*/
        GG.getWindow()->setFramerateLimit(30);
    
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

    if (faseSegunda != nullptr)
    {
        delete faseSegunda;
        faseSegunda = nullptr;
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
}

bool Jogo::jogadoresDerrotados() const {
    if (pJog1 == nullptr) { return true; }
    if (pJog2 == nullptr) { return !pJog1->getAtivo(); }
    return !pJog1->getAtivo() && !pJog2->getAtivo();
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

        
        if (estadoAtual == TELA_MENU) 
        {
            if (menu != nullptr)
            {
                menu->executar();
            }
        }
        else if (estadoAtual == TELA_FASE1) 
        {
            if (fasePrimeira != nullptr) {
                fasePrimeira->executar();

                if (jogadoresDerrotados()) {
                    voltarMenu();
                }
              
                else if (fasePrimeira->getLisEnt().InimsDerr()) { 
                    trocarFase2();
                }
            }
        }
        else if (estadoAtual == TELA_FASE2) 
        {
            if (faseSegunda != nullptr)
            {
                faseSegunda->executar();

                if (jogadoresDerrotados())
                {
                    voltarMenu();
                }
                else if (faseSegunda->getLisEnt().InimsDerr())
                {
                    voltarMenu();
                }
            }
        }

        GG.mostrarElementos();
    }
}

void Jogo::entrarFase(int numeroFase, bool segundoJogador)
{
    if (fasePrimeira != nullptr) {
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (faseSegunda != nullptr) {
        delete faseSegunda;
        faseSegunda = nullptr;
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
    pJog1->setPosicao(110.0f, 250.0f);

    if (segundoJogador)
    {
        pJog2 = new Personagens::Jogador(true);
        pJog2->setPosicao(170.0f, 250.0f);
    }
    else
    {
        pJog2 = nullptr;
    }

    if (numeroFase == 1)
    {
        fasePrimeira = new Fases::FasePrimeira(pJog1, pJog2);
        estadoAtual = TELA_FASE1; 
    }
    else if (numeroFase == 2)
    {
        faseSegunda = new Fases::FaseSegunda(pJog1, pJog2);
        estadoAtual = TELA_FASE2; 
    }
}

void Jogo::trocarFase2()
{
    if (estadoAtual != TELA_FASE1 || fasePrimeira == nullptr)
    {
        return;
    }

    if (fasePrimeira != nullptr)
    {
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (faseSegunda != nullptr)
    {
        delete faseSegunda;
        faseSegunda = nullptr;
    }

    if (pJog1 != nullptr)
    {
        pJog1->setPosicao(110.0f, 250.0f);
    }

    if (pJog2 != nullptr)
    {
        pJog2->setPosicao(170.0f, 250.0f);
    }

    faseSegunda = new Fases::FaseSegunda(pJog1, pJog2);
    estadoAtual = TELA_FASE2; 
}

void Jogo::voltarMenu() {
    if (fasePrimeira != nullptr) {
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (faseSegunda != nullptr) {
        delete faseSegunda;
        faseSegunda = nullptr;
    }

    if (pJog1 != nullptr) {
        delete pJog1;
        pJog1 = nullptr;
    }

    if (pJog2 != nullptr) {
        delete pJog2;
        pJog2 = nullptr;
    }

    estadoAtual = TELA_MENU; 
}