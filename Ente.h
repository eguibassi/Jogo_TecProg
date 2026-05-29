#pragma once
#include "Gerenciadores/Gerenciador_Grafico.h"


class Figura; 

class Ente {
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico* pGG;
    Figura* pFig; 

public:
    Ente();
    virtual ~Ente(); 
    
    virtual void executar() = 0; 
    void desenhar();
    
    static void setGG(Gerenciadores::Gerenciador_Grafico* pG);    
};