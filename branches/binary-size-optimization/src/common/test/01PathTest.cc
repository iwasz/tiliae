/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#define BOOST_TEST_MODULE CommonTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/test/test_case_template.hpp>

#include "../path/Path.h"
#include "../path/ListPath.h"

bool operator== (const Common::IPath &a, const std::string &b) { return a.toString () == b; }
bool operator== (const std::string &a, const Common::IPath &b) { return a == b.toString (); }

BOOST_AUTO_TEST_SUITE (PathsTest);

using namespace Common;
typedef boost::mpl::list <Common::Path, Common::ListPath> TestTypes;

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testValidate, Path, TestTypes)
{
        Path *p = NULL;

        p = new Path ("ala");
        BOOST_CHECK (p->validate () == true);
        delete p;

        p = new Path ("ala.ma");
        BOOST_CHECK (p->validate () == true);
        delete p;

        p = new Path ("ala.ma.kota");
        BOOST_CHECK (p->validate () == true);
        delete p;

        p = new Path ("");
        BOOST_CHECK (p->validate () == true);
        delete p;

        // Separatory na końcu i na początku są ignorowane.
//        BOOST_CHECK_THROW (p = new Path ("ala.ma."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala.ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala..ma"), PathException);
//        BOOST_CHECK_THROW (p = new Path ("."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".."), PathException);
        BOOST_CHECK_THROW (p = new Path ("......"), PathException);
        BOOST_CHECK_THROW (p = new Path ("..ala.ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala...ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.ma.."), PathException);
//        BOOST_CHECK_THROW (p = new Path ("ala."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala"), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala."), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.."), PathException);
        BOOST_CHECK_THROW (p = new Path ("..ala"), PathException);
        BOOST_CHECK_THROW (p = new Path (".ala.ma..ala"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.ma..ala."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".a"), PathException);
//        BOOST_CHECK_THROW (p = new Path ("a."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".a."), PathException);
        BOOST_CHECK_THROW (p = new Path ("a..b"), PathException);
//        BOOST_CHECK_THROW (p = new Path ("ala.ma."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala.ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala..ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("..ala.ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala...ma"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.ma.."), PathException);
//        BOOST_CHECK_THROW (p = new Path ("ala."), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala"), PathException);
//        BOOST_CHECK_THROW (p = new Path (".ala."), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.."), PathException);
        BOOST_CHECK_THROW (p = new Path ("..ala"), PathException);
        BOOST_CHECK_THROW (p = new Path (".ala.ma..ala"), PathException);
        BOOST_CHECK_THROW (p = new Path ("ala.ma..ala."), PathException);


//        throw Core::Exception ("test");
//        throw boost::execution_exception (boost::execution_exception::system_fatal_error, "SegF");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testfindSegmentIndex, Path, TestTypes)
{
        // Brzegowy
        Path p1 ("alama kota, kot ma ale");
        BOOST_CHECK (p1.countSegments () == 1);

        // Brzegowy 2
        Path p2 ("khfdashsj*(&*(&KLSDJFSDKLJFSKL784343754373,,,<><<?<??");
        BOOST_CHECK (p2.countSegments () == 1);

        Path p3 ("ala.makota");
        BOOST_CHECK (p3.countSegments () == 2);

        Path p4 ("ala.makota");
        BOOST_CHECK (p4.countSegments () == 2);

        Path p5 ("ala.makota.a.a.a.a.a.a.a.a.a.a");
        BOOST_CHECK (p5.countSegments () == 12);

        Path p6 ("");
        BOOST_CHECK (p6.countSegments () == 0);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testClear, Path, TestTypes)
{
        Path p1 ("alama kota, kot ma ale");
        p1.clear ();
        BOOST_CHECK (p1 == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutSegmentA, Path, TestTypes)
{
        Path *p = NULL;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (0);
        BOOST_CHECK (*p == "asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (1);
        BOOST_CHECK (*p == "kocham.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (2);
        BOOST_CHECK (*p == "kocham.asie.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (3);
        BOOST_CHECK (*p == "kocham.asie.ala.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (4);
        BOOST_CHECK (*p == "kocham.asie.ala.ma");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (5);
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (-1);
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (6);
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (-100);
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (0);
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (1);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (-1);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (2);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (-2);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (100);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (-100);
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("");
        p->cutSegment (-100);
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("");
        p->cutSegment (100);
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("");
        p->cutSegment (0);
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("");
        p->cutSegment (1);
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("");
        p->cutSegment (-1);
        BOOST_CHECK (*p == "");
        delete p;
}

/****************************************************************************/

/**
 *  To jest test wersji cutSegment, ktora przyjmuje nazwe segmentu, a nie jego
 *  numer.
 */
BOOST_AUTO_TEST_CASE_TEMPLATE (testCutSegmentB, Path, TestTypes)
{
        Path *p = NULL;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("kocham");
        BOOST_CHECK (*p == "asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("asie");
        BOOST_CHECK (*p == "kocham.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("ala");
        BOOST_CHECK (*p == "kocham.asie.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("ma");
        BOOST_CHECK (*p == "kocham.asie.ala.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("kota");
        BOOST_CHECK (*p == "kocham.asie.ala.ma");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("sjhfdskldjf");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("koch");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("am.as");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("ocha");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment ("");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;

        p = new Path ("kocham.asie.ala.ma.kota");
        p->cutSegment (".");
        BOOST_CHECK (*p == "kocham.asie.ala.ma.kota");
        delete p;



        p = new Path ("alamakota");
        p->cutSegment ("alamakota");
        BOOST_CHECK (*p == "");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment ("kfakldhfsklhfgsjhfd");
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment ("shf");
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (".");
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment ("");
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment (".a");
        BOOST_CHECK (*p == "alamakota");
        delete p;

        p = new Path ("alamakota");
        p->cutSegment ("ala");
        BOOST_CHECK (*p == "alamakota");
        delete p;



        Path p2 ("kocham.asie.asie.asie.ala.ma.kota");
        p2.cutSegment ("asie");
        BOOST_CHECK (p2 == "kocham.asie.asie.ala.ma.kota");

        p2.cutSegment ("asie");
        BOOST_CHECK (p2 == "kocham.asie.ala.ma.kota");

        p2.cutSegment ("asie");
        BOOST_CHECK (p2 == "kocham.ala.ma.kota");



        Path p3 ("");
        p3.cutSegment ("asie");
        BOOST_CHECK (p3 == "");

        p3.cutSegment ("");
        BOOST_CHECK (p3 == "");

        p3.cutSegment (".");
        BOOST_CHECK (p3 == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE (testsegmentStringPositionByNumber)
{
        Common::Path p1 ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p1.segmentStringPosition (0) == 0);
        BOOST_CHECK (p1.segmentStringPosition (1) == 7);
        BOOST_CHECK (p1.segmentStringPosition (2) == 12);
        BOOST_CHECK (p1.segmentStringPosition (3) == 16);
        BOOST_CHECK (p1.segmentStringPosition (4) == 19);
        BOOST_CHECK (p1.segmentStringPosition (5) == -1);
        BOOST_CHECK (p1.segmentStringPosition (6) == -1);
        BOOST_CHECK (p1.segmentStringPosition (893276) == -1);
        BOOST_CHECK (p1.segmentStringPosition (-1) == -1);
        BOOST_CHECK (p1.segmentStringPosition (-18934) == -1);

        Path p2 ("kocham");
        BOOST_CHECK (p2.segmentStringPosition (0) == 0);
        BOOST_CHECK (p2.segmentStringPosition (1) == -1);
        BOOST_CHECK (p2.segmentStringPosition (2) == -1);
        BOOST_CHECK (p2.segmentStringPosition (3) == -1);
        BOOST_CHECK (p2.segmentStringPosition (10) == -1);
        BOOST_CHECK (p2.segmentStringPosition (-1) == -1);

        Path p3 ("");
        BOOST_CHECK (p3.segmentStringPosition (0) == -1);
        BOOST_CHECK (p3.segmentStringPosition (1) == -1);
        BOOST_CHECK (p3.segmentStringPosition (2) == -1);
        BOOST_CHECK (p3.segmentStringPosition (-1) == -1);
}

/****************************************************************************/

/**
 *  Find segment position z nazwa
 */
BOOST_AUTO_TEST_CASE (testsegmentStringPositionBySegmentName)
{
        Common::Path p1 ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p1.segmentStringPosition ("kocham") == 0);
        BOOST_CHECK (p1.segmentStringPosition ("asie") == 7);
        BOOST_CHECK (p1.segmentStringPosition ("ala") == 12);
        BOOST_CHECK (p1.segmentStringPosition ("ma") == 16);
        BOOST_CHECK (p1.segmentStringPosition ("kota") == 19);
        BOOST_CHECK (p1.segmentStringPosition ("psa") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("zosie") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("asie.") == -1);
        BOOST_CHECK (p1.segmentStringPosition (".asie") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("koch") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("asi") == -1);
        BOOST_CHECK (p1.segmentStringPosition ("kot") == -1);

        Path p2 ("kocham");
        BOOST_CHECK (p2.segmentStringPosition ("kocham") == 0);
        BOOST_CHECK (p2.segmentStringPosition ("kocha") == -1);
        BOOST_CHECK (p2.segmentStringPosition ("") == -1);
        BOOST_CHECK (p2.segmentStringPosition ("89754328975897345732hdfsjdf") == -1);

        Path p3 ("");
        BOOST_CHECK (p3.segmentStringPosition ("kupa") == -1);
        BOOST_CHECK (p3.segmentStringPosition ("sikushfdsjdfdgsjdggshdgsdgf") == -1);
        BOOST_CHECK (p3.segmentStringPosition ("") == -1);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutAllSegments, Path, TestTypes)
{
        Path p01 ("kocham.asie.asie.asie.asie.asie.asie.ala.ma.kota");
        p01.cutAllSegments ("asie");
        BOOST_CHECK (p01 == "kocham.ala.ma.kota");

        Path p02 ("kocham.asie.asie.ala.ma.kota");
        p02.cutAllSegments ("asie");
        BOOST_CHECK (p02 == "kocham.ala.ma.kota");

        Path p03 ("kocham.asie.ala.ma.kota");
        p03.cutAllSegments ("asie");
        BOOST_CHECK (p03 == "kocham.ala.ma.kota");

        Path p04 ("kocham.ala.ma.kota");
        p04.cutAllSegments ("asie");
        BOOST_CHECK (p04 == "kocham.ala.ma.kota");

        Path p05 ("asie");
        p05.cutAllSegments ("asie");
        BOOST_CHECK (p05 == "");

/*--------------------------------------------------------------------------*/

        Path p06 ("kocham.asie.ala.ma.kota");

        p06.cutAllSegments ("sjhfdskldjf");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

        p06.cutAllSegments ("koch");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

        p06.cutAllSegments ("am.as");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

        p06.cutAllSegments ("ocha");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

        p06.cutAllSegments ("");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

        p06.cutAllSegments (".");
        BOOST_CHECK (p06 == "kocham.asie.ala.ma.kota");

/*--------------------------------------------------------------------------*/

        Path p07 ("");

        p07.cutAllSegments ("koch");
        BOOST_CHECK (p07 == "");

        p07.cutAllSegments ("");
        BOOST_CHECK (p07 == "");

        p07.cutAllSegments (".");
        BOOST_CHECK (p07 == "");

        p07.cutAllSegments ("ko");
        BOOST_CHECK (p07 == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutFirstSegment, Path, TestTypes)
{
        Path path ("kocham.asie.asie.asie.ala.ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "asie.asie.asie.ala.ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "asie.asie.ala.ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "asie.ala.ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "ala.ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "ma.kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "kota");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "");

        path.cutFirstSegment ();
        BOOST_CHECK (path == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutLastSegment, Path, TestTypes)
{
        Path path ("kocham.asie.asie.asie.ala.ma.kota");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham.asie.asie.asie.ala.ma");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham.asie.asie.asie.ala");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham.asie.asie.asie");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham.asie.asie");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham.asie");

        path.cutLastSegment ();
        BOOST_CHECK (path == "kocham");

        path.cutLastSegment ();
        BOOST_CHECK (path == "");

        path.cutLastSegment ();
        BOOST_CHECK (path == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutAllButLastSegment, Path, TestTypes)
{
        Path path ("kocham.asie.asie.asie.ala.ma.kota");
        path.cutAllButLastSegment ();
        BOOST_CHECK (path == "kota");

        Path path2 ("");
        path2.cutAllButLastSegment ();
        BOOST_CHECK (path2 == "");

        Path path3 ("kocham");
        path3.cutAllButLastSegment ();
        BOOST_CHECK (path3 == "kocham");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testCutAllButFirstSegment, Path, TestTypes)
{
        Path path ("kocham.asie.asie.asie.ala.ma.kota");
        path.cutAllButFirstSegment ();
        BOOST_CHECK (path == "kocham");

        Path path2 ("");
        path2.cutAllButFirstSegment ();
        BOOST_CHECK (path2 == "");

        Path path3 ("kocham");
        path3.cutAllButFirstSegment ();
        BOOST_CHECK (path3 == "kocham");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testFindSegmentIndex, Path, TestTypes)
{
        Path p1 ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p1.findSegmentIndex ("kocham") == 0);
        BOOST_CHECK (p1.findSegmentIndex ("asie") == 1);
        BOOST_CHECK (p1.findSegmentIndex ("ala") == 2);
        BOOST_CHECK (p1.findSegmentIndex ("ma") == 3);
        BOOST_CHECK (p1.findSegmentIndex ("kota") == 4);
        BOOST_CHECK (p1.findSegmentIndex ("psa") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("zosie") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("asie.") == -1);
        BOOST_CHECK (p1.findSegmentIndex (".asie") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("koch") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("asi") == -1);
        BOOST_CHECK (p1.findSegmentIndex ("kot") == -1);

        Path p2 ("kocham");
        BOOST_CHECK (p2.findSegmentIndex ("kocham") == 0);
        BOOST_CHECK (p2.findSegmentIndex ("kocha") == -1);
        BOOST_CHECK (p2.findSegmentIndex ("") == -1);
        BOOST_CHECK (p2.findSegmentIndex ("89754328975897345732hdfsjdf") == -1);

        Path p3 ("");
        BOOST_CHECK (p3.findSegmentIndex ("kupa") == -1);
        BOOST_CHECK (p3.findSegmentIndex ("sikushfdsjdfdgsjdggshdgsdgf") == -1);
        BOOST_CHECK (p3.findSegmentIndex ("") == -1);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testGetSegmentByNumber, Path, TestTypes)
{
        Path p1 ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p1.getSegment (0) == "kocham");
        BOOST_CHECK (p1.getSegment (1) == "asie");
        BOOST_CHECK (p1.getSegment (2) == "ala");
        BOOST_CHECK (p1.getSegment (3) == "ma");
        BOOST_CHECK (p1.getSegment (4) == "kota");
        BOOST_CHECK (p1.getSegment (5) == "");
        BOOST_CHECK (p1.getSegment (6) == "");
        BOOST_CHECK (p1.getSegment (893276) == "");
        BOOST_CHECK (p1.getSegment (-1) == "");
        BOOST_CHECK (p1.getSegment (-18934) == "");

        Path p2 ("kocham");
        BOOST_CHECK (p2.getSegment (0) == "kocham");
        BOOST_CHECK (p2.getSegment (1) == "");
        BOOST_CHECK (p2.getSegment (2) == "");
        BOOST_CHECK (p2.getSegment (3) == "");
        BOOST_CHECK (p2.getSegment (10) == "");
        BOOST_CHECK (p2.getSegment (-1) == "");

        Path p3 ("");
        BOOST_CHECK (p3.getSegment (0) == "");
        BOOST_CHECK (p3.getSegment (1) == "");
        BOOST_CHECK (p3.getSegment (2) == "");
        BOOST_CHECK (p3.getSegment (-1) == "");
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testSplitSegments, Path, TestTypes)
{
        Path p01 ("kocham.asie.ala.ma.kota");
        Core::StringList list = p01.splitSegments ();
        Core::StringList::const_iterator i = list.begin ();

        BOOST_CHECK (*i++ == "kocham");
        BOOST_CHECK (*i++ == "asie");
        BOOST_CHECK (*i++ == "ala");
        BOOST_CHECK (*i++ == "ma");
        BOOST_CHECK (*i++ == "kota");

        Path p02 ("kocham");
        BOOST_CHECK (p02.splitSegments ().front () == "kocham");

        Path p03 ("");
        BOOST_CHECK (p03.splitSegments ().size () == 0);
}

/****************************************************************************/

BOOST_AUTO_TEST_CASE_TEMPLATE (testContainsSegment, Path, TestTypes)
{
        Path p1 ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p1.containsSegment ("kocham") == true);
        BOOST_CHECK (p1.containsSegment ("asie") == true);
        BOOST_CHECK (p1.containsSegment ("ala") == true);
        BOOST_CHECK (p1.containsSegment ("ma") == true);
        BOOST_CHECK (p1.containsSegment ("kota") == true);
        BOOST_CHECK (p1.containsSegment ("psa") == false);
        BOOST_CHECK (p1.containsSegment ("zosie") == false);
        BOOST_CHECK (p1.containsSegment ("asie.") == false);
        BOOST_CHECK (p1.containsSegment (".asie") == false);
        BOOST_CHECK (p1.containsSegment ("") == false);
        BOOST_CHECK (p1.containsSegment ("koch") == false);
        BOOST_CHECK (p1.containsSegment ("asi") == false);
        BOOST_CHECK (p1.containsSegment ("kot") == false);


        Path p2 ("kocham");
        BOOST_CHECK (p2.containsSegment ("kocham") == true);
        BOOST_CHECK (p2.containsSegment ("kocha") == false);
        BOOST_CHECK (p2.containsSegment ("") == false);
        BOOST_CHECK (p2.containsSegment ("89754328975897345732hdfsjdf") == false);

        Path p3 ("");
        BOOST_CHECK (p3.containsSegment ("kupa") == false);
        BOOST_CHECK (p3.containsSegment ("sikushfdsjdfdgsjdggshdgsdgf") == false);
        BOOST_CHECK (p3.containsSegment ("") == false);
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testGetLastSegment, Path, TestTypes)
{
        Path p ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p.getLastSegment () == "kota");
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testGetFirstSegment, Path, TestTypes)
{
        Path p ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p.getFirstSegment () == "kocham");
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testGetAllButLastSegment, Path, TestTypes)
{
        Path p ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p.getAllButLastSegment () == "kocham.asie.ala.ma");
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testGetAllButFirstSegment, Path, TestTypes)
{
        Path p ("kocham.asie.ala.ma.kota");
        BOOST_CHECK (p.getAllButFirstSegment () == "asie.ala.ma.kota");
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testWithSegmentsFront, Path, TestTypes)
{
        Path p ("/ala/ma/kota/", '/');

        BOOST_CHECK (p.getLastSegment () == "kota");
        BOOST_CHECK (p.getFirstSegment () == "ala");
}

BOOST_AUTO_TEST_CASE_TEMPLATE (testRelativeAbsolute, Path, TestTypes)
{
        {
                Path p ("/ala/ma/kota/", '/');
                BOOST_CHECK (p.isAbsolute());
        }

        {
                Path p ("/kota", '/');
                BOOST_CHECK (p.isAbsolute());
        }

        {
                Path p ("/", '/');
                BOOST_CHECK (p.isAbsolute());
        }

        {
                Path p ("ala/ma/kota/", '/');
                BOOST_CHECK (p.isRelative());
        }

        {
                Path p ("ala", '/');
                BOOST_CHECK (p.isRelative());
        }
}

BOOST_AUTO_TEST_SUITE_END ();
