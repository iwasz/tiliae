/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAE_DATASOURCE_H_
#define TILIAE_DATASOURCE_H_

#include "core/Exception.h"
#include "core/ApiMacro.h"
#include <sys/types.h>

namespace Common {

/**
 * Resource access abstraction. Regular file and Android NDK asset are both supported.
 * Read only.
 */
class TILIAE_API DataSource {
public:

        DataSource (void *userData = NULL);
        ~DataSource ();

        enum OpenMode {
            MODE_UNKNOWN      = 0,
            MODE_RANDOM       = 1,
            MODE_STREAMING    = 2,
            MODE_BUFFER       = 3
        };

        /**
         * Otwórz źródło.
         */
        void open (const char* filename, OpenMode mode = MODE_UNKNOWN);

        /**
         * Close the asset, freeing all associated resources.
         */
        void close();

        /**
         * Czytaj count elementów, z których kazdy ma size bajtów.
         * Zwraca ilość odczytanych elementów. Lub 0 jeśli błąd lub EOF.
         */
        int read (void* buf, size_t count);

        /**
         *
         */
        size_t seek (off_t offset, int whence);

        /**
         * Akt. poz. w pliku.
         */
        size_t tell ();

        /**
         * Do początku.
         */
        void rewind ();

        /**
         * Report the total size of the asset data.
         */
        size_t getLength ();

private:

        class Impl;
        Impl *impl;
};

/**
 *
 */
class TILIAE_API DataSourceException : public Core::Exception {
public:

        DataSourceException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~DataSourceException () throw () {}
};

} /* namespace Common */
#endif /* DATASOURCE_H_ */
