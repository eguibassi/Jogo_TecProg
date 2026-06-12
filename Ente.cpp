#include "Ente.h"
//Função retirada da resolução de provas do professor Jean Simão, 
//https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/Provas/Provas.htm
void Ente::sementear() {
    rand(); 
    Sleep(100); 
    time_t t;
    srand((unsigned) time(&t)); 
    rand();
}

Gerenciadores::Gerenciador_Grafico* Ente::pGG = nullptr;

Ente::Ente() : id(0),textos() {}

Ente::~Ente() {
    textos.clear();
}

void Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG) {
    pGG = pG;
}

void Ente::desenhar() {
    
    if (pGG) {
        pGG->desenharEnte(this);
    }
}


void Ente::adicionarTexto(sf::Text* pTexto){
    if (pTexto != nullptr)
    {
        textos.push_back(pTexto);
    }
}

void Ente::limparTextos()
{
    textos.clear();
}

const std::vector<sf::Text*>& Ente::getTextos() const
{
    return textos;
}

