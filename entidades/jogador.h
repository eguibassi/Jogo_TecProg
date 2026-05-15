#ifndef JOGADOR_H
#define JOGADOR_H

// Inclui a classe base da qual o Jogador herda
#include "Personagem.h"

// "Avisamos" o compilador que essas classes existem para podermos usar os ponteiros
class Inimigo;
class Obstaculo;

class Jogador : public Personagem {
protected:
    // Atributo protegido exigido pelo UML base
    int pontos;

private:
    // Nossos atributos novos e privados (Encapsulamento)
    float velX;
    float velY;
    bool noChao;
    float velocidadePulo;
    bool olhandoParaDireita;
    float tempoUltimoTiro;
    bool estaVivo;

public:
    // Construtor e Destrutor
    Jogador();
    ~Jogador();

    // Métodos base do UML
    void executar(); // Sobrescrito de Personagem
    void salvar();
    void colidir(Inimigo* pin);

    // Nossos métodos novos
    void pular();
    void atirar();
    void mover();
    void receberDano(int dano);
    void resetarPosicao();
    void colidir(Obstaculo* pObs); // Sobrecarga para obstáculos

    // Métodos de acesso (Getters e Setters)
    void incrementarPontos(int p);
    int getPontos();
    float getPosicaoX();
    float getPosicaoY();
    void setVelY(float v);
    void setNoChao(bool estado);
};

#endif
