#include "Menu.h"
#include "Jogo.h"
#include <iostream>

Menu::Menu() :
    pJog(nullptr),
    ativo(true),
    mouseClick(false)
{
    inicializarFonte();
    inicializarTextos();
}

Menu::Menu(Jogo* pJogo) :
    pJog(pJogo),
    ativo(true),
    mouseClick(false)
{
    inicializarFonte();
    inicializarTextos();
}

Menu::~Menu()
{
    limparTextos();
}

void Menu::setJogo(Jogo* pJogo)
{
    pJog = pJogo;
}

void Menu::inicializarFonte()
{
    if (!fonte.loadFromFile("assets/fontes/arial.ttf"))
    {
        std::cout << "Erro ao carregar fonte do Menu." << std::endl;
    }
}

void Menu::inicializarTextos()
{
    opcaoJogar.setFont(fonte);
    opcaoJogar.setString("FASE 1");
    opcaoJogar.setCharacterSize(50);
    opcaoJogar.setFillColor(sf::Color::White);
    opcaoJogar.setPosition(250.f, 250.f);

    adicionarTexto(&opcaoJogar);
}

void Menu::executar()
{
    if (!ativo)
    {
        return;
    }

    atualizarMouse();
    verificarClique();

    desenhar();
}

void Menu::atualizarMouse()
{
    if (mouseEmCima(opcaoJogar))
    {
        opcaoJogar.setFillColor(sf::Color::Yellow);
    }
    else
    {
        opcaoJogar.setFillColor(sf::Color::White);
    }
}

void Menu::verificarClique()
{
    bool clicouAgora = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (clicouAgora && !mouseClick)
    {
        if (mouseEmCima(opcaoJogar))
        {
            executarJogar();
        }
    }

    mouseClick = clicouAgora;
}

bool Menu::mouseEmCima(const sf::Text& texto) const
{
    if (pGG == nullptr || pGG->getWindow() == nullptr)
    {
        return false;
    }

    sf::Vector2i posPixel = sf::Mouse::getPosition(*pGG->getWindow());
    sf::Vector2f posMouse = pGG->getWindow()->mapPixelToCoords(posPixel);

    return texto.getGlobalBounds().contains(posMouse);
}

void Menu::executarJogar()
{
    if (pJog != nullptr)
    {
        pJog->entrarFase1();
    }
}

void Menu::executarRanking()
{
}

void Menu::executarSalvar()
{
}

void Menu::executarRecuperar()
{
}

void Menu::executarSair()
{
    if (pGG != nullptr)
    {
        pGG->fecharJanela();
    }
}

void Menu::setAtivo(const bool estado)
{
    ativo = estado;
}

bool Menu::getAtivo() const
{
    return ativo;
}