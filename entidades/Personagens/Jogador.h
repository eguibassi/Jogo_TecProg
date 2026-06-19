#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    private:
        bool jogador2;
        std::string nome;
        sf::Clock relogioTontura;
        float duracaoTontura; // interno: recebido do Goblin via setTonto, nao salvo
        
    protected:
        int pontos;
        bool lento;
        bool tonto;

    public:
        Jogador(bool segundo_jogador = false);
        Jogador(
        bool segundo_jogador,
        const std::string& nome,
        int pontos,
        int vidas,
        bool ativo,
        int x,
        int y,
        float vx,
        float vy,
        bool lento,
        bool tonto
);
        ~Jogador();
        
        void executar();
        void salvar();
        void mover();

        int getPontos() const { return pontos; }
        void setNome(const std::string& n);
        const std::string& getNome() const;
        void operator++();

        
        void setLento(bool estado) { lento = estado; }
        bool getLento() const { return lento; }

        void setTonto(bool estado, float duracao = 3.0f);
        bool getTonto() const { return tonto; }
     

    };

}