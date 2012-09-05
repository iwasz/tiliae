/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Core.h"
#include <iostream>

using namespace std::tr1;
using namespace Core;

struct A {
        A (int j = 0) : i (j) {}
        bool operator == (A const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, A const &a) { s << "A(" << a.i << ")"; return s; }

// Niekompletny, zdefiniowany dopiero na końcu.
class I;
extern I globalI;
extern shared_ptr <I> globalP;

struct B : public Object {
        virtual ~B () {}
        B (int j = 0) : i (j) {}
        bool operator == (B const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, B const &a) { s << "B(" << a.i << ")"; return s; }

struct C : public B {
        virtual ~C () {}
        C (int j = 0) : i (j) {}
        bool operator == (C const &a) const { return a.i == i; }
        int i;
};

std::ostream &operator << (std::ostream &s, C const &a) { s << "C(" << a.i << ")"; return s; }

int main (int, char **)
{
        {
                bool d = true;
                Variant v (d);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                bool const d = true;
                Variant v (d);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                bool d = true;
                bool *pd = &d;
                Variant v (pd);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                bool d = true;
                bool const *cpd = &d;
                Variant v (cpd);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                bool d = true;
                bool &rd = d;
                Variant v (rd);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                bool d = true;
                bool const &crd = d;
                Variant v (crd);
                vcast <bool> (v);
                vcast <bool *> (v);
                vcast <bool const *> (v);
                vcast <bool &> (v);
                vcast <bool const &> (v);
        }

        {
                char d = 'a';
                Variant v (d);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                char const d = 'a';
                Variant v (d);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                char d = 'a';
                char *pd = &d;
                Variant v (pd);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                char d = 'a';
                char const *cpd = &d;
                Variant v (cpd);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                char d = 'a';
                char &rd = d;
                Variant v (rd);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                char d = 'a';
                char const &crd = d;
                Variant v (crd);
                vcast <char> (v);
                vcast <char *> (v);
                vcast <char const *> (v);
                vcast <char &> (v);
                vcast <char const &> (v);
        }

        {
                unsigned char d = 129;
                Variant v (d);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                unsigned char const d = 129;
                Variant v (d);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                unsigned char d = 129;
                unsigned char *pd = &d;
                Variant v (pd);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                unsigned char d = 129;
                unsigned char const *cpd = &d;
                Variant v (cpd);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                unsigned char d = 129;
                unsigned char &rd = d;
                Variant v (rd);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                unsigned char d = 129;
                unsigned char const &crd = d;
                Variant v (crd);
                vcast <unsigned char> (v);
                vcast <unsigned char *> (v);
                vcast <unsigned char const *> (v);
                vcast <unsigned char &> (v);
                vcast <unsigned char const &> (v);
        }

        {
                double d = 666.0;
                Variant v (d);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                double const d = 666.0;
                Variant v (d);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                double d = 666.0;
                double *pd = &d;
                Variant v (pd);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                double d = 666.0;
                double const *cpd = &d;
                Variant v (cpd);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                double d = 666.0;
                double &rd = d;
                Variant v (rd);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                double d = 666.0;
                double const &crd = d;
                Variant v (crd);
                vcast <double> (v);
                vcast <double *> (v);
                vcast <double const *> (v);
                vcast <double &> (v);
                vcast <double const &> (v);
        }

        {
                long double d = 666.0;
                Variant v (d);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                long double const d = 666.0;
                Variant v (d);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                long double d = 666.0;
                long double *pd = &d;
                Variant v (pd);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                long double d = 666.0;
                long double const *cpd = &d;
                Variant v (cpd);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                long double d = 666.0;
                long double &rd = d;
                Variant v (rd);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                long double d = 666.0;
                long double const &crd = d;
                Variant v (crd);
                vcast <long double> (v);
                vcast <long double *> (v);
                vcast <long double const *> (v);
                vcast <long double &> (v);
                vcast <long double const &> (v);
        }

        {
                float d = 666.0;
                Variant v (d);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                float const d = 666.0;
                Variant v (d);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                float d = 666.0;
                float *pd = &d;
                Variant v (pd);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                float d = 666.0;
                float const *cpd = &d;
                Variant v (cpd);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                float d = 666.0;
                float &rd = d;
                Variant v (rd);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                float d = 666.0;
                float const &crd = d;
                Variant v (crd);
                vcast <float> (v);
                vcast <float *> (v);
                vcast <float const *> (v);
                vcast <float &> (v);
                vcast <float const &> (v);
        }

        {
                int d = 667;
                Variant v (d);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                int const d = 667;
                Variant v (d);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                int d = 667;
                int *pd = &d;
                Variant v (pd);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                int d = 667;
                int const *cpd = &d;
                Variant v (cpd);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                int d = 667;
                int &rd = d;
                Variant v (rd);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                int d = 667;
                int const &crd = d;
                Variant v (crd);
                vcast <int> (v);
                vcast <int *> (v);
                vcast <int const *> (v);
                vcast <int &> (v);
                vcast <int const &> (v);
        }

        {
                unsigned int d = 667;
                Variant v (d);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                unsigned int const d = 667;
                Variant v (d);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                unsigned int d = 667;
                unsigned int *pd = &d;
                Variant v (pd);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                unsigned int d = 667;
                unsigned int const *cpd = &d;
                Variant v (cpd);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                unsigned int d = 667;
                unsigned int &rd = d;
                Variant v (rd);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                unsigned int d = 667;
                unsigned int const &crd = d;
                Variant v (crd);
                vcast <unsigned int> (v);
                vcast <unsigned int *> (v);
                vcast <unsigned int const *> (v);
                vcast <unsigned int &> (v);
                vcast <unsigned int const &> (v);
        }

        {
                long int d = 667;
                Variant v (d);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                long int const d = 667;
                Variant v (d);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                long int d = 667;
                long int *pd = &d;
                Variant v (pd);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                long int d = 667;
                long int const *cpd = &d;
                Variant v (cpd);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                long int d = 667;
                long int &rd = d;
                Variant v (rd);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                long int d = 667;
                long int const &crd = d;
                Variant v (crd);
                vcast <long int> (v);
                vcast <long int *> (v);
                vcast <long int const *> (v);
                vcast <long int &> (v);
                vcast <long int const &> (v);
        }

        {
                unsigned long int d = 667;
                Variant v (d);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                unsigned long int const d = 667;
                Variant v (d);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                unsigned long int d = 667;
                unsigned long int *pd = &d;
                Variant v (pd);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                unsigned long int d = 667;
                unsigned long int const *cpd = &d;
                Variant v (cpd);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                unsigned long int d = 667;
                unsigned long int &rd = d;
                Variant v (rd);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                unsigned long int d = 667;
                unsigned long int const &crd = d;
                Variant v (crd);
                vcast <unsigned long int> (v);
                vcast <unsigned long int *> (v);
                vcast <unsigned long int const *> (v);
                vcast <unsigned long int &> (v);
                vcast <unsigned long int const &> (v);
        }

        {
                short int d = 667;
                Variant v (d);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                short int const d = 667;
                Variant v (d);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                short int d = 667;
                short int *pd = &d;
                Variant v (pd);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                short int d = 667;
                short int const *cpd = &d;
                Variant v (cpd);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                short int d = 667;
                short int &rd = d;
                Variant v (rd);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                short int d = 667;
                short int const &crd = d;
                Variant v (crd);
                vcast <short int> (v);
                vcast <short int *> (v);
                vcast <short int const *> (v);
                vcast <short int &> (v);
                vcast <short int const &> (v);
        }

        {
                unsigned short int d = 667;
                Variant v (d);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                unsigned short int const d = 667;
                Variant v (d);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                unsigned short int d = 667;
                unsigned short int *pd = &d;
                Variant v (pd);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                unsigned short int d = 667;
                unsigned short int const *cpd = &d;
                Variant v (cpd);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                unsigned short int d = 667;
                unsigned short int &rd = d;
                Variant v (rd);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                unsigned short int d = 667;
                unsigned short int const &crd = d;
                Variant v (crd);
                vcast <unsigned short int> (v);
                vcast <unsigned short int *> (v);
                vcast <unsigned short int const *> (v);
                vcast <unsigned short int &> (v);
                vcast <unsigned short int const &> (v);
        }

        {
                wchar_t d = L'a';
                Variant v (d);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                wchar_t const d = L'a';
                Variant v (d);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                wchar_t d = L'a';
                wchar_t *pd = &d;
                Variant v (pd);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                wchar_t d = L'a';
                wchar_t const *cpd = &d;
                Variant v (cpd);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                wchar_t d = L'a';
                wchar_t &rd = d;
                Variant v (rd);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                wchar_t d = L'a';
                wchar_t const &crd = d;
                Variant v (crd);
                vcast <wchar_t> (v);
                vcast <wchar_t *> (v);
                vcast <wchar_t const *> (v);
                vcast <wchar_t &> (v);
                vcast <wchar_t const &> (v);
        }

        {
                std::string d = "alakot";
                Variant v (d);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                std::string const d = "alakot";
                Variant v (d);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                std::string d = "alakot";
                std::string *pd = &d;
                Variant v (pd);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                std::string d = "alakot";
                std::string const *cpd = &d;
                Variant v (cpd);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                std::string d = "alakot";
                std::string &rd = d;
                Variant v (rd);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                std::string d = "alakot";
                std::string const &crd = d;
                Variant v (crd);
                vcast <std::string> (v);
                vcast <std::string *> (v);
                vcast <std::string const *> (v);
                vcast <std::string &> (v);
                vcast <std::string const &> (v);
        }

        {
                Core::String d = "alakot";
                Variant v (d);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                Core::String const d = "alakot";
                Variant v (d);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                Core::String d = "alakot";
                Core::String *pd = &d;
                Variant v (pd);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                Core::String d = "alakot";
                Core::String const *cpd = &d;
                Variant v (cpd);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                Core::String d = "alakot";
                Core::String &rd = d;
                Variant v (rd);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                Core::String d = "alakot";
                Core::String const &crd = d;
                Variant v (crd);
                vcast <Core::String> (v);
                vcast <Core::String *> (v);
                vcast <Core::String const *> (v);
                vcast <Core::String &> (v);
                vcast <Core::String const &> (v);
        }

        {
                A a (668);
                Variant v (a); // Tworzy handler POINTER_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                A const a (668);
                Variant v (a); // Tworzy handler POINTER_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                A a (668);
                A *pa = &a;
                Variant v (pa); // Tworzy handler POINTER
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                A a (668);
                A &ra = a;
                Variant v (ra); // Tworzy handler POINTER_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                A const a (668);
                A const *cpa = &a;
                Variant v (cpa); // Tworzy handler POINTER_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                vcast <shared_ptr<A const> > (v);
        }

        {
                shared_ptr <A> a (new A (668));
                Variant v (a); // Tworzy handler SMART
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                (vcast <shared_ptr<A> > (v));
                (vcast <shared_ptr<A const> > (v));
        }

        {
                shared_ptr <A const> a (new A (668));
                Variant v (a); // Tworzy handler SMART_CONST
                vcast <A> (v);
                vcast <A *> (v);
                vcast <A const *> (v);
                vcast <A &> (v);
                vcast <A const &> (v);
                vcast <shared_ptr<A> > (v);
                (vcast <shared_ptr<A const> > (v));
        }

        {
                I *pa = (I *)0x01;
                Variant v (pa); // Tworzy handler POINTER
                vcast <I *> (v);
                vcast <I const *> (v);
                &(vcast <I &> (v));
                &(vcast <I const &> (v));
                vcast <shared_ptr<I> > (v);
                vcast <shared_ptr<I const> > (v);
        }

        {
                I const*pa = (I *)0x01;
                Variant v (pa); // Tworzy handler CONST_POINTER
                vcast <I *> (v);
                vcast <I const *> (v);
                vcast <I &> (v);
                &(vcast <I const &> (v));
                vcast <shared_ptr<I> > (v);
                vcast <shared_ptr<I const> > (v);
        }

        {
                extern I &func (void);
                Variant v (func ()); // Tworzy handler CONST_POINTER bo referencja
                vcast <I *> (v);
                vcast <I const *> (v);
                vcast <I &> (v);
                &(vcast <I const &> (v));
                vcast <shared_ptr<I> > (v);
                vcast <shared_ptr<I const> > (v);
        }

        {
                extern I const &func2 (void);
                Variant v (func2 ()); // Tworzy handler CONST_POINTER bo referencja
                vcast <I *> (v);
                vcast <I const *> (v);
                vcast <I &> (v);
                &(vcast <I const &> (v));
                vcast <shared_ptr<I> > (v);
                vcast <shared_ptr<I const> > (v);
        }

        {
                extern shared_ptr<I> func3 ();
                Variant v (func3 ()); // Tworzy handler SMART
                vcast <I *> (v);
                vcast <I const *> (v);
                &(vcast <I &> (v));
                &(vcast <I const &> (v));
                (vcast <shared_ptr<I> > (v));
                (vcast <shared_ptr<I const> > (v));
        }

        {
                extern shared_ptr<I const> func4 ();
                Variant v (func4 ()); // Tworzy handler CONST_SMART
                vcast <I *> (v);
                vcast <I const *> (v);
                vcast <I &> (v);
                &(vcast <I const &> (v));
                vcast <shared_ptr<I> > (v);
                (vcast <shared_ptr<I const> > (v));
        }

        {
                C a (668);
                Variant v (a); // Tworzy handler POINTER_CONST
                &(ocast <B> (v));
                ocast <B *> (v);
                ocast <B const *> (v);
                ocast <B &> (v);
                &(ocast <B const &> (v));
                ocast <shared_ptr<B> > (v);
                ocast <shared_ptr<B const> > (v);
        }

        {
                C const a (668);
                Variant v (a); // Tworzy handler POINTER_CONST
                ocast <B> (v);
                ocast <B *> (v);
                ocast <B const *> (v);
                ocast <B &> (v);
                ocast <B const &> (v);
                ocast <shared_ptr<B> > (v);
                ocast <shared_ptr<B const> > (v);
        }

        /****************************************************************************/



        {
                C c (668);
                Variant v (&c); // Tworzy handler OBJECT
                &(ocast <B> (v));
                ocast <B *> (v);
                ocast <B const *> (v);
                ocast <B &> (v);
                ocast <B const &> (v);
                ocast <shared_ptr<B> > (v);
                ocast <shared_ptr<B const> > (v);
        }

        {
                C c (668);
                B &b = c;
                Variant v (&b);
                ocast <C> (v);
        }
}

class I { int i; };
I globalI;
shared_ptr <I> globalP (new I);

I &func () { return globalI; }
I const &func2 () { return globalI; }
shared_ptr<I> func3 () { return globalP; }
shared_ptr<I const> func4 () { return globalP; }
