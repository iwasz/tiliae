/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONNECTIONPOINTREFERENCE_H_
#define CONNECTIONPOINTREFERENCE_H_

#include "Vertex.h"
#include <vector>
//#include <boost/ptr_container/ptr_vector.hpp>
#include "core/Pointer.h"

namespace Machine {

class ConnectionPointReference : public Vertex {
public:
        virtual ~ConnectionPointReference () {}
};

typedef std::vector <Ptr <ConnectionPointReference> > ConnectionPointReferenceVector;
//typedef boost::ptr_vector <ConnectionPointReference> ConnectionPointReferenceVector2;

} /* namespace Machine */

#	endif /* CONNECTIONPOINTREFERENCE_H_ */
