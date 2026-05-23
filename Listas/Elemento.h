#pragma once

// Template inspirado no slide 10A de conceitos avançados de c++, disponível em:
// https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/Fundamentos2.htm

namespace Listas{
    template <class TE>
    class Elemento
    {
    private:
        Elemento<TE>* pProx;
        TE* pInfo;

    public:
        Elemento();
        ~Elemento();

        void incluir(TE* p);
        void setProx(Elemento<TE>* pE);
        Elemento<TE>* getProximo() const;
        TE* getInfo() const;
    };

    template <class TE>
    Elemento<TE>::Elemento()
    {
        pProx = nullptr;
        pInfo = nullptr;
    }

    template <class TE>
    Elemento<TE>::~Elemento()
    {
        pProx = nullptr;
        pInfo = nullptr;
    }

    template <class TE>
    void Elemento<TE>::incluir(TE* p)
    {
        pInfo = p;
    }

    template <class TE>
    void Elemento<TE>::setProx(Elemento<TE>* pE)
    {
        pProx = pE;
    }

    template <class TE>
    Elemento<TE>* Elemento<TE>::getProximo() const
    {
        return pProx;
    }

    template <class TE>
    TE* Elemento<TE>::getInfo() const
    {
        return pInfo;
    }
}