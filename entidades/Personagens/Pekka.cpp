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
        num_vidas += aumentaVida;
    }
}

void Pekka::salvar()
{
    std::ofstream arquivo("save_jogo.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "PEKKA "
            << buffer.str()
            << num_vidas << " "
            << nivel_maldade << " "
            << velocidade.x << " "
            << velocidade.y << " "
            << direcao << " "
            << tamanho << " "
            << aumentaVida
            << std::endl;

    arquivo.close();
}