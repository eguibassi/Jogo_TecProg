#include"jogador.h"
#include <iostream>

// Construtor: Inicializa as variáveis com valores padrão seguros
Jogador::Jogador() {
    pontos = 0;
    velX = 0.0f;
    velY = 0.0f;
    noChao = false;
    velocidadePulo = -15.0f; // Negativo porque, na tela, o Y sobe para baixo
    olhandoParaDireita = true;
    tempoUltimoTiro = 0.0f;
    estaVivo = true;
    
    // Assumindo que num_vidas vem da classe Personagem
    num_vidas = 3; 
}

// Destrutor: Por enquanto não estamos alocando nada dinamicamente com "new" aqui
Jogador::~Jogador() {
}

// Lógica de pulo simples
void Jogador::pular() {
    // Só pode pular se estiver pisando em algo
    if (noChao == true) {
        velY = velocidadePulo;
        noChao = false; // Assim que pula, não está mais no chão
    }
}

// Atualiza a posição baseada na velocidade
void Jogador::mover() {
    // Aqui no futuro você colocará os comandos da SFML (Ex: se apertar 'D', velX = 5)
    
    // Atualiza as posições X e Y herdadas de Personagem/Entidade
    x += velX;
    y += velY;
}

// Lida com a perda de vidas
void Jogador::receberDano(int dano) {
    num_vidas -= dano;
    
    if (num_vidas <= 0) {
        estaVivo = false;
        // Futuramente: tocar animação de morte do Rei
    }
}

// Volta o jogador para o início se ele cair da fase, por exemplo
void Jogador::resetarPosicao() {
    x = 100.0f; // Posição X inicial genérica
    y = 100.0f; // Posição Y inicial genérica
    velX = 0.0f;
    velY = 0.0f;
}

// Métodos de Acesso (Getters e Setters)
void Jogador::incrementarPontos(int p) {
    pontos += p;
}

int Jogador::getPontos() {
    return pontos;
}

float Jogador::getPosicaoX() {
    return x;
}

float Jogador::getPosicaoY() {
    return y;
}

void Jogador::setVelY(float v) {
    velY = v;
}

void Jogador::setNoChao(bool estado) {
    noChao = estado;
}

// O Executar é o "coração" da classe. Ele roda a cada frame do jogo.
void Jogador::executar() {
    if (estaVivo == true) {
        // 1. Aplica a gravidade constantemente puxando para baixo
        velY += 0.5f; // 0.5f é a força da gravidade genérica
        
        // 2. Chama a função que altera o X e Y
        mover();
        
        // Futuramente: Atualizar animação do personagem aqui
    }
}


// =========================================================
// MÉTODOS VAZIOS (Dependem de outras classes para o futuro)
// =========================================================

void Jogador::colidir(Inimigo* pin) {
    // Futuro: Verificar se tomou dano do Hog Rider / P.E.K.K.A ou se pulou na cabeça deles
}

void Jogador::colidir(Obstaculo* pObs) {
    // Futuro: Verificar se pisou no Elixir Negro ou bateu na Lápide
}

void Jogador::atirar() {
    // Futuro: Criar um objeto Projetil e adicioná-lo na lista de entidades
}

void Jogador::salvar() {
    // Futuro: Gravar os dados (pontos, vidas, posições) num arquivo .txt
}
