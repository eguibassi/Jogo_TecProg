#include "ListaEntidades.h"
#include "../Entidades/Entidade.h"

using namespace Listas;

ListaEntidades::ListaEntidades()
{
}

ListaEntidades::~ListaEntidades()
{
    LEs.limpar();
}

void ListaEntidades::incluir(Entidades::Entidade* pE)
{
    LEs.incluir(pE);
}

void ListaEntidades::percorrer()
{
    Listas::Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

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

void ListaEntidades::salvar()
{
    Listas::Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    while (pAux != nullptr)
    {
        Entidades::Entidade* pEntidade = pAux->getInfo();

        if (pEntidade != nullptr)
        {
            pEntidade->salvar();
        }

        pAux = pAux->getProximo();
    }
}

void ListaEntidades::desenhar()
{
    Listas::Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    while (pAux != nullptr)
    {
        Entidades::Entidade* pEntidade = pAux->getInfo();

        if (pEntidade != nullptr)
        {
            pEntidade->desenhar();
        }

        pAux = pAux->getProximo();
    }
}
bool ListaEntidades::InimsDerr() const{
    Listas::Lista<Entidades::Entidade>::Elemento<Entidades::Entidade>* pAux = LEs.getPrimeiro();

    bool encontrouInimigo = false;

    while (pAux != nullptr)
    {
        Entidades::Entidade* pEntidade = pAux->getInfo();

        if (pEntidade != nullptr)
        {
            Personagens::Inimigo* pInimigo = dynamic_cast<Personagens::Inimigo*>(pEntidade);

            if (pInimigo != nullptr)
            {
                encontrouInimigo = true;

                if (pInimigo->getAtivo())
                {
                    return false;
                }
            }
        }

        pAux = pAux->getProximo();
    }

    return encontrouInimigo;
}
