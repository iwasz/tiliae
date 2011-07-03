/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Manager.h"

/****************************************************************************/

//using namespace Core;

/****************************************************************************/

namespace Reflection {

void init ()
{
        // Dodaje niezaadnotowane typy takie jak String, bool, int etc.
//        addStandardTypes ();
        Reflection::Manager::init ();
}

}
