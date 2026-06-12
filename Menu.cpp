#include "Menu.h"

Menu::Menu() : pJog(nullptr), ativo(true), rankingAberto(false), mouseClick(false), segundoJogador(false){
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
    txtTituloRanking.setCharacterSize(70);
    txtTituloRanking.setFillColor(sf::Color::Transparent);
    txtTituloRanking.setPosition(300.f, 120.f);
    textosRanking.push_back(txtTituloRanking);

    sf::Text txtVoltar;
    txtVoltar.setFont(fonte);
    txtVoltar.setString("Pressione ESC para voltar ao menu");
    txtVoltar.setCharacterSize(35);
    txtVoltar.setFillColor(sf::Color::Transparent);
    txtVoltar.setPosition(180.f, 300.f);
    textosRanking.push_back(txtVoltar);

    caixa1P.setSize(sf::Vector2f(90.f, 50.f));
    caixa1P.setPosition(300.f, 500.f);
    caixa1P.setFillColor(sf::Color::Yellow);
    caixa1P.setOutlineColor(sf::Color::White);
    caixa1P.setOutlineThickness(3.f);

    caixa2P.setSize(sf::Vector2f(90.f, 50.f));
    caixa2P.setPosition(410.f, 500.f);
    caixa2P.setFillColor(sf::Color::Transparent);
    caixa2P.setOutlineColor(sf::Color::White);
    caixa2P.setOutlineThickness(3.f);

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

    adicionarTexto(&titulo);
    adicionarTexto(&texto1P);
    adicionarTexto(&texto2P);
    
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
    else{
        atualizarMouse();
        verificarClique();
    }

    if (pGG != nullptr && pGG->getWindow() != nullptr){
        pGG->getWindow()->draw(fundo);

        if (!rankingAberto)
        {
            pGG->getWindow()->draw(caixa1P);
            pGG->getWindow()->draw(caixa2P);
        }
    }

    desenhar();
}

void Menu::atualizarMouse(){
    titulo.setFillColor(sf::Color::White);
    texto1P.setFillColor(sf::Color::White);
    texto2P.setFillColor(sf::Color::White);

    // Esconde a tela de ranking
    for (size_t i = 0; i < textosRanking.size(); i++) {
        textosRanking[i].setFillColor(sf::Color::Transparent);
    }

    if (!segundoJogador)
    {
        caixa1P.setFillColor(sf::Color::Yellow);
        caixa2P.setFillColor(sf::Color::Transparent);
        texto1P.setFillColor(sf::Color::Black);
        texto2P.setFillColor(sf::Color::White);
    }
    else
    {
        caixa1P.setFillColor(sf::Color::Transparent);
        caixa2P.setFillColor(sf::Color::Yellow);
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
                    pJog->entrarFase(1, segundoJogador);
                } 
                else if (i == 1 && pJog != nullptr) { // FASE 2
                    pJog->entrarFase(2, segundoJogador);
                } 
                else if (i == 2) { // RANKING
                    rankingAberto = true;
                } 
                else if (i == 3) { // SAIR
                    executarSair();
                }
            }
        }

        if (mCaixa(caixa1P))
        {
            segundoJogador = false;
        }
        else if (mCaixa(caixa2P))
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