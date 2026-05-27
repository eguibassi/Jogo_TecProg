#include "Projetil.h"

using namespace Entidades;

Projetil::Projetil():
    Entidade(),
    vx(10),
    dano(1),
    ativo(false)
{
    corpo.setSize(sf::Vector2f(20.f, 10.f));
    corpo.setFillColor(sf::Color::Red);
    corpo.setPosition(0.f, 0.f);
}

Projetil::~Projetil(){}

void Projetil::setVx(int n){vx = n;}
int Projetil::getVx() const{return vx;}

void Projetil::setDano(int d){dano = d;}
int Projetil::getDano() const{return dano;}

bool Projetil::getAtivo() const{return ativo;}
void Projetil::setAtivo(bool a){ativo = a;}

void Projetil::executar()
{
    if (!ativo)
    {
        return;
    }

    corpo.move((float)vx, 0.f);

    if (corpo.getPosition().x < 0 || corpo.getPosition().x > 1280)
    {
        ativo = false;
    }
}

void Projetil::salvar()
{
    //implementar futuramente
}