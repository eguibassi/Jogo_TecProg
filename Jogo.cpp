#include "Jogo.h"
#include "Menu.h"
#include "Ente.h"
#include <fstream>
#include <algorithm>
#include <cstdlib>

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

    salvarRanking();
    
    menu = new Menu();
    menu->setJogo(this);
}

Jogo::~Jogo()
{
    salvarRanking();

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
    if (pJog1 == nullptr) {
        return true;
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

            if (estadoAtual == MENU && menu != nullptr)
            {
                menu->tratarEvento(evento);
            }
        }

        GG.limparJanela();

        
        if (estadoAtual == TELA_MENU) 
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

                    if (fasePrimeira->getLisEnt().InimsDerr()){
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

void Jogo::entrarFase(
    int numeroFase,
    bool segundoJogador,
    const std::string& nomeJogador1,
    const std::string& nomeJogador2
)
{
    if (fasePrimeira != nullptr){
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

    // Posição inicial do jogador 1
    pJog1->setPosicao(110.0f, 250.0f);

    if (segundoJogador)
    {
        pJog2 = new Personagens::Jogador(true);
        pJog2->setNome(nomeJogador2);

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
void Jogo::voltarMenu(){
    if (fasePrimeira != nullptr){
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

    std::sort(ranking.begin(), ranking.end(), [](const RegistroRanking& a, const RegistroRanking& b) {
        return a.pontos > b.pontos;
    });

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
        arquivoSaida << ranking[i].nome << ", " << ranking[i].pontos << std::endl;
    }

    arquivoSaida.close();
}

const std::vector<RegistroRanking>& Jogo::getRanking() const
{
    return ranking;
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

    std::sort(ranking.begin(), ranking.end(), [](const RegistroRanking& a, const RegistroRanking& b) {
        return a.pontos > b.pontos;
    });

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
        arquivoSaida << ranking[i].nome << ", " << ranking[i].pontos << std::endl;
    }

    arquivoSaida.close();
}

const std::vector<RegistroRanking>& Jogo::getRanking() const
{
    return ranking;
}