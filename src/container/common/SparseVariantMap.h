/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SPARSEVARIANTMAP_H_
#define SPARSEVARIANTMAP_H_

//#include <hash_fun.h>
#include <google/sparse_hash_map>
#include "core/variant/Variant.h"
#include "core/StrUtil.h"

namespace Container {


// typedef google::sparse_hash_map <const char*, Core::Variant, std::hash<const char*>, Eqstr> SparseVariantMap;
typedef std::map<const char *, Core::Variant, StrLess> SparseVariantMap;

} // namsp

#endif /* SPARSEVARIANTMAP_H_ */
