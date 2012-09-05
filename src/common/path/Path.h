/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PATH2_468050_H
#define PATH2_468050_H

#include "IPath.h"

namespace Common {

/**
 * Ścieżka zaimplementowana jako jeden string. Pomocnicza klasa do operacji
 * na sciezkac w BeanWrapper i w Scope. Jest to
 * wlasciwie taki dekorator do , ktory dodaje do Stringa rozne
 * fajne metody, ktore ulatwiaja obrobke sciezek. Prawie kazda metoda ma
 * swoj odpowiednik statyczny, tak ze nawet nie trzeba tworzyc obiektu typu
 * Path.
 *
 * Sciezki to poprostu stringi skladajace sie z nazw rozdzielonych kropkami.
 * Kazda taka nazwa jest tutaj okreslana jako jeden *segment*.
 *
 * Separatory na końcu i na początku są ignorowane.
 */
class TILIAE_API Path : public IPath {
public:

        /**
         * @param path String representing the path.
         * @param separator Separator, defaults to ".".
         */
        Path (const std::string &path, char separator = '.');
        Path (const Path &p);

        std::string toString () const;
        operator std::string const & () const { return body; }

        /**
         *  \todo Moze zamiast validate dac metode isEmpty i zalozyc, ze nie da sie
         *  stworzyc niewalidujacej sie sciezki, ale dopuscic puste sciezki? Przeciez
         *  jak mamy dobra sciezke i uzyjemy cut, tak zeby wyciac wszystkie elementy?
         *  No to bedzie pusta, czyli validate bedzie false. Alternatywnie, metody
         *  cut moga nic nie robic gdy liczba segmentow jest rowna 1.
         */
        bool validate () const;
        int countSegments () const;
        void clear () { body = ""; }

        void cutSegment (unsigned int index);
        void cutSegment (const std::string &segmentName);
        void cutAllSegments (const std::string &segmentName);
        void cutLastSegment ();
        void cutFirstSegment ();
        void cutAllButLastSegment ();
        void cutAllButFirstSegment ();

        int segmentStringPosition (const std::string &segmentName) const;
        int segmentStringPosition (int number) const;
        int findSegmentIndex (const std::string &segmentName) const;
        bool containsSegment (const std::string &segmentName) const;

        std::string getSegment (unsigned int number) const;
        std::string getLastSegment () const;
        std::string getFirstSegment () const { return firstSegmentCache; }
        std::string getAllButLastSegment () const;
        std::string getAllButFirstSegment () const;
        Core::StringVector splitSegments () const;

        bool isRelative () const;
        bool isAbsolute () const;

private:

        // Optymalizacja.
        void updateFirstSegmentCache () const;

private:

        std::string body; // Stripped and leading and trailing separators cut
        std::string original; // Unchanged string passed into constructor.
        std::string separatorStr;
        char separator;
        mutable std::string firstSegmentCache;

};

} // namespace

#endif

