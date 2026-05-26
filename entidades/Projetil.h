#pragma once

namespace Entidades {

    class Projetil : public Entidade {
    protected:
        int vx;
        int dano;
        bool ativo;

    public:
        Projetil();
        ~Projetil();

        void setVx(int n);
        int getVx() const;

        void setDano(int d);
        int getDano() const;

        void executar();
        void salvar();
    };

}