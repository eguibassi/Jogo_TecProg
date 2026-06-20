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
                    else if (opcao == 3)
                    {
                        salvarJogo();
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
                    else if (opcao == 3)
                    {
                        salvarJogo();
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
    filaRanking = std::priority_queue<RegistroRanking>();
    std::ifstream arquivoEntrada("ranking.txt");

    if(arquivoEntrada.is_open()){
        std::string linha;
        while(std::getline(arquivoEntrada, linha)){
            size_t posicaoSeparador = linha.find_last_of(';');
            if(posicaoSeparador == std::string::npos){continue;}

            RegistroRanking registro;
            registro.nome = linha.substr(0, posicaoSeparador);
            registro.pontos = std::atoi(linha.substr(posicaoSeparador+1).c_str());
            if(registro.nome != "" && registro.pontos > 0)
                {filaRanking.push(registro);}
        }
        arquivoEntrada.close();
    }

    if(pJog1 != nullptr && pJog1->getPontos() > 0){
        RegistroRanking registro;
        registro.setNome(pJog1->getNome());
        registro.setPontos(pJog1->getPontos());

        filaRanking.push(registro);
    }
    if (pJog2 != nullptr && pJog2->getPontos() > 0)
    {
        RegistroRanking registro;
        registro.setNome(pJog2->getNome());
        registro.setPontos(pJog2->getPontos());

        filaRanking.push(registro);
    }

    std::priority_queue<RegistroRanking> filaAuxiliar = filaRanking;

    int quantidade = 0;

    while (!filaAuxiliar.empty() && quantidade < 10)
    {
        RegistroRanking registro = filaAuxiliar.top();
        filaAuxiliar.pop();

        ranking.push_back(registro);

        quantidade++;
    }

    std::ofstream arquivoSaida("ranking.txt");

    if (!arquivoSaida.is_open()){return;}

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

void Jogo::salvarJogo()
{
    if (estadoAtual == TELA_MENU)
    {
        return;
    }

    try
    {
        if (estadoAtual == TELA_FASE1 && fasePrimeira == nullptr)
        {
            throw std::runtime_error("Erro: fase 1 não existe.");
        }

        if (estadoAtual == TELA_FASE2 && faseSegunda == nullptr)
        {
            throw std::runtime_error("Erro: fase 2 não existe.");
        }

        std::ofstream arqJogo;

        arqJogo.exceptions(std::ios::failbit | std::ios::badbit);

        arqJogo.open("save_jogo.txt", std::ios::trunc);

        arqJogo << "CLASHPP_SAVE 1" << std::endl;
        arqJogo << "FASE " << estadoAtual << std::endl;
        arqJogo << "DOIS_JOGADORES " << (pJog2 != nullptr) << std::endl;

        arqJogo.close();

        if (estadoAtual == TELA_FASE1)
        {
            fasePrimeira->salvar();
        }
        else if (estadoAtual == TELA_FASE2)
        {
            faseSegunda->salvar();
        }
        else
        {
            throw std::runtime_error("Erro: estado invalido no salvamento.");
        }
    }
    catch (const std::exception& erro)
    {
        std::remove("save_jogo.txt");

        std::cerr << "Falha ao salvar o jogo: "
                  << erro.what()
                  << std::endl;
    }
    catch (...)
    {
        std::remove("save_jogo.txt");

        std::cerr << "Falha desconhecida ao salvar o jogo."
                  << std::endl;
    }
}

void Jogo::carregarJogo(){
    std::ifstream arqJogo("save_jogo.txt");

    if (!arqJogo.is_open())
    {
        return;
    }

    std::vector<std::string> linhas;
    std::string linha;
    std::string assinatura;
    int versao = 0;
    int faseSalva = 0;
    bool temJogador2 = false;

    if (!std::getline(arqJogo, linha))
    {
        arqJogo.close();
        return;
    }

    std::istringstream cabecalho(linha);
    cabecalho >> assinatura >> versao;

    if (assinatura != "CLASHPP_SAVE" || versao != 1)
    {
        arqJogo.close();
        return;
    }

    while (std::getline(arqJogo, linha))
    {
        linhas.push_back(linha);

        std::istringstream leitor(linha);
        std::string tipo;

        leitor >> tipo;

        if (tipo == "FASE")
        {
            leitor >> faseSalva;
        }
        else if (tipo == "DOIS_JOGADORES")
        {
            leitor >> temJogador2;
        }
    }

    arqJogo.close();

    if (faseSalva != TELA_FASE1 && faseSalva != TELA_FASE2)
    {
        return;
    }

    pausado = false;

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

    for (size_t i = 0; i < linhas.size(); i++)
    {
        std::istringstream leitor(linhas[i]);

        std::string tipo;
        bool ehJogador2 = false;
        std::string nome;
        int pontos = 0;
        int vidas = 0;
        bool ativo = true;
        int x = 0;
        int y = 0;
        float vx = 0.0f;
        float vy = 0.0f;
        bool lento = false;
        bool tonto = false;

        leitor >> tipo;

        if (tipo != "JOGADOR")
        {
            continue;
        }

        leitor >> ehJogador2
               >> std::quoted(nome)
               >> pontos
               >> vidas
               >> ativo
               >> x
               >> y
               >> vx
               >> vy
               >> lento
               >> tonto;

        Personagens::Jogador* jog = new Personagens::Jogador(
            ehJogador2,
            nome,
            pontos,
            vidas,
            ativo,
            x,
            y,
            vx,
            vy,
            lento,
            tonto
        );

        if (ehJogador2)
        {
            pJog2 = jog;
        }
        else
        {
            pJog1 = jog;
        }
    }

    if (pJog1 == nullptr)
    {
        pJog1 = new Personagens::Jogador(false);
    }

    if (temJogador2 && pJog2 == nullptr)
    {
        pJog2 = new Personagens::Jogador(true);
    }

    if (!temJogador2 && pJog2 != nullptr)
    {
        delete pJog2;
        pJog2 = nullptr;
    }

    if (faseSalva == TELA_FASE1)
    {
        fasePrimeira = new Fases::FasePrimeira(pJog1, pJog2, true);
        estadoAtual = TELA_FASE1;
    }
    else if (faseSalva == TELA_FASE2)
    {
        faseSegunda = new Fases::FaseSegunda(pJog1, pJog2, true);
        estadoAtual = TELA_FASE2;
    }
        for (size_t i = 0; i < linhas.size(); i++)
    {
        std::istringstream leitor(linhas[i]);
        std::string tipo;

        leitor >> tipo;

        if (tipo == "GOBLIN")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            int vidas = 0;
            int nivel = 0;
            float vx = 0.0f;
            float vy = 0.0f;
            int direcao = 1;
            float raio = 0.0f;
            float duracaoTontura = 3.0f;

            leitor >> ativo
                   >> x
                   >> y
                   >> vidas
                   >> nivel
                   >> vx
                   >> vy
                   >> direcao
                   >> raio
                   >> duracaoTontura;

            Personagens::Goblin* goblin = new Personagens::Goblin(
                ativo,
                x,
                y,
                vidas,
                nivel,
                vx,
                vy,
                direcao,
                raio,
                duracaoTontura
            );

            if (faseSalva == TELA_FASE1 && fasePrimeira != nullptr)
            {
                fasePrimeira->incEntCar(goblin);
                fasePrimeira->incInimGC(goblin);
            }
            else if (faseSalva == TELA_FASE2 && faseSegunda != nullptr)
            {
                faseSegunda->incEntCar(goblin);
                faseSegunda->incInimGC(goblin);
            }
        }
        else if (tipo == "PEKKA")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            int vidas = 0;
            int nivel = 0;
            float vx = 0.0f;
            float vy = 0.0f;
            int direcao = 1;
            int tamanho = 0;
            int aumentaVida = 2;

            leitor >> ativo
                   >> x
                   >> y
                   >> vidas
                   >> nivel
                   >> vx
                   >> vy
                   >> direcao
                   >> tamanho
                   >> aumentaVida;

            Personagens::Pekka* pekka = new Personagens::Pekka(
                ativo,
                x,
                y,
                vidas,
                nivel,
                vx,
                vy,
                direcao,
                tamanho,
                aumentaVida
            );

            if (faseSalva == TELA_FASE1 && fasePrimeira != nullptr)
            {
                fasePrimeira->incEntCar(pekka);
                fasePrimeira->incInimGC(pekka);
            }
        }
        else if (tipo == "HOG")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            int vidas = 0;
            int nivel = 0;
            float vx = 0.0f;
            float vy = 0.0f;
            int direcao = 1;
            int forca = 0;

            leitor >> ativo
                   >> x
                   >> y
                   >> vidas
                   >> nivel
                   >> vx
                   >> vy
                   >> direcao
                   >> forca;

            Personagens::Hog* hog = new Personagens::Hog(
                ativo,
                x,
                y,
                vidas,
                nivel,
                vx,
                vy,
                direcao,
                forca
            );

            if (faseSalva == TELA_FASE2 && faseSegunda != nullptr)
            {
                faseSegunda->incEntCar(hog);
                faseSegunda->incInimGC(hog);
            }
        }
    }
        for (size_t i = 0; i < linhas.size(); i++)
    {
        std::istringstream leitor(linhas[i]);
        std::string tipo;

        leitor >> tipo;

        if (tipo == "PLATAFORMA")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            bool danoso = false;
            int yBase = 0;
            float velocidadeY = 0.0f;
            int altura = 0;
            int offset = 0;
            bool pisadaFrame = false;

            leitor >> ativo
                   >> x
                   >> y
                   >> danoso
                   >> yBase
                   >> velocidadeY
                   >> altura
                   >> offset
                   >> pisadaFrame;

            Entidades::Plataforma* plataforma = new Entidades::Plataforma(
                ativo,
                x,
                y,
                danoso,
                yBase,
                velocidadeY,
                altura,
                offset,
                pisadaFrame
            );

            if (faseSalva == TELA_FASE1 && fasePrimeira != nullptr)
            {
                fasePrimeira->incEntCar(plataforma);
                fasePrimeira->incObsGC(plataforma);
            }
            else if (faseSalva == TELA_FASE2 && faseSegunda != nullptr)
            {
                faseSegunda->incEntCar(plataforma);
                faseSegunda->incObsGC(plataforma);
            }
        }
        else if (tipo == "PILHA")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            bool danoso = false;
            int yBase = 0;
            float velocidadeY = 0.0f;
            float largura = 0.0f;

            leitor >> ativo
                   >> x
                   >> y
                   >> danoso
                   >> yBase
                   >> velocidadeY
                   >> largura;

            Entidades::Pilha* pilha = new Entidades::Pilha(
                ativo,
                x,
                y,
                danoso,
                yBase,
                velocidadeY,
                largura
            );

            if (faseSalva == TELA_FASE1 && fasePrimeira != nullptr)
            {
                fasePrimeira->incEntCar(pilha);
                fasePrimeira->incObsGC(pilha);
            }
        }
        else if (tipo == "JAULA")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            bool danoso = false;
            int yBase = 0;
            float velocidadeY = 0.0f;
            int danosidade = 0;

            leitor >> ativo
                   >> x
                   >> y
                   >> danoso
                   >> yBase
                   >> velocidadeY
                   >> danosidade;

            Entidades::Jaula* jaula = new Entidades::Jaula(
                ativo,
                x,
                y,
                danoso,
                yBase,
                velocidadeY,
                danosidade
            );

            if (faseSalva == TELA_FASE2 && faseSegunda != nullptr)
            {
                faseSegunda->incEntCar(jaula);
                faseSegunda->incObsGC(jaula);
            }
        }
    }
        for (size_t i = 0; i < linhas.size(); i++)
    {
        std::istringstream leitor(linhas[i]);
        std::string tipo;

        leitor >> tipo;

        if (tipo == "PROJETIL")
        {
            bool ativo = true;
            int x = 0;
            int y = 0;
            int vx = 0;
            int dano = 0;
            float velocidadeY = 0.0f;

            leitor >> ativo
                   >> x
                   >> y
                   >> vx
                   >> dano
                   >> velocidadeY;

            Entidades::Projetil* projetil = new Entidades::Projetil(
                ativo,
                x,
                y,
                vx,
                dano,
                velocidadeY
            );

            if (faseSegunda != nullptr)
            {
                faseSegunda->incEntCar(projetil);
                faseSegunda->incProjGC(projetil);
            }
        }
    }

    pausado = false;
}