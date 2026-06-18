#include "Pekka.h"

using namespace Personagens;

Pekka::Pekka() : Inimigo(), tamanho(35){
    nivel_maldade = 8;
    num_vidas = 6;

    corpo.setSize(sf::Vector2f(tamanho * 2.0f, tamanho * 2.5f));
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

void Pekka::salvar()
{
    std::ofstream arquivo("salvar.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "PEKKA "
            << buffer.str()
            << num_vidas << " "
            << nivel_maldade << " "
            << velocidade.x << " "
            << velocidade.y << " "
            << direcao << " "
            << tamanho
            << std::endl;

    arquivo.close();
}