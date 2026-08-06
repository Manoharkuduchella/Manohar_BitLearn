Bit-banding is a hardware feature found in some microprocessors (like the Arm Cortex-M3 and Cortex-M4) that maps a complete 32-bit word in an "alias" memory region to a single, 
specific bit in a "bit-band" memory region. 
It is faster and safer than a software Read-Modify-Write (RMW) sequence because it offloads the bit-manipulation process entirely to the hardware bus logic, 
allowing a single STR (store) assembly instruction to change a bit instead of a multi-instruction software sequence



//AXI vs AHB
The main advantage of AXI over AHB for large data transfers is its multi-channel, 
full-duplex architecture combined with support for multiple outstanding transactions. 
This completely bypasses the data pipeline limitations and blocking delays inherent in traditional shared buses.

advantages:
Five Independent Channels: Unlike AHB's shared data bus, AXI features five separate channels (Write Address, Write Data, Write Response, Read Address, and Read Data). 
This allows the bus to perform reads and writes simultaneously (full-duplex).

 AXI masters do not have to wait for a current data transfer to finish before initiating a new one. 
 For bulk data movement, this pipelining keeps the data bus continuously saturated.

  AXI uses transaction IDs,
 allowing data from faster memory segments to arrive out-of-order and be reassembled properly at the destination.

 //advantages of Bus matrix
 A bus matrix eliminates single-bus bottlenecks by creating dynamic, 
 parallel pathways between multiple bus masters (like CPUs and DMAs) and memory or peripherals.
  It maximizes system performance through the following mechanisms:

  1)A bus matrix eliminates single-bus bottlenecks by creating dynamic, parallel pathways between multiple bus masters (like CPUs and DMAs) and memory or peripherals. It maximizes system performance through the following mechanisms
  2)When multiple masters (e.g., CPU, DSP, USB controller) simultaneously request access to the exact same memory bank or slave peripheral, the matrix avoids data collisions via integrated arbiters:
        a)Round-Robin
        b)Fixed Priority
  3)The matrix acts as a high-speed multiplexer, instantly connecting a requesting master to an available target. This removes "access blocking" and ensures that independent transactions happen concurrently without having to wait for the system bus to become free



  //Bus arbitration btw CPU and DMA
  Bus arbitration uses a dedicated hardware component called an arbiter to determine who gets control.
   When both request the bus simultaneously,
   the arbiter grants access based on a pre-programmed prioritization policy
    a) Fixed Priority
    b) Rotating/Polling Priority
    arbiter uses Bus Request (BR), Bus Grant (BG), Bus Busy (BB)to resolve the conflict.


//Vector table
A vector table is a data structure in memory that maps exceptions and hardware interrupts to their corresponding handler functions. It acts as a directory for the processor, directing it to the exact memory location where specific code resides.
vector table is a sequential array of 32-bit memory addresses.
contains: Initial Stack pointer and Exception/Interrupt vectors

after reset:
1) Setting the Stack Pointer (SP): The processor reads the very first address in the vector table and loads it into the stack pointer. This is mandatory because the processor requires working RAM space to temporarily store variables, return addresses, and nested function calls before it can execute any software.
2) Finding the Reset Handler: The processor reads the second entry in the vector table. This entry points to the Reset Vector, which is the starting address of the startup code. By reading this, the processor knows exactly where to find the first line of code required to initialize the system and launch the operating system or application


//what Reset handler do?
Upon a reset, the microcontroller's hardware loads the stack pointer and jumps to the Reset Handler. 
The Reset Handler then performs four crucial steps: initializing hardware, copying initialized variables to RAM, zeroing uninitialized variables, 
and setting up the C runtime environment,
before finally calling the main function

//what does startupcode do?
Startup code is the essential initialization software that executes immediately after a processor resets, 
bridging the gap between hardware power-up and the main() function. 
It establishes the execution environment, configures system clocks, sets the stack pointer, and ensures program memory is correctly populated.

//count set bits without loops
// Function to count set bits without any loops
uint32_t countSetBits(uint32_t n) {
    // 1. Pack counts of 2 bits into 2-bit fields
    n = n - ((n >> 1) & 0x55555555);
    
    // 2. Pack counts of 4 bits into 4-bit fields
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    
    // 3. Pack counts of 8 bits into 8-bit fields
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    
    // 4. Multiply to sum up all 4 bytes into the top byte, then shift right
    return (n * 0x01010101) >> 24;
}



//find mid node of sll
// Function to find the middle node in a single traversal
struct Node* findMiddle(struct Node* head) {
    // Edge case: empty list or list with only one node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct Node* slow = head;
    struct Node* fast = head;

    // Traverse the list
    // fast moves twice as fast as slow
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // slow now points to the middle node
    return slow;
}