#include "ListaEntidades.h"
//"../" no include volta uma pasta, necessário para acessar arquivos em pastas diferentes.
#include "../entidades/Entidade.h"

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