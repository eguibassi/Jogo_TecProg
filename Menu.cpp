#include "Menu.h"

Menu::Menu() : pJog(nullptr), ativo(true), rankingAberto(false), mouseClick(false){
    inicializarFonte();
    inicializarFundo();
    inicializarTextos();
}

Menu::Menu(Jogo* pJogo) : pJog(pJogo), ativo(true), rankingAberto(false), mouseClick(false){
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

    opcaoFase1.setFont(fonte);
    opcaoFase1.setString("FASE 1: PARQUINHO DA P.E.K.K.A");
    opcaoFase1.setCharacterSize(30);
    opcaoFase1.setFillColor(sf::Color::White);
    opcaoFase1.setPosition(150.f, 250.f);

    opcaoFase2.setFont(fonte);
    opcaoFase2.setString("FASE 2: PICO CONGELADO");
    opcaoFase2.setCharacterSize(30);
    opcaoFase2.setFillColor(sf::Color::White);
    opcaoFase2.setPosition(150.f, 320.f);

    opcaoRanking.setFont(fonte);
    opcaoRanking.setString("RANKING");
    opcaoRanking.setCharacterSize(30);
    opcaoRanking.setFillColor(sf::Color::White);
    opcaoRanking.setPosition(300.f, 390.f);

    textoRanking.setFont(fonte);
    textoRanking.setString("Ranking");
    textoRanking.setCharacterSize(70);
    textoRanking.setFillColor(sf::Color::Transparent);
    textoRanking.setPosition(300.f, 120.f);

    textoVoltar.setFont(fonte);
    textoVoltar.setString("Pressione ESC para voltar ao menu");
    textoVoltar.setCharacterSize(35);
    textoVoltar.setFillColor(sf::Color::Transparent);
    textoVoltar.setPosition(180.f, 300.f);

    adicionarTexto(&titulo);
    adicionarTexto(&opcaoFase1);
    adicionarTexto(&opcaoFase2);
    adicionarTexto(&opcaoRanking);
    adicionarTexto(&textoRanking);
    adicionarTexto(&textoVoltar);
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
    }

    desenhar();
}

void Menu::atualizarMouse(){
    titulo.setFillColor(sf::Color::White);
    textoRanking.setFillColor(sf::Color::Transparent);
    textoVoltar.setFillColor(sf::Color::Transparent);

    if (mouseEmCima(opcaoFase1))
    {
        opcaoFase1.setFillColor(sf::Color::Yellow);
    }
    else
    {
        opcaoFase1.setStyle(sf::Text::Bold);
        opcaoFase1.setFillColor(sf::Color::White);
    }

    if (mouseEmCima(opcaoFase2))
    {
        opcaoFase2.setFillColor(sf::Color::Yellow);
    }
    else
    {
        opcaoFase2.setStyle(sf::Text::Bold);
        opcaoFase2.setFillColor(sf::Color::White);
    }

    if (mouseEmCima(opcaoRanking))
    {
        opcaoRanking.setFillColor(sf::Color::Yellow);
    }
    else
    {
        opcaoRanking.setStyle(sf::Text::Bold);
        opcaoRanking.setFillColor(sf::Color::White);
    }
}

void Menu::verificarClique(){
    bool clicouAgora = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (clicouAgora && !mouseClick)
    {
        if (mouseEmCima(opcaoFase1))
        {
            executarJogar();
        }
        else if (mouseEmCima(opcaoFase2))
        {
            executarFase2();
        }
        else if (mouseEmCima(opcaoRanking))
        {
            executarRanking();
        }
    }

    mouseClick = clicouAgora;
}

void Menu::verificarRanking(){
    titulo.setFillColor(sf::Color::Transparent);
    opcaoFase1.setFillColor(sf::Color::Transparent);
    opcaoFase2.setFillColor(sf::Color::Transparent);
    opcaoRanking.setFillColor(sf::Color::Transparent);

    textoRanking.setFillColor(sf::Color::White);
    textoVoltar.setFillColor(sf::Color::White);

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

void Menu::executarJogar(){
    if (pJog != nullptr){
        pJog->entrarFase1();
    }
}

void Menu::executarFase2(){
    //Quando a fase 2 for criada no Jogo, chamar a função entrarFase2 aqui
}

void Menu::executarRanking(){
    rankingAberto = true;
}

void Menu::executarSalvar(){}
void Menu::executarRecuperar(){}

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