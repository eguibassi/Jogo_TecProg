#include "Goblin.h"

using namespace Personagens;


Goblin::Goblin() : Inimigo(), raio(15.0f){
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
    float raio
) : Goblin(){
    this->ativo = ativo;
    num_vidas = vidas;
    nivel_maldade = nivel;
    velocidade.x = vx;
    velocidade.y = vy;
    this->direcao = direcao;

    setPosicao(x, y);

    (void)raio;
}
Goblin::~Goblin(){}

void Goblin::executar(){
    mover(); 

    if (sprite.getTexture() != nullptr)
    {
        sprite.setPosition(corpo.getPosition());
    }
}

void Goblin::danificar(Jogador* pJogador){
    if (pJogador != nullptr)
    {
        pJogador->tomarDano(nivel_maldade); 
    }
}

void Goblin::salvar()
{
    std::ofstream arquivo("save_jogo.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "GOBLIN "
            << buffer.str()
            << num_vidas << " "
            << nivel_maldade << " "
            << velocidade.x << " "
            << velocidade.y << " "
            << direcao << " "
            << raio
            << std::endl;

    arquivo.close();
}

