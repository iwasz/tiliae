/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef APIMACRO_H_
#define APIMACRO_H_

/*
 * From : http://gcc.gnu.org/wiki/Visibility
 */

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define TILIAE_HELPER_DLL_IMPORT __declspec(dllimport)
  #define TILIAE_HELPER_DLL_EXPORT __declspec(dllexport)
  #define TILIAE_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define TILIAE_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
    #define TILIAE_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
    #define TILIAE_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TILIAE_HELPER_DLL_IMPORT
    #define TILIAE_HELPER_DLL_EXPORT
    #define TILIAE_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define TILIAE_API and TILIAE_LOCAL.
// TILIAE_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// TILIAE_LOCAL is used for non-api symbols.

#ifdef TILIAE_DLL // defined if TILIAE is compiled as a DLL
  #ifdef TILIAE_DLL_EXPORTS // defined if we are building the TILIAE DLL (instead of using it)
    #define TILIAE_API TILIAE_HELPER_DLL_EXPORT
  #else
    #define TILIAE_API TILIAE_HELPER_DLL_IMPORT
  #endif // TILIAE_DLL_EXPORTS
  #define TILIAE_LOCAL TILIAE_HELPER_DLL_LOCAL
#else // TILIAE_DLL is not defined: this means TILIAE is a static lib.
  #define TILIAE_API
  #define TILIAE_LOCAL
#endif // TILIAE_DLL

#	endif /* APIMACRO_H_ */
