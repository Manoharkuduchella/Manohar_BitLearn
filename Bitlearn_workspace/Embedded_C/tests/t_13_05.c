// 2)An ISR (Interrupt Service Routine) is a specialized function executed by a microcontroller when a specific hardware or software event occurs, 
// interrupting the main program flow.

// Step 1: The Event & Request: A peripheral (e.g., a timer or GPIO) flags an event and sends an Interrupt Request (IRQ) to the NVIC (Nested Vector Interrupt Controller).
// Step 2: Context Saving (Pushing to Stack): The CPU temporarily pauses the main program. It saves the current execution state (registers and Program Counter) onto the stack to remember exactly where it left off.
// Step 3: Branch to the ISR: The CPU looks up the function address in the Interrupt Vector Table (IVT) and jumps to the specific ISR function (e.g., USART1_IRQHandler).
// Step 4: Execution: The ISR code runs. Crucially, in STM32 development, the ISR code must explicitly clear the peripheral’s interrupt flag before finishing, otherwise, the interrupt will re-trigger immediately upon exit.
// Step 5: Context Restoring & Return: The CPU pops the saved state from the stack and seamlessly resumes the main program or task where it was suspended