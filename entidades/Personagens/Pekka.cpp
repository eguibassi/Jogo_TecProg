#include "Pekka.h"

using namespace Personagens;

Pekka::Pekka() : Inimigo(), tamanho(2){
    nivel_maldade = 8;
    num_vidas = 6;

    corpo.setSize(sf::Vector2f(70.f, 90.f));
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/PEKKA.png");

    if (textura != nullptr)
    {
        sprite.setTexture(*textura);
        sprite.setPosition(corpo.getPosition());
        sprite.setScale(0.25f, 0.25f);
    }
}

Pekka::~Pekka(){}

void Pekka::executar(){
    mover();

    if (sprite.getTexture() != nullptr)
    {
        sprite.setPosition(corpo.getPosition());
    }
}

void Pekka::danificar(Jogador* pJogador){
    if (pJogador != nullptr)
    {
        pJogador->tomarDano(nivel_maldade);
    }
}

void Pekka::salvar(){}