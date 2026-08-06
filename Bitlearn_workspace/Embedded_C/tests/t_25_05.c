// Structure Padding, RAM Wastage & Packed Structs in Embedded Systems
// 1. How Padding Increases RAM Wastage
// The C compiler inserts padding bytes between struct members to satisfy alignment requirements (each member must sit at an address that's a multiple of its size).
// c// Naive struct — looks like 7 bytes, actually 12 bytes
// struct Sensor {
//     uint8_t  id;        // 1 byte  @ offset 0
//                         // 3 bytes PADDING (to align next field to 4-byte boundary)
//     uint32_t value;     // 4 bytes @ offset 4
//     uint8_t  status;    // 1 byte  @ offset 8
//                         // 3 bytes PADDING (to align struct size to 4)
// };                      // Total: 12 bytes  (wasted 6 bytes = 50% waste!)
// In systems with arrays of structs, this multiplies fast:
// cstruct Sensor sensors[100];
// // Expected: 700 bytes
// // Actual:  1200 bytes  ← 500 bytes wasted RAM
// On a microcontroller with 32KB SRAM, this is significant.

// 2. Risks of __attribute__((packed)) on ARM Cortex-M
// packed removes all padding, but ARM Cortex-M has strict alignment rules:
// ⚠️ Unaligned Access Fault (HardFault)
// cstruct __attribute__((packed)) Packet {
//     uint8_t  flag;      // offset 0
//     uint32_t value;     // offset 1  ← NOT 4-byte aligned!
//     uint16_t checksum;  // offset 5  ← NOT 2-byte aligned!
// };

// struct Packet p;
// uint32_t x = p.value;  // CRASH on Cortex-M0/M0+!
//                         // Bus fault / HardFault on M3/M4 if CCR.UNALIGN_TRP set
// CoreDefault Unaligned AccessRiskCortex-M0 / M0+❌ Always faultsImmediate HardFaultCortex-M3 / M4⚠️ Allowed but slowFault if CCR.UNALIGN_TRP=1Cortex-M7⚠️ Allowed but slowSame trap risk
// ⚠️ Pointer Dereferencing is Dangerous
// cstruct __attribute__((packed)) Foo { uint8_t a; uint32_t b; };
// struct Foo f;

// uint32_t *ptr = &f.b;   // ptr = 0x20000001 (unaligned!)
// *ptr = 42;              // ← UNDEFINED BEHAVIOUR / HardFault
//                         // Compiler may not protect you here
// The compiler generates safe multi-byte loads for direct member access, but if you take the address of an unaligned member and cast it, all bets are off.

// 3. Why Packed Structures Reduce Performance
// Even when the hardware allows unaligned access (M3/M4/M7), it's never free:
// Normal aligned read:      1 bus cycle   → LDR r0, [r1]
// Unaligned word read:      2 bus cycles  → two LDRBs + shifts + ORR
//                                           (compiler generates ~4-6 instructions)
// The compiler replaces a single LDR with something like:
// asm; Reading an unaligned uint32_t from packed struct:
// LDRB  r0, [r1, #0]
// LDRB  r2, [r1, #1]
// ORR   r0, r0, r2, LSL #8
// LDRB  r2, [r1, #2]
// ORR   r0, r0, r2, LSL #16
// LDRB  r2, [r1, #3]
// ORR   r0, r0, r2, LSL #24
// ; 7 instructions instead of 1!
// This means:

// ~4–7× more instructions per unaligned field access
// Increased code size (Flash usage goes up)
// Cache pressure on M7 (more instruction cache lines consumed)
// No pipelining benefit — dependent instructions stall


// ✅ The Right Fix: Reorder Members
// Instead of packed, reorder fields largest → smallest to eliminate padding naturally:
// c// ❌ Wastes 6 bytes
// struct Bad  { uint8_t a; uint32_t b; uint8_t c; };  // 12 bytes

// // ✅ Zero padding, zero performance penalty
// struct Good { uint32_t b; uint8_t a; uint8_t c; };  // 6 bytes


The answer is unambiguous: bitmask wins for hardware register access. Here's the complete reasoning.

What each technique is
Bitmask is manual bit manipulation using &, |, ~, and << on an integer variable holding the raw register value. You write the bit positions explicitly and the compiler faithfully translates them to exact instructions.
Bitfield is a C struct where you declare members with a : N width specifier. The compiler handles the shifting and masking for you, which sounds helpful — but comes with serious hidden costs when accessing hardware.

Why bitmask is superior for register access
1. Exact assembly output — you control what the CPU does
With bitmask you know precisely what instructions will be generated:
c// Set bit 0 of GPIOA->ODR
GPIOA->ODR |= (1U << 0);
// Compiler → ORR r0, r0, #1 (or LDREX/STREX for atomic)
With bitfield, the generated assembly is compiler- and ABI-dependent. GCC and Clang can produce different instruction sequences for the same bitfield operation. In safety-critical embedded code, this unpredictability is unacceptable.
2. Bit ordering is implementation-defined in C
The C standard (C99 §6.7.2.1) explicitly states that the allocation of bitfields within a storage unit is implementation-defined — meaning the compiler decides whether bit 0 of your struct maps to bit 0 or bit 7 of the physical register. On little-endian ARM this usually works "intuitively," but it's never guaranteed. One compiler version bump or a -mbig-endian flag and your register map is silently wrong.
With bitmask, (1U << 5) means bit 5, unconditionally, on every compiler and every architecture.
3. No padding surprises
cstruct BadReg {
    uint8_t EN    : 1;
    // compiler MAY insert padding here to align next field
    uint32_t SPEED : 3;  // different type triggers padding!
};
If your bitfield members span different underlying types (uint8_t and uint32_t), most compilers insert padding between them, silently breaking the bit layout. __attribute__((packed)) avoids this but brings the ARM unaligned-access hazards we covered earlier.
4. Read-modify-write is explicit and auditable
Both approaches perform a load-modify-store (RMW) for field writes — neither is automatically atomic. But with bitmask, the RMW sequence is visible in your source and you know exactly where to add a critical section or use bitband addressing. With bitfield, the RMW is hidden inside compiler magic, making it easy to forget about interrupt-safety.
c// BITMASK — RMW is visible, you know to protect it
__disable_irq();
REG = (REG & ~0x30) | (mode << 4);
__enable_irq();

// BITFIELD — RMW is hidden, easy to forget the guard
reg_ptr->MODE = mode;  // looks atomic, is NOT
5. No Cortex-M0 portability issue
Cortex-M4/M7 have the BFI/BFC (Bit Field Insert/Clear) instructions. If the compiler uses these for bitfield access, the code silently breaks on Cortex-M0/M0+ which lack those instructions. Bitmask-based code with AND/ORR/LSL runs identically across all Cortex-M variants.