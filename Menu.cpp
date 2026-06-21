#include "Menu.h"
#include "Jogo.h"
namespace Menus{
Menu::RegistroRanking::RegistroRanking() :
    nome(""),
    pontos(0)
{}

Menu::RegistroRanking::~RegistroRanking(){}

void Menu::RegistroRanking::setNome(const std::string& nome){this->nome = nome;}

void Menu::RegistroRanking::setPontos(const int pontos){this->pontos = pontos;}

bool Menu::RegistroRanking::operator<(const RegistroRanking& outro) const
{
    if (pontos == outro.pontos)
    {
        return nome > outro.nome;
    }

    return pontos < outro.pontos;
}

Menu::Menu() :
    pJog(nullptr),
    ativo(true),
    rankingAberto(false),
    cadastroAberto(false),
    mouseClick(false),
    Jog2(false),
    menuPrincipalInicializado(false),
    faseSelecionada(1),
    indiceNomeAtual(0)
{
    nomesJogadores.resize(2);

    inicializarFonte();
}

Menu::~Menu(){
    limparTextos();
}

void Menu::setMenuPrincipal(){
    if (menuPrincipalInicializado)
    {
        return;
    }

    inicializarFundo();
    inicializarTextos();

    menuPrincipalInicializado = true;
}

void Menu::setJogo(Jogo* pJogo){
    pJog = pJogo;
}

void Menu::inicializarFonte(){
    if (!fonte.loadFromFile("assets/fontes/arial.ttf"))
    {
        std::cerr << "Erro ao carregar fonte do Menu." << std::endl;
    }
}

void Menu::inicializarFundo(){
    if (!texturaFundo.loadFromFile("assets/fundo Menu.png"))
    {
        std::cerr << "Erro ao carregar fundo do Menu." << std::endl;
    }

    fundo.setTexture(texturaFundo);

    sf::Vector2u tamanhoOriginal = texturaFundo.getSize();

    fundo.setScale(
        800.0f / tamanhoOriginal.x,
        600.0f / tamanhoOriginal.y
    );

    fundo.setPosition(0.f, 0.f);
}

sf::Text Menu::criarTexto(
    const std::string& conteudo,
    const unsigned int tam,
    const sf::Color& cor,
    const sf::Vector2f& pos
){
    sf::Text texto;

    texto.setFont(fonte);
    texto.setString(conteudo);
    texto.setCharacterSize(tam);
    texto.setFillColor(cor);
    texto.setPosition(pos);

    return texto;
}

void Menu::inicializarTextos(){
    titulo = criarTexto(
        "Clash++",
        70,
        sf::Color::White,
        sf::Vector2f(280.f, 80.f)
    );

    std::vector<std::string> nomesOpcoes = {
        "FASE 1: PARQUINHO DA P.E.K.K.A",
        "FASE 2: PICO CONGELADO",
        "CARREGAR JOGO",
        "RANKING",
        "SAIR"
    };

    opcoesMenu.reserve(nomesOpcoes.size());

    for (size_t i = 0; i < nomesOpcoes.size(); i++) {
        opcoesMenu.push_back(
            criarTexto(
                nomesOpcoes[i],
                30,
                sf::Color::White,
                sf::Vector2f(150.f, 220.f + (i * 55.f))
            )
        );
    }

    textosRanking.reserve(12);

    textosRanking.push_back(
        criarTexto(
            "Ranking",
            55,
            sf::Color::Transparent,
            sf::Vector2f(300.f, 60.f)
        )
    );

    for (int i = 0; i < 10; i++) {
        textosRanking.push_back(
            criarTexto(
                "",
                24,
                sf::Color::Transparent,
                sf::Vector2f(210.f, 140.f + (i * 33.f))
            )
        );
    }

    textosRanking.push_back(
        criarTexto(
            "Pressione ESC para voltar ao menu",
            25,
            sf::Color::Transparent,
            sf::Vector2f(190.f, 520.f)
        )
    );

    caixaJogs.resize(2);
    textosJogs.reserve(2);

    for(int i = 0; i < 2; i++){
        caixaJogs[i].setSize(sf::Vector2f(90.f, 50.f));
        caixaJogs[i].setPosition(300.f + (110.f * i), 520.f);
        caixaJogs[i].setOutlineColor(sf::Color::White);
        caixaJogs[i].setOutlineThickness(3.f);

        textosJogs.push_back(
            criarTexto(
                std::to_string(i + 1) + "P",
                30,
                sf::Color::White,
                sf::Vector2f(325.f + (110.f * i), 528.f)
            )
        );
    }

    textosCadastro.reserve(3);

    textosCadastro.push_back(
        criarTexto(
            "Nome do jogador 1",
            45,
            sf::Color::Transparent,
            sf::Vector2f(210.f, 160.f)
        )
    );

    textosCadastro.push_back(
        criarTexto(
            "Nome: _",
            35,
            sf::Color::Transparent,
            sf::Vector2f(220.f, 275.f)
        )
    );

    textosCadastro.push_back(
        criarTexto(
            "Digite o nome e pressione ENTER",
            25,
            sf::Color::Transparent,
            sf::Vector2f(190.f, 370.f)
        )
    );

    adicionarTexto(&titulo);

    for (size_t i = 0; i < opcoesMenu.size(); i++) {
        adicionarTexto(&opcoesMenu[i]);
    }

    for (size_t i = 0; i < textosRanking.size(); i++) {
        adicionarTexto(&textosRanking[i]);
    }

    for (size_t i = 0; i < textosJogs.size(); i++) {
        adicionarTexto(&textosJogs[i]);
    }

    for (size_t i = 0; i < textosCadastro.size(); i++) {
        adicionarTexto(&textosCadastro[i]);
    }
}

void Menu::executar(){
    if (!ativo){
        return;
    }

    if (rankingAberto || cadastroAberto){
        verificarTelaAberta();
    }
    else{
        atualizarMouse();
        verificarClique();
    }

    if (pGG != nullptr && pGG->getWindow() != nullptr){
        pGG->getWindow()->draw(fundo);

        if (!rankingAberto && !cadastroAberto)
        {
            for(int i = 0; i < 2; i++){
                pGG->getWindow()->draw(caixaJogs[i]);
            }
        }
    }

    desenhar();
}

void Menu::setVisibilidade(std::vector<sf::Text>& textos, const sf::Color& cor){
    for (size_t i = 0; i < textos.size(); i++) {
        textos[i].setFillColor(cor);
    }
}

void Menu::atualizarMouse()
{
    titulo.setFillColor(sf::Color::White);

    setVisibilidade(textosRanking, sf::Color::Transparent);
    setVisibilidade(textosCadastro, sf::Color::Transparent);

    int jogadorSelecionado = Jog2 ? 1 : 0;

    for (int i = 0; i < 2; i++)
    {
        if (i == jogadorSelecionado)
        {
            caixaJogs[i].setFillColor(sf::Color::Yellow);
            textosJogs[i].setFillColor(sf::Color::Black);
        }
        else
        {
            caixaJogs[i].setFillColor(sf::Color::Transparent);
            textosJogs[i].setFillColor(sf::Color::White);
        }
    }

    for (size_t i = 0; i < opcoesMenu.size(); i++)
    {
        opcoesMenu[i].setStyle(sf::Text::Bold);

        if (mouseEmCima(opcoesMenu[i]))
        {
            opcoesMenu[i].setFillColor(sf::Color::Yellow);
        }
        else
        {
            opcoesMenu[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::verificarClique()
{
    bool clicouAgora = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (clicouAgora && !mouseClick)
    {
        for (size_t i = 0; i < opcoesMenu.size(); i++)
        {
            if (mouseEmCima(opcoesMenu[i]))
            {
                if (i < 2 && pJog != nullptr)
                {
                    abrirCadastro(static_cast<int>(i + 1));
                }
                else if (i == 2 && pJog != nullptr)
                {
                    pJog->carregarJogo();
                }
                else if (i == 3)
                {
                    atualizarTextosRanking();
                    rankingAberto = true;
                }
                else if (i == 4)
                {
                    executarSair();
                }
            }
        }

        for (int i = 0; i < 2; i++)
        {
            if (mouseEmCima(caixaJogs[i]))
            {
                Jog2 = (i == 1);
            }
        }
    }

    mouseClick = clicouAgora;
}

void Menu::verificarTelaAberta(){
    titulo.setFillColor(sf::Color::Transparent);

    setVisibilidade(opcoesMenu, sf::Color::Transparent);
    setVisibilidade(textosJogs, sf::Color::Transparent);

    if (rankingAberto)
    {
        setVisibilidade(textosCadastro, sf::Color::Transparent);
        setVisibilidade(textosRanking, sf::Color::White);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            rankingAberto = false;
        }
    }
    else if (cadastroAberto)
    {
        setVisibilidade(textosRanking, sf::Color::Transparent);
        setVisibilidade(textosCadastro, sf::Color::White);
    }
}

void Menu::abrirCadastro(const int nFase){
    faseSelecionada = nFase;

    cadastroAberto = true;
    rankingAberto = false;

    indiceNomeAtual = 0;

    for (int i = 0; i < 2; i++) {
        nomesJogadores[i].clear();
    }

    atualizarTextoCadastro();
}

void Menu::atualizarTextoCadastro(){
    textosCadastro[0].setString(
        "Nome do jogador " + std::to_string(indiceNomeAtual + 1)
    );

    if (nomesJogadores[indiceNomeAtual].empty())
    {
        textosCadastro[1].setString("Nome: _");
    }
    else
    {
        textosCadastro[1].setString(
            "Nome: " + nomesJogadores[indiceNomeAtual] + "_"
        );
    }
}

void Menu::iniciarFaseSelecionada(){
    if (pJog == nullptr)
    {
        return;
    }

    cadastroAberto = false;

    pJog->entrarFase(
        faseSelecionada,
        Jog2,
        nomesJogadores[0],
        nomesJogadores[1]
    );
}

void Menu::atualizarTextosRanking(){
    if (pJog == nullptr)
    {
        return;
    }

    const std::vector<Menus::Menu::RegistroRanking>& ranking = pJog->getRanking();

    for (int i = 0; i < 10; i++) {
        if (i < static_cast<int>(ranking.size())) {
            textosRanking[i + 1].setString(
                std::to_string(i + 1) + ". " +
                ranking[i].nome + " - " +
                std::to_string(ranking[i].pontos) + " pontos"
            );
        }
        else if (i == 0) {
            textosRanking[i + 1].setString("Ranking vazio");
        }
        else {
            textosRanking[i + 1].setString("");
        }
    }
}

void Menu::tratarEvento(const sf::Event& evento){
    if (!cadastroAberto)
    {
        return;
    }

    if (evento.type == sf::Event::TextEntered)
    {
        if (evento.text.unicode == 8)
        {
            if (!nomesJogadores[indiceNomeAtual].empty())
            {
                nomesJogadores[indiceNomeAtual].erase(
                    nomesJogadores[indiceNomeAtual].size() - 1,
                    1
                );
            }
        }
        else if (
            evento.text.unicode >= 32 &&
            evento.text.unicode < 128 &&
            evento.text.unicode != ';'
        ){
            if (nomesJogadores[indiceNomeAtual].size() < 15)
            {
                nomesJogadores[indiceNomeAtual] +=
                    static_cast<char>(evento.text.unicode);
            }
        }

        atualizarTextoCadastro();
    }
    else if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Enter)
        {
            if (Jog2 && indiceNomeAtual == 0)
            {
                indiceNomeAtual = 1;
                atualizarTextoCadastro();
            }
            else
            {
                iniciarFaseSelecionada();
            }
        }
        else if (evento.key.code == sf::Keyboard::Escape)
        {
            cadastroAberto = false;
        }
    }
}

void Menu::executarSair(){
    if (pGG != nullptr)
    {
        pGG->fecharJanela();
    }
}

void Menu::setAtivo(const bool estado){
    ativo = estado;
}

bool Menu::getAtivo() const{
    return ativo;
}
}