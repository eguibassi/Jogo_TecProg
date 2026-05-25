#include "Projetil.h"

using namespace Entidades;

Projetil::Projetil():
    Entidade(),
    vx(0),
    dano(0),
    ativo(true){}

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

    sprite.move(vx, 0);

    if (sprite.getPosition().x < 0 || sprite.getPosition().x > 1280)
    {
        ativo = false;
    }
}

void Projetil::salvar()
{
    //implementar futuramente
}
