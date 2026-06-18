#pragma once
#include "Entidade.h"
#include <string>

namespace Entidades {

    class Projetil : public Entidade {
    private:
        int vx;
        int dano;
        /*usar o bool ativo */

    public:
        float velocidadeY;
    
    public:
        Projetil(const std::string& caminhoTextura);
        ~Projetil();

        void setVx(int n);
        int getVx() const;

        void setDano(int d);
        int getDano() const;

        void executar();
        void salvar();
    };

}
