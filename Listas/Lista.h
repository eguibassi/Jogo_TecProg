#pragma once

// Template inspirado no slide 10A de conceitos avançados de C++ 
//https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/LinguagemC++UML/Fundamentos2-SlidesC++10B-2020-07-20.pdf
// Elemento fica dentro de Lista, como no UML

namespace Listas
{
    template <class TL>
    class Lista
    {
    public:
        template <class TE>
        class Elemento
        {
        private:
            Elemento<TE>* pProx;
            TE* pInfo;

        public:
            Elemento();
            ~Elemento();

            //Coloca a informação dentro do elemento
            void incluir(TE* p);
            //Define o próximo elemento
            void setProx(Elemento<TE>* pE);
            Elemento<TE>* getProximo() const;
            TE* getInfo() const;
        };

    private:
        Elemento<TL>* pPrimeiro;
        Elemento<TL>* pUltimo;

    public:
        Lista();
        ~Lista();

        //Adiciona um elemtno no FINAL da lista
        void incluir(TL* p);
        //Apaga os elementos da lista
        void limpar();

        Elemento<TL>* getPrimeiro() const;
        Elemento<TL>* getUltimo() const;
    };


    template <class TL>
    template <class TE>
    Lista<TL>::Elemento<TE>::Elemento()
    {
        pProx = nullptr;
        pInfo = nullptr;
    }

    template <class TL>
    template <class TE>
    Lista<TL>::Elemento<TE>::~Elemento()
    {
        pProx = nullptr;
        pInfo = nullptr;
    }

    template <class TL>
    template <class TE>
    void Lista<TL>::Elemento<TE>::incluir(TE* p)
    {
        pInfo = p;
    }

    template <class TL>
    template <class TE>
    void Lista<TL>::Elemento<TE>::setProx(Elemento<TE>* pE)
    {
        pProx = pE;
    }

    template <class TL>
    template <class TE>
    typename Lista<TL>::template Elemento<TE>* Lista<TL>::Elemento<TE>::getProximo() const
    {
        return pProx;
    }

    template <class TL>
    template <class TE>
    TE* Lista<TL>::Elemento<TE>::getInfo() const
    {
        return pInfo;
    }


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
    typename Lista<TL>::template Elemento<TL>* Lista<TL>::getPrimeiro() const
    {
        return pPrimeiro;
    }

    template <class TL>
    typename Lista<TL>::template Elemento<TL>* Lista<TL>::getUltimo() const
    {
        return pUltimo;
    }
}