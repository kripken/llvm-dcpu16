
#include "llvm/Support/raw_ostream.h"

static void printStackAccess(int offset, llvm::raw_ostream &O) {
  O << "HEAP[STACKTOP+" << offset << "]";
}

