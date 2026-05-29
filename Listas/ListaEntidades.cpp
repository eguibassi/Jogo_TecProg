#include "ListaEntidades.h"
//"../" no include volta uma pasta, necessário para acessar arquivos em pastas diferentes.
#include "../Entidades/Entidade.h"


#include "../Gerenciadores/Gerenciador_Grafico.h"

using namespace Listas;

ListaEntidades::ListaEntidades()
{
}

ListaEntidades::~ListaEntidades()
{
    LEs.limpar();
}

//Inclui uma entidade na lista
void ListaEntidades::incluir(Entidades::Entidade* pE)
{
    LEs.incluir(pE);
}

//Percorre a lista de entidades
void ListaEntidades::percorrer()
{
    Listas::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    while (pAux != nullptr)
    {
        Entidades::Entidade* pEntidade = pAux->getInfo();

        if (pEntidade != nullptr)
        {
            pEntidade->executar();
        }

        pAux = pAux->getProximo();
    }
}

void ListaEntidades::desenhar() {
    Listas::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    while (pAux != nullptr) {
        Entidades::Entidade* pEntidade = pAux->getInfo();
        if (pEntidade != nullptr) {
            pEntidade->desenhar(); 
        }
        pAux = pAux->getProximo();
    }
}