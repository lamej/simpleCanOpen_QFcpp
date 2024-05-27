//============================================================================
// QP/C++ Real-Time Embedded Framework (RTEF)
//
//                   Q u a n t u m  L e a P s
//                   ------------------------
//                   Modern Embedded Software
//
// Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
//
// This software is dual-licensed under the terms of the open source GNU
// General Public License version 3 (or any later version), or alternatively,
// under the terms of one of the closed source Quantum Leaps commercial
// licenses.
//
// The terms of the open source GNU General Public License version 3
// can be found at: <www.gnu.org/licenses/gpl-3.0>
//
// The terms of the closed source Quantum Leaps commercial licenses
// can be found at: <www.state-machine.com/licensing>
//
// Redistributions in source code must retain this top-level comment block.
// Plagiarizing this software to sidestep the license obligations is illegal.
//
// Contact information:
// <www.state-machine.com>
// <info@state-machine.com>
//============================================================================
//! @date Last updated on: 2023-09-07
//! @version Last updated for: @ref qpcpp_7_3_0
//!
//! @file
//! @brief QP/C++ port to Cortex-R, cooperative QV kernel, IAR-ARM

#ifndef QP_PORT_HPP_
#define QP_PORT_HPP_

#include <cstdint>  // Exact-width types. C++11 Standard
#include <intrinsics.h> // IAR intrinsic functions

#ifdef QP_CONFIG
#include "qp_config.hpp" // external QP configuration
#endif

// no-return function specifier (C++11 Standard)
#define Q_NORETURN  [[ noreturn ]] void

// QF configuration for QV -- data members of the QActive class...

// QV event-queue used for AOs
#define QACTIVE_EQUEUE_TYPE     QEQueue

// QF interrupt disable/enable, see NOTE2
#define QF_INT_DISABLE()        __disable_irq()
#define QF_INT_ENABLE()         __enable_irq()
#define QF_INT_ENABLE_ALL()     __enable_interrupt()

// Cortex-R provide the CLZ instruction for fast LOG2
#define QF_LOG2(n_) (static_cast<std::uint8_t>(32U - __CLZ(n_)))

// QF critical section entry/exit, see NOTE3
#define QF_CRIT_STAT            std::uint32_t cpsr_;
#define QF_CRIT_ENTRY() do { \
    cpsr_ = __get_CPSR(); \
    QF_INT_DISABLE();     \
} while (false)
#define QF_CRIT_EXIT()          __set_CPSR(cpsr_)
#define QF_CRIT_EXIT_NOP()      __ISB()

// macro to put the CPU to sleep inside QV_onIdle()
#define QV_CPU_SLEEP() do { \
    __WFI(); \
    QF_INT_ENABLE(); \
} while (false)

// include files -------------------------------------------------------------
#include "qequeue.hpp"   // QV kernel uses the native QP event queue
#include "qmpool.hpp"    // QV kernel uses the native QP memory pool
#include "qp.hpp"        // QP framework
#include "qv.hpp"        // QV kernel

//============================================================================
// NOTE2:
// The FIQ-type interrupts are NEVER disabled in this port, so the FIQ is
// a "kernel-unaware" interrupt. If the FIQ is ever used in the application,
// it must be an "__arm __fiq"-type function. For this to work, the FIQ
// stack needs to be initialized.
//
// NOTE3:
// This port implements the "save and restore" interrupt status policy,
// which again never disables the FIQ-type interrupts. This policy allows
// for nesting critical sections, which is necessary inside IRQ-type
// interrupts that run with interrupts (IRQ) disabled.
//

#endif // QP_PORT_HPP_

