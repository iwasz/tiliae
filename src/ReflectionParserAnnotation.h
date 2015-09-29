#ifndef REFLECTIONPARSERANNOTATION_H
#define REFLECTIONPARSERANNOTATION_H

#define __tiliae_reflect__ __attribute__((annotate("__tiliae_reflect__")))
#define __tiliae_reflect_token__(className) __attribute__((annotate("__tiliae_reflect_token__"))) __attribute__((annotate(#className)))
#define __tiliae_no_reflect__ __attribute__((annotate("__tiliae_no_reflect__")))

#endif // REFLECTIONPARSERANNOTATION_H

