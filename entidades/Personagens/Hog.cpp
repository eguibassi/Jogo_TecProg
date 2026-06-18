#include "Hog.h"

using namespace Personagens;
Hog::Hog() : Inimigo(), forca(5){
    nivel_maldade = 3;
    num_vidas = 10;

    x = 900;
    y = 100;

    corpo.setSize(sf::Vector2f(80.f, 80.f));
    corpo.setPosition((float)x, (float)y);
    corpo.setFillColor(sf::Color::Transparent);
    sprite.setOrigin(0.0f,-75.0f);
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Corredor.png");
    if (textura != nullptr) {
        sprite.setTexture(*textura);

        sf::Vector2u tamanhoTextura = textura->getSize();

        if (tamanhoTextura.x > 0 && tamanhoTextura.y > 0) {
            sprite.setScale(
                corpo.getSize().x / (float)tamanhoTextura.x,
                corpo.getSize().y / (float)tamanhoTextura.y);
        }
    }
}
Hog::~Hog(){forca = -1;}

Entidades::Projetil* Hog::arremessar() {
    if (!ativo) {
        return nullptr;
    }

    Entidades::Projetil* novoProjetil = new Entidades::Projetil("Assets/Projetil Rei.png");
    novoProjetil->setPosicao(x, y + 25);
    novoProjetil->setVx(-8);
    novoProjetil->setDano(forca);
    novoProjetil->setAtivo(true);

    return novoProjetil;
}

void Hog::executar() {
    if (!ativo) {return;}
    mover();
    x = static_cast<int>(corpo.getPosition().x);
    y = static_cast<int>(corpo.getPosition().y);

    sprite.setPosition((float)x, (float)y);
    if (num_vidas <= 0) {
        ativo = false;
    }
}
void Hog::danificar(Jogador* p) {
    if (p == nullptr) {
        return;
    }
    p->tomarDano(forca);
}

void Hog::salvar()
{
    std::ofstream arquivo("salvar.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "HOG "
            << buffer.str()
            << num_vidas << " "
            << nivel_maldade << " "
            << velocidade.x << " "
            << velocidade.y << " "
            << direcao << " "
            << forca
            << std::endl;

    arquivo.close();
}
