/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MACROS_H_
#define MACROS_H_

#include <iostream> // Wywalić
#include <boost/preprocessor.hpp> // TODO Zamienić na pojedyncze hedery
#include <boost/current_function.hpp>
#include "core/ApiMacro.h"

/**
 * TODO Czy da się w klasie użyć jakiegoś magicznego makra w stylu __CLASS__,
 * ktore rozwija się do nazwy klasy? __PRETTY_FUNCTION__ jakoś to pokazuje!
 *
 * TODO Zamienić przedrostki REFLECT_ na ANNOTATION_
 */

/**
 * Definicja : annotation_method : metoda generowana dla każdej metody w klasie.
 * Jest wiele takiehc metod i każda ma prefix REFLECT_ANNOTATION_METHOD_PREFIX
 */
#define REFLECT_ANNOTATION_METHOD_PREFIX __annotation_method__

/**
 * Definicja : init_method : taka metoda jest tylko jedna i inicjuje refleksję
 * dla tej klasy. Jest statyczna i można ją wywołać ręcznie, aczkolwiek każda
 * klasa z odpowiednimi adnotacjami będzie generować kod odpalający taką metodę
 * automatycznie.
 */
#define REFLECT_INIT_METHOD_NAME __init_method__

/**
 * Sposób inicjowania klas. Zawsze był tylko jeden sposób, ale można sobie
 * wyobrazić, że może być ich kilka. Każdy mechanizm ainicjowania klas
 * z adnotacjami na końcu sprowadza się do wywołania metody REFLECT_INIT_METHOD_NAME.
 */

/**
 * Stała oznaczająca automatyczne inicjowania klas z adnotacjami. Aby aktywować
 * ten sposób, REFLECT_INITIALIZATION_TYPE musi być ustawione właśnie na to.
 */
#define REFLECT_AUTOMATIC_INIT 1

/**
 * Manualny sposób (uruchamiamy na koniec wielką metodę init).
 */
#define REFLECT_MANUAL_INIT 2

/**
 * Sposób inicjowania klas.
 */
#define REFLECT_INITIALIZATION_TYPE REFLECT_AUTOMATIC_INIT

#define REFLECT_CLASS_TYPE __Clazz_Reflect_Internal__
#define REFLECT_CLASS_NAME __clazz_reflect_name__

//#define REFLECT_INIT_CHECK_NAME __init_check_function__

/****************************************************************************/

/**
 *
 */
#define DECL(z, n, data) BOOST_PP_CAT(REFLECT_ANNOTATION_METHOD_PREFIX,n)();

/**
 *
 */
#define REFLECT_GEN_BOOTSTRAP BOOST_PP_REPEAT(__COUNTER__, DECL, ~)

/*--------------------------------------------------------------------------*/

#define ANNOTATION_METHOD_HEADER_ARG_RECURENCE(n)                                                    \
                                                                                                     \
TILIAE_LOCAL static void BOOST_PP_CAT(REFLECT_ANNOTATION_METHOD_PREFIX,n) (const char *REFLECT_CLASS_NAME)        \
{                                                                                                    \
      /*std::cerr <<     REFLECT_CLASS_NAME << std::endl; */                                         \
        BOOST_PP_CAT(REFLECT_ANNOTATION_METHOD_PREFIX,BOOST_PP_DEC(n)) (REFLECT_CLASS_NAME) ;

/**
 * Generuje nagłówek metody adnotacyjnej (znajduje się na początku [każdego?] makra z jednym _)
 */
#define ANNOTATION_METHOD_HEADER_RECURENCE ANNOTATION_METHOD_HEADER_ARG_RECURENCE(__COUNTER__)

/*--------------------------------------------------------------------------*/

#define ANNOTATION_METHOD_HEADER_ARG(n)                                                          \
                                                                                                 \
TILIAE_LOCAL static void BOOST_PP_CAT(REFLECT_ANNOTATION_METHOD_PREFIX,n) (const char *REFLECT_CLASS_NAME)    \
{

/**
 * Generuje nagłówek metody adnotacyjnej (znajduje się na początku [każdego?] makra z dwoma __)
 */
#define ANNOTATION_METHOD_HEADER ANNOTATION_METHOD_HEADER_ARG(__COUNTER__)

/*--------------------------------------------------------------------------*/

/**
 * Generuje nazwę dla metody uruchamiającej cały łańcuch metod adnotacyjnych (użyte gdzieź w REFLECTION_END).
 * Uwaga! Tutaj jest __COUNTER__ pomniejszony 0 2! Ponieważ makro REFLECTION_END i _tX używają __COUNTER__ 1
 * raz (czyli zwiększenie jest o 2)!
 */
#define GEN_ANNOTATION_METHOD_TAIL_NAME BOOST_PP_CAT(REFLECT_ANNOTATION_METHOD_PREFIX,BOOST_PP_DEC(BOOST_PP_DEC(__COUNTER__)))

/**
 * Koniec klasy.
 * @arg NClazz Nazwa klasy wraz z namespace (jako identyfikator, nie jako string).
 * @arg Token Unikalna nazwa w obrębie całego projektu (nie tylko jednostki translacji).
 */
#define _e_implementation_arg(NClazz, Token)                                                  \
                                                                                              \
       public:                                                                                \
       typedef NClazz CLASS;                                                                 \
       static void REFLECT_INIT_METHOD_NAME (const char *REFLECT_CLASS_NAME)                  \
       {                                                                                      \
               GEN_ANNOTATION_METHOD_TAIL_NAME (REFLECT_CLASS_NAME);     \
       }                                                                                      \
                                                                                              \
}; /* Koniec klasy */                                                                         \
                                                                                              \
        struct Token {                                                                        \
                Token (int) {                                                                 \
                        static Token dummy;                                                   \
                        /*std::cerr << "Token(int) : " << BOOST_PP_STRINGIZE (NClazz) << ", dummy : " << (unsigned long int)&dummy << std::endl;*/     \
                }                                                                             \
                                                                                              \
                Token ()                                                                      \
                { NClazz::REFLECT_INIT_METHOD_NAME (BOOST_PP_STRINGIZE (NClazz));    \
                /*std::cerr << "Token() : " << BOOST_PP_STRINGIZE (NClazz) << std::endl;*/ }    \
        };                                                                                    \
                                                                                              \
namespace  {                                                                                   \
        static Token BOOST_PP_CAT(Token,__LINE__) (1);

/*##########################################################################*/

#define _tb_implementation_arg(Token)                                                       \
                                                                                            \
       public:                                                                              \
       typedef REFLECT_CLAZZ_TYPE CLASS;                                                                                     \
       static void REFLECT_INIT_METHOD_NAME (const char *REFLECT_CLASS_NAME)                \
       {                                                                                    \
               GEN_ANNOTATION_METHOD_TAIL_NAME <CLASS> (REFLECT_CLASS_NAME);   \
       }                                                                                    \
                                                                                            \
}; /* Koniec klasy */                                                                       \
                                                                                            \
        struct Token {                                                                      \
                Token (int)                                                                 \
                { static Token dummy; }                                                     \
                                                                                            \
                Token () {                                                                  \


#define REFLECTION_TEMPLATE_BEGIN _tb_implementation_arg(BOOST_PP_CAT(TOKEN,__COUNTER__))

#define REFLECTION_TEMPLATE(NClazz)  NClazz::REFLECT_INIT_METHOD_NAME <NClazz> (BOOST_PP_STRINGIZE (NClazz));

#define _te_implementation_arg(Token)                                                    \
}                                                                                        \
        };                                                                               \
                                                                                         \
namespace {                                                                              \
        static Token BOOST_PP_CAT(Token,__LINE__) (0);

#define REFLECTION_TEMPLATE_END _te_implementation_arg(BOOST_PP_CAT(TOKEN,BOOST_PP_DEC(BOOST_PP_DEC(__COUNTER__))))


#ifdef REFLECTION_ENABLED
#define REFLECTION_END(Clazz) _e_implementation_arg(Clazz, BOOST_PP_CAT(ServiceClass,BOOST_PP_CAT(__COUNTER__, __LINE__)))
#else
#define REFLECTION_END(Clazz)
#endif

#ifdef REFLECTION_ENABLED
#define REFLECTION_END_(Clazz) REFLECTION_CONSTRUCTOR_(void); REFLECTION_END(Clazz)
#else
#define REFLECTION_END_(Clazz)
#endif

/**
 * Implementacja dla makra ANNOTATION_RUN_ONCE_AT_STARTUP
 */
#define ANNOTATION_RUN_ONCE_AT_STARTUP_IMPL(TmpClassUp,instanceName,codeToRun)                              \
                                                                                                            \
        struct TmpClassUp {                                                                                 \
                TmpClassUp () { codeToRun }                                                                 \
                TmpClassUp (int) { static TmpClassUp dummy; }                                               \
        };                                                                                                  \
                                                                                                            \
        namespace {                                                                                         \
                static TmpClassUp instanceName (0);                                                         \
        }


/**
 * Adnotacja, które wykonuje podany w argumencie kod jeden raz przy uruchomieniu się programu.
 * Wykorzystana na przykład w REFLECTION_FACTORY
 */
#define ANNOTATION_RUN_ONCE_AT_STARTUP(codeToRun)                                                                                            \
                                                                                                                                             \
        ANNOTATION_RUN_ONCE_AT_STARTUP_IMPL(BOOST_PP_CAT(BOOST_PP_CAT(__SOME_UNIQUE_UP_CLASS_RUN_ONCE_AT_STARTUP__,__LINE__),__COUNTER__),   \
                BOOST_PP_CAT(BOOST_PP_CAT(__SOME_UNIQUE_INSTANCE_VAR_RUN_ONCE_AT_STARTUP__,__LINE__),__COUNTER__),                           \
                codeToRun)

#endif /* MACROS_H_ */
