#include "Menu.h"

Menu::Menu() :
    pJog(nullptr),
    ativo(true),
    rankingAberto(false),
    cadastroAberto(false),
    digitandoJogador2(false),
    mouseClick(false),
    segundoJogador(false),
    faseSelecionada(1)
{
    inicializarFonte();
    inicializarFundo();
    inicializarTextos();
}

Menu::~Menu(){
    limparTextos();
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
    fundo.setScale(800.0f / tamanhoOriginal.x, 600.0f / tamanhoOriginal.y);
    fundo.setPosition(0.f, 0.f);
}

void Menu::inicializarTextos(){
    titulo.setFont(fonte);
    titulo.setString("Clash++");
    titulo.setCharacterSize(70);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(280.f, 80.f);

    std::vector<std::string> nomesOpcoes = {
        "FASE 1: PARQUINHO DA P.E.K.K.A",
        "FASE 2: PICO CONGELADO",
        "RANKING",
        "SAIR"
    };

    for (size_t i = 0; i < nomesOpcoes.size(); i++) {
        sf::Text texto;
        texto.setFont(fonte);
        texto.setString(nomesOpcoes[i]);
        texto.setCharacterSize(30);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(150.f, 250.f + (i * 70.f)); 
        opcoesMenu.push_back(texto);
    }

    /*textos ranking*/
    sf::Text txtTituloRanking;
    txtTituloRanking.setFont(fonte);
    txtTituloRanking.setString("Ranking");
    txtTituloRanking.setCharacterSize(55);
    txtTituloRanking.setFillColor(sf::Color::Transparent);
    txtTituloRanking.setPosition(300.f, 60.f);
    textosRanking.push_back(txtTituloRanking);

    for (int i = 0; i < 10; i++) {
        sf::Text txtLinhaRanking;
        txtLinhaRanking.setFont(fonte);
        txtLinhaRanking.setString("");
        txtLinhaRanking.setCharacterSize(24);
        txtLinhaRanking.setFillColor(sf::Color::Transparent);
        txtLinhaRanking.setPosition(210.f, 140.f + (i * 33.f));
        textosRanking.push_back(txtLinhaRanking);
    }

    sf::Text txtVoltar;
    txtVoltar.setFont(fonte);
    txtVoltar.setString("Pressione ESC para voltar ao menu");
    txtVoltar.setCharacterSize(25);
    txtVoltar.setFillColor(sf::Color::Transparent);
    txtVoltar.setPosition(190.f, 520.f);
    textosRanking.push_back(txtVoltar);

    caixaJogs.resize(2);
    for(int i = 0; i < 2; i++){
       caixaJogs[i].setSize(sf::Vector2f(90.f, 50.f));
       caixaJogs[i].setPosition(300 + (110*i), 500.f);
       caixaJogs[i].setOutlineColor(sf::Color::White);
       caixaJogs[i].setOutlineThickness(3.f);
    }
    caixaJogs[0].setFillColor(sf::Color::Yellow);
    caixaJogs[1].setFillColor(sf::Color::White);

    texto1P.setFont(fonte);
    texto1P.setString("1P");
    texto1P.setCharacterSize(30);
    texto1P.setFillColor(sf::Color::Black);
    texto1P.setPosition(325.f, 508.f);

    texto2P.setFont(fonte);
    texto2P.setString("2P");
    texto2P.setCharacterSize(30);
    texto2P.setFillColor(sf::Color::White);
    texto2P.setPosition(435.f, 508.f);

    textoCadastroTitulo.setFont(fonte);
    textoCadastroTitulo.setString("Nome do jogador 1");
    textoCadastroTitulo.setCharacterSize(45);
    textoCadastroTitulo.setFillColor(sf::Color::Transparent);
    textoCadastroTitulo.setPosition(210.f, 160.f);

    textoCadastroNome.setFont(fonte);
    textoCadastroNome.setString("Nome: _");
    textoCadastroNome.setCharacterSize(35);
    textoCadastroNome.setFillColor(sf::Color::Transparent);
    textoCadastroNome.setPosition(220.f, 275.f);

    textoCadastroAjuda.setFont(fonte);
    textoCadastroAjuda.setString("Digite o nome e pressione ENTER");
    textoCadastroAjuda.setCharacterSize(25);
    textoCadastroAjuda.setFillColor(sf::Color::Transparent);
    textoCadastroAjuda.setPosition(190.f, 370.f);

    adicionarTexto(&titulo);
    adicionarTexto(&texto1P);
    adicionarTexto(&texto2P);
    adicionarTexto(&textoCadastroTitulo);
    adicionarTexto(&textoCadastroNome);
    adicionarTexto(&textoCadastroAjuda);
    
    for (size_t i = 0; i < opcoesMenu.size(); i++) {
        adicionarTexto(&opcoesMenu[i]);
    }
    
    for (size_t i = 0; i < textosRanking.size(); i++) {
        adicionarTexto(&textosRanking[i]);
    }
}

void Menu::executar(){
    if (!ativo){return;}

    if (rankingAberto){
        verificarRanking();
    }
    else if (cadastroAberto){
        verificarCadastro();
    }
    else{
        atualizarMouse();
        verificarClique();
    }

    if (pGG != nullptr && pGG->getWindow() != nullptr){
        pGG->getWindow()->draw(fundo);

        if (!rankingAberto && !cadastroAberto)
        {
            for(int i = 0; i < 2; i++)
                pGG->getWindow()->draw(caixaJogs[i]);
        }
    }

    desenhar();
}

void Menu::atualizarMouse(){
    titulo.setFillColor(sf::Color::White);
    texto1P.setFillColor(sf::Color::White);
    texto2P.setFillColor(sf::Color::White);

    esconderTextosRanking();
    esconderTextosCadastro();

    if (!segundoJogador)
    {
        caixaJogs[0].setFillColor(sf::Color::Yellow);
        caixaJogs[1].setFillColor(sf::Color::Transparent);
        texto1P.setFillColor(sf::Color::Black);
        texto2P.setFillColor(sf::Color::White);
    }
    else
    {
        caixaJogs[0].setFillColor(sf::Color::Transparent);
        caixaJogs[1].setFillColor(sf::Color::Yellow);
        texto1P.setFillColor(sf::Color::White);
        texto2P.setFillColor(sf::Color::Black);
    }

    for (size_t i = 0; i < opcoesMenu.size(); i++) {
        if (mouseEmCima(opcoesMenu[i])) {
            opcoesMenu[i].setFillColor(sf::Color::Yellow);
        } else {
            opcoesMenu[i].setStyle(sf::Text::Bold);
            opcoesMenu[i].setFillColor(sf::Color::White);
        }
    }
}

void Menu::verificarClique(){
    bool clicouAgora = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (clicouAgora && !mouseClick)
    {
        for (size_t i = 0; i < opcoesMenu.size(); i++) {
            if (mouseEmCima(opcoesMenu[i])) {
                if (i == 0 && pJog != nullptr) { // FASE 1
                    abrirCadastro(1);
                } 
                else if (i == 1 && pJog != nullptr) { // FASE 2
                    abrirCadastro(2);
                } 
                else if (i == 2) { // RANKING
                    atualizarTextosRanking();
                    rankingAberto = true;
                } 
                else if (i == 3) { // SAIR
                    executarSair();
                }
            }
        }

        if (mCaixa(caixaJogs[0]))
        {
            segundoJogador = false;
        }
        else if (mCaixa(caixaJogs[1]))
        {
            segundoJogador = true;
        }
    }

    mouseClick = clicouAgora;
}

void Menu::verificarRanking(){
    titulo.setFillColor(sf::Color::Transparent);
    texto1P.setFillColor(sf::Color::Transparent);
    texto2P.setFillColor(sf::Color::Transparent);
    esconderTextosCadastro();
    
    // Esconde os botões do menu
    for (size_t i = 0; i < opcoesMenu.size(); i++) {
        opcoesMenu[i].setFillColor(sf::Color::Transparent);
    }
    
    // Mostra a tela de ranking
    for (size_t i = 0; i < textosRanking.size(); i++) {
        textosRanking[i].setFillColor(sf::Color::White);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        rankingAberto = false;
    }
}

void Menu::verificarCadastro(){
    titulo.setFillColor(sf::Color::Transparent);
    texto1P.setFillColor(sf::Color::Transparent);
    texto2P.setFillColor(sf::Color::Transparent);
    esconderTextosRanking();

    for (size_t i = 0; i < opcoesMenu.size(); i++) {
        opcoesMenu[i].setFillColor(sf::Color::Transparent);
    }

    textoCadastroTitulo.setFillColor(sf::Color::White);
    textoCadastroNome.setFillColor(sf::Color::White);
    textoCadastroAjuda.setFillColor(sf::Color::White);
}

void Menu::abrirCadastro(const int numeroFase){
    faseSelecionada = numeroFase;
    cadastroAberto = true;
    rankingAberto = false;
    digitandoJogador2 = false;
    nomeJogador1.clear();
    nomeJogador2.clear();
    atualizarTextoCadastro();
}

void Menu::atualizarTextoCadastro(){
    if (digitandoJogador2)
    {
        textoCadastroTitulo.setString("Nome do jogador 2");
    }
    else
    {
        textoCadastroTitulo.setString("Nome do jogador 1");
    }

    std::string nomeAtual = getNomeDigitadoAtual();

    if (nomeAtual.empty())
    {
        textoCadastroNome.setString("Nome: _");
    }
    else
    {
        textoCadastroNome.setString("Nome: " + nomeAtual + "_");
    }
}

void Menu::iniciarFaseSelecionada(){
    if (pJog == nullptr)
    {
        return;
    }

    cadastroAberto = false;
    pJog->entrarFase(faseSelecionada, segundoJogador, nomeJogador1, nomeJogador2);
}

void Menu::atualizarTextosRanking(){
    if (pJog == nullptr)
    {
        return;
    }

    const std::vector<RegistroRanking>& ranking = pJog->getRanking();

    for (int i = 0; i < 10; i++) {
        if (i < (int)ranking.size()) {
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

std::string Menu::getNomeDigitadoAtual() const{
    if (digitandoJogador2)
    {
        return nomeJogador2;
    }

    return nomeJogador1;
}

void Menu::setNomeDigitadoAtual(const std::string& nome){
    if (digitandoJogador2)
    {
        nomeJogador2 = nome;
    }
    else
    {
        nomeJogador1 = nome;
    }
}

void Menu::esconderTextosRanking(){
    for (size_t i = 0; i < textosRanking.size(); i++) {
        textosRanking[i].setFillColor(sf::Color::Transparent);
    }
}

void Menu::esconderTextosCadastro(){
    textoCadastroTitulo.setFillColor(sf::Color::Transparent);
    textoCadastroNome.setFillColor(sf::Color::Transparent);
    textoCadastroAjuda.setFillColor(sf::Color::Transparent);
}

void Menu::tratarEvento(const sf::Event& evento){
    if (!cadastroAberto)
    {
        return;
    }

    if (evento.type == sf::Event::TextEntered)
    {
        std::string nomeAtual = getNomeDigitadoAtual();

        if (evento.text.unicode == 8)
        {
            if (!nomeAtual.empty())
            {
                nomeAtual.erase(nomeAtual.size() - 1, 1);
            }
        }
        else if (evento.text.unicode >= 32 && evento.text.unicode < 128 && evento.text.unicode != ';')
        {
            if (nomeAtual.size() < 15)
            {
                nomeAtual += static_cast<char>(evento.text.unicode);
            }
        }

        setNomeDigitadoAtual(nomeAtual);
        atualizarTextoCadastro();
    }
    else if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::Enter)
        {
            if (segundoJogador && !digitandoJogador2)
            {
                digitandoJogador2 = true;
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

bool Menu::mouseEmCima(const sf::Text& texto) const{
    if (pGG == nullptr || pGG->getWindow() == nullptr)
    {
        return false;
    }

    sf::Vector2i posPixel = sf::Mouse::getPosition(*pGG->getWindow());
    sf::Vector2f posMouse = pGG->getWindow()->mapPixelToCoords(posPixel);

    return texto.getGlobalBounds().contains(posMouse);
}

bool Menu::mCaixa(const sf::RectangleShape& caixa) const{
    if (pGG == nullptr || pGG->getWindow() == nullptr)
    {
        return false;
    }

    sf::Vector2i posPixel = sf::Mouse::getPosition(*pGG->getWindow());
    sf::Vector2f posMouse = pGG->getWindow()->mapPixelToCoords(posPixel);

    return caixa.getGlobalBounds().contains(posMouse);
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