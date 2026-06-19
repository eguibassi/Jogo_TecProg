#pragma once
#include <SFML/Graphics.hpp>
#include <iomanip>
#include "personagem.h"

namespace Personagens {

    class Jogador : public Personagem { 
    private:
        bool jogador2;
        std::string nome;
        
    protected:
        int pontos;
        bool lento;

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
        bool lento
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
     

    };

}