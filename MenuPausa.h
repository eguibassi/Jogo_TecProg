#pragma once

#include "Menu.h"

class MenuPausa : public Menu {
private:
    sf::RectangleShape fundoPausa;

private:
    void inicializarTextosPausa();

public:
    MenuPausa();
    ~MenuPausa();

    int executarPausa();
};