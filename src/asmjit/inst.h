/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Copyright (c) 2008-2017, Petr Kobalicek

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#ifndef __PLUMED_asmjit_inst_h
#define __PLUMED_asmjit_inst_h
#ifdef __PLUMED_HAS_ASMJIT
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
// [AsmJit]
// Complete x86/x64 JIT and Remote Assembler for C++.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Guard]
#ifndef _ASMJIT_BASE_INST_H
#define _ASMJIT_BASE_INST_H

// [Dependencies]
#include "./cpuinfo.h"
#include "./operand.h"

// [Api-Begin]
#include "./asmjit_apibegin.h"

namespace PLMD {
namespace asmjit {

//! \addtogroup asmjit_base
//! \{

// ============================================================================
// [asmjit::Inst]
// ============================================================================

//! Definitions and utilities related to instructions used by all architectures.
struct Inst {
  ASMJIT_ENUM(Id) {
    kIdNone = 0                          //!< Invalid or uninitialized instruction id.
  };

  //! Describes an instruction's jump type, if any.
  ASMJIT_ENUM(JumpType) {
    kJumpTypeNone        = 0,            //!< Instruction doesn't jump (regular instruction).
    kJumpTypeDirect      = 1,            //!< Instruction is a unconditional (direct) jump.
    kJumpTypeConditional = 2,            //!< Instruction is a conditional jump.
    kJumpTypeCall        = 3,            //!< Instruction is a function call.
    kJumpTypeReturn      = 4             //!< Instruction is a function return.
  };

  // --------------------------------------------------------------------------
  // [Detail]
  // --------------------------------------------------------------------------

  //! Instruction id, options, and extraReg packed in a single structure. This
  //! structure exists to simplify analysis and validation API that requires a
  //! lot of information about the instruction to be processed.
  class Detail {
  public:
    ASMJIT_INLINE Detail() noexcept
      : instId(0),
        options(0),
        extraReg() {}

    explicit ASMJIT_INLINE Detail(uint32_t instId, uint32_t options = 0) noexcept
      : instId(instId),
        options(options),
        extraReg() {}

    ASMJIT_INLINE Detail(uint32_t instId, uint32_t options, const RegOnly& reg) noexcept
      : instId(instId),
        options(options),
        extraReg(reg) {}

    ASMJIT_INLINE Detail(uint32_t instId, uint32_t options, const Reg& reg) noexcept
      : instId(instId),
        options(options) { extraReg.init(reg); }

    // ------------------------------------------------------------------------
    // [Accessors]
    // ------------------------------------------------------------------------

    ASMJIT_INLINE bool hasExtraReg() const noexcept { return extraReg.isValid(); }

    // ------------------------------------------------------------------------
    // [Members]
    // ------------------------------------------------------------------------

    uint32_t instId;
    uint32_t options;
    RegOnly extraReg;
  };

  // --------------------------------------------------------------------------
  // [API]
  // --------------------------------------------------------------------------

#if !defined(ASMJIT_DISABLE_VALIDATION)
  //! Validate the given instruction.
  ASMJIT_API static Error validate(uint32_t archType, const Detail& detail, const Operand_* operands, uint32_t count) noexcept;
#endif // !ASMJIT_DISABLE_VALIDATION

#if !defined(ASMJIT_DISABLE_EXTENSIONS)
  //! Check CPU features required to execute the given instruction.
  ASMJIT_API static Error checkFeatures(uint32_t archType, const Detail& detail, const Operand_* operands, uint32_t count, CpuFeatures& out) noexcept;
#endif // !defined(ASMJIT_DISABLE_EXTENSIONS)
};

//! \}

} // asmjit namespace
} // namespace PLMD

// [Api-End]
#include "./asmjit_apiend.h"

// [Guard]
#endif // _ASMJIT_BASE_INST_H
#pragma GCC diagnostic pop
#endif // __PLUMED_HAS_ASMJIT
#endif
