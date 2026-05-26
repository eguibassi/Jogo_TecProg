#include "Fase_Primeira.h"
#include <cstdlib> 
#include <ctime>   

// Classe temporária de Inimigo para teste 
class Hog : public Personagens::Inimigo {
public:
    // Construtor adaptado para receber a posição inicial
    Hog(float pos_x = 0, float pos_y = 0) { 
        x = static_cast<int>(pos_x);
        y = static_cast<int>(pos_y);
        corpo.setSize(sf::Vector2f(50.f, 50.f)); 
        corpo.setPosition(pos_x, pos_y);
        corpo.setFillColor(sf::Color::Red); 
    }
    void executar() { mover(); }
    void danificar(Personagens::Jogador* p)  {}
    void salva() {}
    void salvar()  {}
};

namespace Fases {


    FasePrimeira::FasePrimeira(Personagens::Jogador* pJog) : Fase(), maxInimMedios(5) {
        
        srand(time(NULL)); 

        //Vinculamos o Jogador recebido do Jogo
        pJogador = pJog;
        lista_ents.incluir(pJogador);
        GC.setJogador(pJogador);

        // Criamos o cenário
        criarCenario(); 
    }

    FasePrimeira::~FasePrimeira() {
    }

    void FasePrimeira::criarObstaculo() {
        // Criamos o chão em um laço de repetição para forrar o cenário
        for (int i = 0; i < 8; i++) {
            Entidades::Plataforma* chao = new Entidades::Plataforma();
            
            chao->setPosicao(i * 200, 500); 
            lista_ents.incluir(chao);
            GC.incluirObstaculo(chao);
        }

        
        criarObstMedios();
    }

    void FasePrimeira::criarInimigos() {
        criarInimMedios();
    }

    void FasePrimeira::criarInimMedios() {
        int quantidade = (rand() % maxInimMedios) + 1; 

        for (int i = 0; i < quantidade; i++) {
            
            Hog* inimigo = new Hog(300.0f + (i * 150.0f), 100.0f); 
            inimigo->setJogador(pJogador);
            
            lista_ents.incluir(inimigo);
            GC.incluirInimigo(inimigo);
        }
    }

    void FasePrimeira::criarObstMedios() {
        
        for (int i = 0; i < 3; i++) {
            
            Entidades::ObstaculoLento* lama = new Entidades::ObstaculoLento();
            lama->setPosicao(250 + (i * 350), 480);
            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);

            Entidades::ObstaculoDano* espinho = new Entidades::ObstaculoDano();
            espinho->setPosicao(400 + (i * 350), 470);
            lista_ents.incluir(espinho);
            GC.incluirObstaculo(espinho);
            
        }
    }

}