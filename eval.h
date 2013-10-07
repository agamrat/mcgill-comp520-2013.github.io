#ifndef EVAL_H
#define EVAL_H

#include "tree.h"

typedef struct EXPresult {
  enum {string, number} kind;
  union {
    char *idE;
    int intconstE;
  } val;
} EXPresult;

EXPresult evalEXP(EXP *e);

#endif /* !EVAL_H */
