using namespace Entidades;

    Projetil::Projetil() : Entidade(),vx(0), dano(0),ativo(true){}
    Projetil::~Projetil(){
        vx = -1;
        dano = -1;
        ativo = false
    }

    Projetil::setVx(int n){vx = n;}
    Projetil::getVx()
