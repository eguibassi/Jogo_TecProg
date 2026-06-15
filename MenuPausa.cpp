#include "MenuPausa.h"

MenuPausa::MenuPausa()
{
    inicializarTextosPausa();
}

MenuPausa::~MenuPausa(){
}

void MenuPausa::inicializarTextosPausa(){
    fundoPausa.setSize(sf::Vector2f(430.f, 300.f));
    fundoPausa.setPosition(185.f, 150.f);
    fundoPausa.setFillColor(sf::Color(0, 0, 0, 190));
    fundoPausa.setOutlineColor(sf::Color::White);
    fundoPausa.setOutlineThickness(3.f);

    opcoesMenu.reserve(4);

    opcoesMenu.push_back(
        criarTexto(
            "PAUSADO",
            45,
            sf::Color::White,
            sf::Vector2f(300.f, 175.f)
        )
    );

    opcoesMenu.push_back(
        criarTexto(
            "CONTINUAR",
            30,
            sf::Color::White,
            sf::Vector2f(310.f, 255.f)
        )
    );

    opcoesMenu.push_back(
        criarTexto(
            "VOLTAR AO MENU",
            30,
            sf::Color::White,
            sf::Vector2f(270.f, 315.f)
        )
    );

    opcoesMenu.push_back(
        criarTexto(
            "SALVAR E SAIR",
            30,
            sf::Color(130, 130, 130),
            sf::Vector2f(285.f, 375.f)
        )
    );

    for (size_t i = 0; i < opcoesMenu.size(); i++)
    {
        adicionarTexto(&opcoesMenu[i]);
    }
}

int MenuPausa::executarPausa(){
    if (pGG == nullptr || pGG->getWindow() == nullptr)
    {
        return 0;
    }

    bool clicouAgora = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    for (size_t i = 1; i < opcoesMenu.size(); i++)
    {
        if (i == 3)
        {
            opcoesMenu[i].setFillColor(sf::Color(130, 130, 130));
            continue;
        }

        if (mouseEmCima(opcoesMenu[i]))
        {
            opcoesMenu[i].setFillColor(sf::Color::Yellow);

            if (clicouAgora && !mouseClick)
            {
                mouseClick = clicouAgora;
                return static_cast<int>(i);
            }
        }
        else
        {
            opcoesMenu[i].setFillColor(sf::Color::White);
        }
    }

    mouseClick = clicouAgora;

    pGG->getWindow()->draw(fundoPausa);
    desenhar();

    return 0;
}