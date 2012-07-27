//===-- DCPU16MCAsmInfo.cpp - DCPU16 asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the DCPU16MCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "DCPU16MCAsmInfo.h"
#include "llvm/ADT/StringRef.h"
using namespace llvm;

void DCPU16MCAsmInfo::anchor() { }

DCPU16MCAsmInfo::DCPU16MCAsmInfo(const Target &T, StringRef TT) {
  LabelPrefix = "var "; // Should not really be used
  LabelSuffix = " = ";
  PointerSize = 4;

  GlobalPrefix = "_";
  PrivateGlobalPrefix = "_";
  WeakRefDirective ="\t.weak\t";
  PCSymbol=".";
  CommentString = "//";

  AlignmentIsInBytes = false;
  // TODO(krasin): support .align
  // https://github.com/krasin/llvm-dcpu16/issues/52
  AlignDirective = "\t; .align\t";
  AllowNameToStartWithDigit = false;
  AllowPeriodsInName = false;
  UsesELFSectionDirectiveForBSS = false;
  HasDotTypeDotSizeDirective = false;

  // Use .lcomm instead of .local .comm (required for binutils support)
  LCOMMDirectiveType = LCOMM::NoAlignment;

  AsciiDirective = "";
  AscizDirective = "";
  SeparatorString = "/* */";
  AlignDirective = "// align ";
  GlobalDirective = "// global ";

}
