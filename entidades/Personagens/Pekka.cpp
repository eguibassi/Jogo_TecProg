#include "Pekka.h"

using namespace Personagens;

Pekka::Pekka() : Inimigo(), tamanho(35), aumentaVida(2){
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
Pekka::Pekka(
    bool ativo,
    int x,
    int y,
    int vidas,
    int nivel,
    float vx,
    float vy,
    int direcao,
    int tamanho,
    int aumentaVida
) : Pekka()
{
    this->ativo = ativo;
    num_vidas = vidas;
    nivel_maldade = nivel;
    velocidade.x = vx;
    velocidade.y = vy;
    this->direcao = direcao;
    this->aumentaVida = aumentaVida;

    setPosicao(x, y);

    (void)tamanho;
}

Pekka::~Pekka(){}

void Pekka::executar(){
    if (!ativo) {
        return;
    }

    if (num_vidas <= 3)
    {
        nivel_maldade = 12;
        velocidade.x = 4.0f;
    }
    else
    {
        nivel_maldade = 8;
        velocidade.x = 2.0f;
    }

    mover();

    x = static_cast<int>(corpo.getPosition().x);
    y = static_cast<int>(corpo.getPosition().y);

    if (sprite.getTexture() != nullptr)
    {
        sprite.setPosition(corpo.getPosition());
    }

    if (num_vidas <= 0) {
        ativo = false;
    }
}

void Pekka::danificar(Jogador* pJogador){
    if (pJogador != nullptr)
    {
        pJogador->tomarDano(nivel_maldade);
        num_vidas += aumentaVida;
    }
}

void Pekka::salvar(){
    std::ofstream arquivo("save_jogo.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "PEKKA "
            << buffer.str()
            << tamanho << " "
            << aumentaVida
            << std::endl;

    arquivo.close();
}