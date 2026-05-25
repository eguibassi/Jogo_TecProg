/*#include "ListaEntidades.h"
//"../" no include volta uma pasta, necessário para acessar arquivos em pastas diferentes.
#include "../entidades/Entidade.h"

ListaEntidades::ListaEntidades()
{
}

ListaEntidades::~ListaEntidades()
{
    LEs.limpar();
}

//Inclui uma entidade na lista.
void ListaEntidades::incluir(Entidade* pE)
{
    LEs.incluir(pE);
}

//Percorre a lista.
void ListaEntidades::percorrer()
{
    Lista::Elemento<Entidade>* pAux = LEs.getPrimeiro();

    while (pAux != nullptr)
    {
        Entidade* pEntidade = pAux->getInfo();

        if (pEntidade != nullptr)
        {
            pEntidade->executar();
        }

        pAux = pAux->getProximo();
    }
}*/