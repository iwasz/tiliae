/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_H_
#define TILIAE_H_

#include "core/Core.h"
#include "beanWrapper/BeanWrapper.h"
#include "common/Common.h"
#include "reflection/Reflection.h"
#include "editor/Editor.h"
#include "factory/Factory.h"
#include "k202/K202.h"
#include "signal/Signal.h"
//#include "stateMachine/StateMachine.h"
#include "container/Container.h"

/**
 * \mainpage
 * \section Podstrony
 * - \ref Core
 *  - \ref String
 *  - \ref Variant
 *  - \ref CoreAPI
 * - \ref Reflection
 * - \ref Factory
 * - \ref Editor
 * - \ref BeanWrapper
 * - \ref Kontener
 *
 * \section Zawieranie
 * \subsection MainPliki Pliki nagłówkowe
 * W projektach używających tiliae inkludujemy plik Tiliae.h (można próbować go prekompilować do gch),
 * albo poszczególne pliki podprojektów. Ścieżka -I jest tylko do głównego katalogu tiliae, więc inkludując
 * poszczególne pliki nagłówkowe inne niż Tiliae.h) podajemy ścieżkę zależną od katalogu w którym jest
 * Tiliae.h. Na przykład:
 *
 * <pre>
 * #include <Tiliae.h>
 *
 * // Ale już poszczególne pliki podprojektów:
 * #include <container/Container.h>
 * </pre>

 * \section Budowanie
 * <pre>
 * cmake .
 * make -j8
 * make install
 * </pre>
 *
 * \section Zaleznosci Zależności między modułami
 * Zależności staram się, żeby były 1 do 1, czyli każda następna biblioteka (moduł) jest zależna tylko
 * od 1 biblioteki. Przez bibliotekę rozumiem podkatalogi katalogu src. Zależności idą tak jak zmienne
 * w pliku CMakeLists.txt (od najbardziej podstawowego, czyli core - ktore nie zależy od żadnego innego
 * modułu, do container, ktory zależy bezpośrednio od xml, a pośrednio od wszystkich innych) :
 *
 * - core
 * - common
 * - reflection
 * - factory
 * - editor
 * - bean_wrapper
 * - k202
 * - signal
 * - state_machine
 * - xml
 * - container
*/

#	endif /* TILIAE_H_ */
