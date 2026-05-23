#pragma once
#include "Elemento.h"

// Template inspirado no slide 10A de conceitos avançados de c++, disponível em:
// https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/Fundamentos2.htm

namespace Listas
{
    template <class TL>
    class Lista
    {
    private:
        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;

    public:
        Lista();
        ~Lista();

        void incluir(TL* p);
        void limpar();

        Elemento<TL>* getPrimeiro() const;
        Elemento<TL>* getUltimo() const;
    };

    template <class TL>
    Lista<TL>::Lista()
    {
        pPrimeiro = nullptr;
        pUltimo = nullptr;
    }

    template <class TL>
    Lista<TL>::~Lista()
    {
        limpar();
    }

    template <class TL>
    void Lista<TL>::incluir(TL* p)
    {
        if (p == nullptr)
        {
            return;
        }

        Elemento<TL>* pNovo = new Elemento<TL>();
        pNovo->incluir(p);

        if (pPrimeiro == nullptr)
        {
            pPrimeiro = pNovo;
            pUltimo = pNovo;
        }
        else
        {
            pUltimo->setProx(pNovo);
            pUltimo = pNovo;
        }
    }

    template <class TL>
    void Lista<TL>::limpar()
    {
        Elemento<TL>* pAux = pPrimeiro;
        Elemento<TL>* pProx = nullptr;

        while (pAux != nullptr)
        {
            pProx = pAux->getProximo();

            delete pAux;

            pAux = pProx;
        }

        pPrimeiro = nullptr;
        pUltimo = nullptr;
    }

    template <class TL>
    Elemento<TL>* Lista<TL>::getPrimeiro() const
    {
        return pPrimeiro;
    }

    template <class TL>
    Elemento<TL>* Lista<TL>::getUltimo() const
    {
        return pUltimo;
    }
}