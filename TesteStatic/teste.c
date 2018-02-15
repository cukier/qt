#include "teste.h"

static volatile int nr = 12;

extern int getNr() {
    return nr;
}
