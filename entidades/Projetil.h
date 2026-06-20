#pragma once
#include "Entidade.h"
#include <string>

namespace Entidades {

    class Projetil : public Entidade {
    private:
        int vx;
        int dano;
      

    public:
        float velocidadeY;
    
    public:
        Projetil(const std::string& caminhoTextura);
       Projetil(
            bool ativo,
            int x,
            int y,
            int vx,
            int dano,
            float velocidadeY
);
        ~Projetil();

        void setVx(int n);
        int getVx() const;

        void setDano(int d);
        int getDano() const;

        void executar();
        void salvar();
    };

}
