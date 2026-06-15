#include "Projetil.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"

#define GRAVIDADE_PROJETIL 0.1f

using namespace Entidades;

Projetil::Projetil(const std::string& caminhoTextura):
    Entidade(),
    vx(10),
    dano(1),
    velocidadeY(0.f)
{
    ativo = false;

    corpo.setSize(sf::Vector2f(32.f, 32.f));
    corpo.setFillColor(sf::Color::Transparent);
    corpo.setPosition(0.f, 0.f);
    //.c_str: Converte a string em const char
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura(caminhoTextura.c_str());

    if (textura != nullptr) {
        sprite.setTexture(*textura);

        sf::Vector2u tamanhoTextura = textura->getSize();

        if (tamanhoTextura.x > 0 && tamanhoTextura.y > 0) {
            sprite.setScale(
                corpo.getSize().x / (float)tamanhoTextura.x,
                corpo.getSize().y / (float)tamanhoTextura.y
            );
        }

        sprite.setPosition(0.f, 0.f);
    }
}

Projetil::~Projetil(){}

void Projetil::setVx(int n){ vx = n; }
int Projetil::getVx() const{ return vx; }

void Projetil::setDano(int d){ dano = d; }
int Projetil::getDano() const{ return dano; }

void Projetil::executar()
{
    if (!ativo) {
        return;
    }

    velocidadeY += GRAVIDADE_PROJETIL; /*gravidade */

    corpo.move((float)vx, velocidadeY);

    x = static_cast<int>(corpo.getPosition().x);
    y = static_cast<int>(corpo.getPosition().y);

    sprite.setPosition((float)x, (float)y);

    if (corpo.getPosition().x < 0 || corpo.getPosition().x > 1280) {
        ativo = false;
    }

    /*desativa se o projetil cair no chao*/
    if (corpo.getPosition().y > 550.f) {
        ativo = false;
    }
}

void Projetil::salvar()
{
    //implementar futuramente
}