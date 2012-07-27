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
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/ADT/OwningPtr.h"

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

static MCStreamer *createDCPU16Streamer(MCContext &Ctx,
                                        formatted_raw_ostream &OS,
                                        bool isVerboseAsm,
                                        bool useLoc,
                                        bool useCFI,
                                        bool useDwarfDirectory,
                                        MCInstPrinter *InstPrint,
                                        MCCodeEmitter *CE,
                                        MCAsmBackend *TAB,
                                        bool ShowInst) {
  class DCPU16MCStreamer : public MCStreamer {
  protected:
    formatted_raw_ostream &OS;
    const MCAsmInfo &MAI;

  private:
    OwningPtr<MCInstPrinter> InstPrinter;

  public:
    DCPU16MCStreamer(MCContext &Context, formatted_raw_ostream &OS_,
                     MCInstPrinter *InstPrint)
      : MCStreamer(Context), OS(OS_), MAI(Context.getAsmInfo()),
        InstPrinter(InstPrint) {}

    // MCStreamer implementations
	  virtual void InitSections() {}
	  virtual void EmitAssemblerFlag(MCAssemblerFlag) {
      OS << "EmitAssemblerFlag\n";
    }
	  virtual void EmitThumbFunc(MCSymbol*) {
      OS << "EmitThumbFunc\n";
    }
	  virtual void EmitAssignment(MCSymbol*, const MCExpr*) {
      OS << "EmitAssignment\n";
    }
	  virtual void EmitSymbolAttribute(MCSymbol*, MCSymbolAttr) {} // don't think we need this
	  virtual void EmitSymbolDesc(MCSymbol*, unsigned int) {
      OS << "EmitSymbolDesc\n";
    }
	  virtual void BeginCOFFSymbolDef(const MCSymbol*) {
      OS << "BeginCOFFSymbolDef\n";
    }
	  virtual void EmitCOFFSymbolStorageClass(int) {
      OS << "EmitCOFFSymbolStorageClass\n";
    }
	  virtual void EmitCOFFSymbolType(int) {
      OS << "EmitCOFFSymbolType\n";
    }
	  virtual void EndCOFFSymbolDef() {
      OS << "EndCOFFSymbolDef\n";
    }
	  virtual void EmitELFSize(MCSymbol*, const MCExpr*) {
      OS << "EmitELFSize\n";
    }
	  virtual void EmitCommonSymbol(MCSymbol*, uint64_t, unsigned int) {
      OS << "EmitCommonSymbol\n";
    }
	  virtual void EmitLocalCommonSymbol(MCSymbol*, uint64_t, unsigned int) {
      OS << "EmitLocalCommonSymbol\n";
    }
	  virtual void EmitZerofill(const MCSection*, MCSymbol*, uint64_t, unsigned int) {
      OS << "EmitZerofill\n";
    }
	  virtual void EmitTBSSSymbol(const MCSection*, MCSymbol*, uint64_t, unsigned int) {
      OS << "EmitTBSSSymbol\n";
    }
	  virtual void EmitBytes(StringRef Str, unsigned int) {
      OS << "[";
      unsigned int Size = Str.size();
      for (unsigned int i = 0; i < Size; i++) {
        if (i > 0) OS << ",";
        OS << (int)Str[i];
      }
      OS << "]";
    }
	  virtual void EmitValueToAlignment(unsigned int, int64_t, unsigned int, unsigned int) {
      OS << "EmitValueToAlignment\n";
    }
	  virtual void EmitCodeAlignment(unsigned int, unsigned int) {} // we don't need this
	  virtual void EmitFileDirective(StringRef) {} // we don't need this
	  virtual void ChangeSection(const llvm::MCSection*) {} // we don't need this either
	  virtual void EmitWeakReference(llvm::MCSymbol*, const llvm::MCSymbol*) {
      OS << "EmitWeakReference\n";
    }
	  virtual void EmitValueImpl(const llvm::MCExpr*, unsigned int, unsigned int) {
      OS << "EmitValueImpl\n";
    }
	  virtual void EmitULEB128Value(const llvm::MCExpr*) {
      OS << "EmitULEB128Value\n";
    }
	  virtual void EmitSLEB128Value(const llvm::MCExpr*) {
      OS << "EmitSLEB128Value\n";
    }
	  virtual bool EmitValueToOffset(const llvm::MCExpr*, unsigned char) {
      OS << "EmitValueToOffset\n";
      return true;
    }
	  virtual void EmitDwarfAdvanceLineAddr(int64_t, const llvm::MCSymbol*, const llvm::MCSymbol*, unsigned int) {
      OS << "EmitDwarfAdvanceLineAddr\n";
    }
	  virtual void EmitInstruction(const llvm::MCInst& Inst) {
      // If we have an AsmPrinter, use that to print, otherwise print the MCInst.
      if (InstPrinter)
        InstPrinter->printInst(&Inst, OS, "");
      else
        Inst.print(OS, &MAI);
      EmitEOL();
    }
	  virtual void FinishImpl() {} // not needed
    virtual void EmitLabel(MCSymbol *Symbol) {
      assert(Symbol->isUndefined() && "Cannot define a symbol twice!");
      MCStreamer::EmitLabel(Symbol);

      OS << "var " << *Symbol << " = ";
    }

    inline void EmitEOL() {
      OS << '\n';
    }

    void EmitRawText(StringRef String) {
      if (!String.empty() && String.back() == '\n')
        String = String.substr(0, String.size()-1);
      OS << String;
      EmitEOL();
    }
  };

  return new DCPU16MCStreamer(Ctx, OS, InstPrint);
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
  TargetRegistry::RegisterAsmStreamer(TheDCPU16Target, createDCPU16Streamer);
}

