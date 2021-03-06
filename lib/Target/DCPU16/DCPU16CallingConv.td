//==- DCPU16CallingConv.td - Calling Conventions for DCPU16 -*- tablegen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for DCPU16 architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// DCPU16 Return Value Calling Convention
//
// JS goal: Return a 32-bit or double value directly via |return|; for
//          larger values, use direct value as low 32 bits, registers for
//          the rest.
//===----------------------------------------------------------------------===//
def RetCC_DCPU16 : CallingConv<[
  // Promote i8 return values to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // i16 are returned in registers A, B, C
  CCIfType<[i16], CCAssignToReg<[A, B, C]>>
]>;

//===----------------------------------------------------------------------===//
// DCPU16 Argument Calling Conventions
//
// JS goal: Pass 32-bit or double values as normal |(x,y,z)| JS arguments;
//          for varargs, pass a single argument which is a pointer to the
//          varargs in memory.
//===----------------------------------------------------------------------===//
def CC_DCPU16 : CallingConv<[
  // Promote i8 arguments to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // The first 3 integer arguments of non-varargs functions are passed in
  // integer registers.
  CCIfNotVarArg<CCIfType<[i16], CCAssignToReg<[A, B, C]>>>,

  // Integer values get stored in stack slots that are 1 (16 bit) byte in
  // size and 1-byte aligned.
  CCIfType<[i16], CCAssignToStack<1, 1>>
]>;

def CSR_DCPU16 : CalleeSavedRegs<(add X, Y, Z, I, J)>;
