#include "Jogo.h"
#include "Menu.h"
#include "MenuPausa.h"
#include "Ente.h"

Jogo::Jogo() :
    estadoAtual(TELA_MENU),
    pJog1(nullptr),
    pJog2(nullptr),
    fasePrimeira(nullptr),
    faseSegunda(nullptr),
    menu(nullptr),
    menuPausa(nullptr),
    pausado(false)
{
    Ente::setGG(&GG);

    if (GG.getWindow() != nullptr)
    {
        GG.getWindow()->setFramerateLimit(30);
        GG.getWindow()->setKeyRepeatEnabled(false);
    }

    salvarRanking();

    menu = new Menu();
    menu->setMenuPrincipal();
    menu->setJogo(this);

    menuPausa = new MenuPausa();
}

Jogo::~Jogo()
{
    salvarRanking();

    if (menu != nullptr)
    {
        delete menu;
        menu = nullptr;
    }

    if (menuPausa != nullptr)
    {
        delete menuPausa;
        menuPausa = nullptr;
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

bool Jogo::jogsDerr() const
{
    if (pJog1 == nullptr)
    {
        return true;
    }

    if (pJog2 == nullptr)
    {
        return !pJog1->getAtivo();
    }

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

            if (
                evento.type == sf::Event::KeyPressed &&
                evento.key.code == sf::Keyboard::Escape &&
                estadoAtual != TELA_MENU
            ){
                pausado = !pausado;
            }

            if (estadoAtual == TELA_MENU && menu != nullptr)
            {
                menu->tratarEvento(evento);
            }
        }

        GG.limparJanela();

        if (estadoAtual == TELA_MENU)
        {
            pausado = false;

            if (menu != nullptr)
            {
                menu->executar();
            }
        }
        else if (estadoAtual == TELA_FASE1)
        {
            if (fasePrimeira != nullptr)
            {
                if (pausado)
                {
                    fasePrimeira->pausaFase();

                    int opcao = menuPausa->executarPausa();

                    if (opcao == 1)
                    {
                        pausado = false;
                    }
                    else if (opcao == 2)
                    {
                        pausado = false;
                        voltarMenu();
                    }
                }
                else
                {
                    fasePrimeira->executar();

                    if (jogsDerr())
                    {
                        voltarMenu();
                    }
                    else if (fasePrimeira->getLisEnt().InimsDerr())
                    {
                        trocarFase2();
                    }
                }
            }
        }
        else if (estadoAtual == TELA_FASE2)
        {
            if (faseSegunda != nullptr)
            {
                if (pausado)
                {
                    faseSegunda->pausaFase();

                    int opcao = menuPausa->executarPausa();

                    if (opcao == 1)
                    {
                        pausado = false;
                    }
                    else if (opcao == 2)
                    {
                        pausado = false;
                        voltarMenu();
                    }
                }
                else
                {
                    faseSegunda->executar();

                    if (jogsDerr())
                    {
                        voltarMenu();
                    }
                    else if (faseSegunda->getLisEnt().InimsDerr())
                    {
                        voltarMenu();
                    }
                }
            }
        }

        GG.mostrarElementos();
    }
}

void Jogo::entrarFase(
    int nFase,
    bool Jog2,
    const std::string& nomeJ1,
    const std::string& nomeJ2
)
{
    pausado = false;

    if (nFase != 1 && nFase != 2)
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
        delete pJog1;
        pJog1 = nullptr;
    }

    if (pJog2 != nullptr)
    {
        delete pJog2;
        pJog2 = nullptr;
    }

    pJog1 = new Personagens::Jogador(false);
    pJog1->setNome(nomeJ1);
    pJog1->setPosicao(110.0f, 250.0f);

    if (Jog2)
    {
        pJog2 = new Personagens::Jogador(true);
        pJog2->setNome(nomeJ2);
        pJog2->setPosicao(170.0f, 250.0f);
    }
    else
    {
        pJog2 = nullptr;
    }

    if (nFase == 1)
    {
        fasePrimeira = new Fases::FasePrimeira(pJog1, pJog2);
        estadoAtual = TELA_FASE1;
    }
    else if (nFase == 2)
    {
        faseSegunda = new Fases::FaseSegunda(pJog1, pJog2);
        estadoAtual = TELA_FASE2;
    }
}

void Jogo::trocarFase2()
{
    pausado = false;

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

void Jogo::voltarMenu()
{
    pausado = false;

    salvarRanking();

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

    estadoAtual = TELA_MENU;
}

void Jogo::salvarRanking()
{
    ranking.clear();

    std::ifstream arquivoEntrada("ranking.txt");

    if (arquivoEntrada.is_open())
    {
        std::string linha;

        while (std::getline(arquivoEntrada, linha))
        {
            size_t posicaoSeparador = linha.find_last_of(';');

            if (posicaoSeparador == std::string::npos)
            {
                continue;
            }

            RegistroRanking registro;
            registro.nome = linha.substr(0, posicaoSeparador);
            registro.pontos = std::atoi(linha.substr(posicaoSeparador + 1).c_str());

            if (registro.pontos > 0)
            {
                ranking.push_back(registro);
            }
        }

        arquivoEntrada.close();
    }

    if (pJog1 != nullptr && pJog1->getPontos() > 0)
    {
        RegistroRanking registro;
        registro.nome = pJog1->getNome();
        registro.pontos = pJog1->getPontos();

        ranking.push_back(registro);
    }

    if (pJog2 != nullptr && pJog2->getPontos() > 0)
    {
        RegistroRanking registro;
        registro.nome = pJog2->getNome();
        registro.pontos = pJog2->getPontos();

        ranking.push_back(registro);
    }

    std::sort(
        ranking.begin(),
        ranking.end(),
        [](const RegistroRanking& a, const RegistroRanking& b) {
            return a.pontos > b.pontos;
        }
    );

    if (ranking.size() > 10)
    {
        ranking.resize(10);
    }

    std::ofstream arquivoSaida("ranking.txt");

    if (!arquivoSaida.is_open())
    {
        return;
    }

    for (size_t i = 0; i < ranking.size(); i++)
    {
        arquivoSaida << ranking[i].nome << ";" << ranking[i].pontos << std::endl;
    }

    arquivoSaida.close();
}

const std::vector<RegistroRanking>& Jogo::getRanking() const
{
    return ranking;
}