#include "Goblin.h"

using namespace Personagens;


Goblin::Goblin() : Inimigo(), raio(15.0f), duracaoTontura(3.0f){
    nivel_maldade = 1; 
    num_vidas = 3;     

    
    corpo.setSize(sf::Vector2f(raio * 2.0f, raio * 2.0f));
    /*carregar a imagem do goblin, e transforma o png em texture*/
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Goblin.png");
    /*textura vai guardar o endereco de memoria onde a imagem do goblin ficou armazenada*/
    if (textura != nullptr)
    {
        sprite.setTexture(*textura);
        sprite.setPosition(corpo.getPosition());
        sprite.setScale(0.1f, 0.1f);
    }
}
Goblin::Goblin(
    bool ativo,
    int x,
    int y,
    int vidas,
    int nivel,
    float vx,
    float vy,
    int direcao,
    float raio,
    float duracaoTontura
) : Goblin(){
    this->ativo = ativo;
    num_vidas = vidas;
    nivel_maldade = nivel;
    velocidade.x = vx;
    velocidade.y = vy;
    this->direcao = direcao;
    this->duracaoTontura = duracaoTontura;

    setPosicao(x, y);

    (void)raio;
}
Goblin::~Goblin(){}

void Goblin::executar(){
    if (!ativo) {
        return;
    }

    if (!seguindoJogador)
    {
        velocidade.x = 5.0f;
    }
    else
    {
        velocidade.x = 2.5f;
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
void Goblin::danificar(Jogador* pJogador){
    if (pJogador != nullptr)
    {
        pJogador->tomarDano(nivel_maldade);
        pJogador->setTonto(true, duracaoTontura);
    }
}

void Goblin::salvar()
{
    std::ofstream arquivo("save_jogo.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "GOBLIN "
            << buffer.str()
            << raio << " "
            << duracaoTontura
            << std::endl;

    arquivo.close();
}