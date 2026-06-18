#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
#include "Gerenciadores/Gerenciador_Grafico.h"


class Figura; 

class Ente {
protected:
    int id;
    static Gerenciadores::Gerenciador_Grafico* pGG;/*ponteiro que todos olham*/
  
    //Vector para textos no menu
    std::vector<sf::Text*> textos;
protected:
    static void sementear();

public:
    Ente();
    virtual ~Ente(); 
    
    virtual void executar() = 0; 
    void desenhar();
    
    static void setGG(Gerenciadores::Gerenciador_Grafico* pG);    

    //pushback no vector
    void adicionarTexto(sf::Text* pTexto);
    //limpa o vector
    void limparTextos();
    const std::vector<sf::Text*>& getTextos() const;
};