
#include "llvm/Support/raw_ostream.h"
#include "llvm/MC/MCExpr.h"

static void printMemoryAccess(int Addr, llvm::raw_ostream &O) {
  O << "HEAP32[" << Addr << "]";
}

static void printStackAccess(int Offset, llvm::raw_ostream &O) {
  O << "HEAP32[STACKTOP+" << Offset << "]";
}

static void printStackAccess(const llvm::MCExpr *Expr, llvm::raw_ostream &O) {
  O << "HEAP32[STACKTOP+";
  O << *Expr;
  O << "]";
}

