//===-- DCPU16MCTargetDesc.cpp - DCPU16 Target Descriptions ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides DCPU16 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "DCPU16MCTargetDesc.h"
#include "DCPU16MCAsmInfo.h"
#include "InstPrinter/DCPU16InstPrinter.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "DCPU16GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "DCPU16GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "DCPU16GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createDCPU16MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitDCPU16MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createDCPU16MCRegisterInfo(StringRef TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitDCPU16MCRegisterInfo(X, DCPU16::A);
  return X;
}

static MCSubtargetInfo *createDCPU16MCSubtargetInfo(StringRef TT, StringRef CPU,
                                                    StringRef FS) {
  MCSubtargetInfo *X = new MCSubtargetInfo();
  InitDCPU16MCSubtargetInfo(X, TT, CPU, FS);
  return X;
}

static MCCodeGenInfo *createDCPU16MCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                                CodeModel::Model CM,
                                                CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  X->InitMCCodeGenInfo(RM, CM, OL);
  return X;
}

static MCInstPrinter *createDCPU16MCInstPrinter(const Target &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI,
                                                const MCSubtargetInfo &STI) {
  if (SyntaxVariant == 0)
    return new DCPU16InstPrinter(MAI, MII, MRI);
  return 0;
}

static MCStreamer *createDCPU16MCStreamer(const Target &T, StringRef TT,
                                    MCContext &Ctx, MCAsmBackend &MAB,
                                    raw_ostream &_OS,
                                    MCCodeEmitter *_Emitter,
                                    bool RelaxAll,
                                    bool NoExecStack) {
  Triple TheTriple(TT);

  class DCPU16MCStreamer : public MCObjectStreamer {
  public:
    DCPU16MCStreamer(MCContext &Context, MCAsmBackend &MAB,
                     raw_ostream &OS, MCCodeEmitter *Emitter)
      : MCObjectStreamer(Context, MAB, OS, Emitter) {}

    // MCStreamer
	  virtual void InitSections() {}
	  virtual void EmitAssemblerFlag(MCAssemblerFlag) {}
	  virtual void EmitThumbFunc(MCSymbol*) {}
	  virtual void EmitAssignment(MCSymbol*, const MCExpr*) {}
	  virtual void EmitSymbolAttribute(MCSymbol*, MCSymbolAttr) {}
	  virtual void EmitSymbolDesc(MCSymbol*, unsigned int) {}
	  virtual void BeginCOFFSymbolDef(const MCSymbol*) {}
	  virtual void EmitCOFFSymbolStorageClass(int) {}
	  virtual void EmitCOFFSymbolType(int) {}
	  virtual void EndCOFFSymbolDef() {}
	  virtual void EmitELFSize(MCSymbol*, const MCExpr*) {}
	  virtual void EmitCommonSymbol(MCSymbol*, uint64_t, unsigned int) {}
	  virtual void EmitLocalCommonSymbol(MCSymbol*, uint64_t, unsigned int) {}
	  virtual void EmitZerofill(const MCSection*, MCSymbol*, uint64_t, unsigned int) {}
	  virtual void EmitTBSSSymbol(const MCSection*, MCSymbol*, uint64_t, unsigned int) {}
	  virtual void EmitBytes(StringRef, unsigned int) {}
	  virtual void EmitValueToAlignment(unsigned int, int64_t, unsigned int, unsigned int) {}
	  virtual void EmitCodeAlignment(unsigned int, unsigned int) {}
	  virtual void EmitFileDirective(StringRef) {}

    // MCObjectStreamer
    virtual void EmitInstToData(const MCInst&) {}
  };

  return new DCPU16MCStreamer(Ctx, MAB, _OS, _Emitter);
}

extern "C" void LLVMInitializeDCPU16TargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<DCPU16MCAsmInfo> X(TheDCPU16Target);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheDCPU16Target,
                                        createDCPU16MCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheDCPU16Target, createDCPU16MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheDCPU16Target,
                                    createDCPU16MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheDCPU16Target,
                                          createDCPU16MCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheDCPU16Target,
                                        createDCPU16MCInstPrinter);

  // Register the object streamer.
  TargetRegistry::RegisterMCObjectStreamer(TheDCPU16Target, createDCPU16MCStreamer);
}

