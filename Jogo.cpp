#include "Jogo.h"
#include "Menu.h"
#include "Ente.h"

Jogo::Jogo() :
    estadoAtual(MENU),
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
bool Jogo::jogadoresDerrotados() const{
    if (pJog1 == nullptr){return true;}

    if (pJog2 == nullptr){return !pJog1->getAtivo();}

    return !pJog1->getAtivo() && !pJog2->getAtivo();
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
                if (fasePrimeira != nullptr){
                    fasePrimeira->executar();

                    if (jogadoresDerrotados()){
                        voltarMenu();
                        break;
                    }

                    if (fasePrimeira->getLisEnt().todosInimigosDerrotados()){
                        trocarFase2();
                    }
                }
                break;

            case FASE2:
                if (faseSegunda != nullptr)
                {
                    faseSegunda->executar();

                    if (jogadoresDerrotados())
                    {
                        voltarMenu();
                        break;
                    }

                    if (faseSegunda->getLisEnt().todosInimigosDerrotados())
                    {
                        voltarMenu();
                    }
                }
                break;
        }

        GG.mostrarElementos();
    }
}

void Jogo::entrarFase(int numeroFase, bool segundoJogador)
{
    if (fasePrimeira != nullptr){
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (faseSegunda != nullptr){
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

    // Posição inicial do jogador 1
    pJog1->setPosicao(110.0f, 250.0f);

    if (segundoJogador)
    {
        pJog2 = new Personagens::Jogador(true);

        // Posição inicial do jogador 2
        pJog2->setPosicao(170.0f, 250.0f);
    }
    else
    {
        pJog2 = nullptr;
    }

    if (numeroFase == 1)
    {
        fasePrimeira = new Fases::FasePrimeira(pJog1, pJog2);
        estadoAtual = FASE1;
    }
    else if (numeroFase == 2)
    {
        faseSegunda = new Fases::FaseSegunda(pJog1, pJog2);
        estadoAtual = FASE2;
    }
}

void Jogo::trocarFase2()
{
    if (estadoAtual != FASE1 || fasePrimeira == nullptr)
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
    estadoAtual = FASE2;
}
void Jogo::voltarMenu(){
    if (fasePrimeira != nullptr){
        delete fasePrimeira;
        fasePrimeira = nullptr;
    }

    if (faseSegunda != nullptr){
        delete faseSegunda;
        faseSegunda = nullptr;
    }

    if (pJog1 != nullptr){
        delete pJog1;
        pJog1 = nullptr;
    }

    if (pJog2 != nullptr){
        delete pJog2;
        pJog2 = nullptr;
    }

    estadoAtual = MENU;
}