# Round Robin Task Scheduler for STM32F446RE

## Overview

This project implements a cooperative/preemptive Round Robin Task Scheduler from scratch on the STM32F446RE microcontroller without using any RTOS.

The goal of this project was to understand how an operating system kernel works internally by building the core scheduling infrastructure directly on ARM Cortex-M4 hardware.

The project includes a custom startup file, linker script, build system, task management framework, context switching mechanism, and SysTick-based scheduling.

---

## Features

* Round Robin task scheduling
* Multiple user tasks running concurrently
* SysTick-based periodic scheduling
* Task state management

  * READY
  * RUNNING
  * BLOCKED
* Software task delay mechanism
* Context switching using Process Stack Pointer (PSP)
* ARM Cortex-M4 exception-based scheduling
* Idle task implementation
* Custom startup code
* Custom linker script
* Custom Makefile-based build system
* Cross-compilation using GNU Arm Embedded Toolchain

---

## Hardware

* STM32F446RE Nucleo Board
* ARM Cortex-M4 Core

---

## Software Tools

* GNU Arm Embedded Toolchain
* GNU Make
* OpenOCD
* GDB
* STM32CubeProgrammer
* Git Bash
* VS Code

---

## Project Structure

```text
.
├── main.c
├── scheduler.c
├── scheduler.h
├── stm32_startup.c
├── stm32_ls.ld
├── Makefile
├── led.c
├── led.h
└── README.md
```

---

## Scheduler Architecture

The scheduler maintains a Task Control Block (TCB) for each task.

Each task is assigned:

* Dedicated stack space
* Current PSP value
* Task state
* Delay information

The scheduler rotates through all READY tasks in a Round Robin fashion.

```text
Task1
  ↓
Task2
  ↓
Task3
  ↓
Task4
  ↓
Idle Task
  ↓
Task1
```

---

## Context Switching

Context switching is performed inside the SysTick exception handler.

### Save Context

```text
PSP
 ├─ R4
 ├─ R5
 ├─ R6
 ├─ R7
 ├─ R8
 ├─ R9
 ├─ R10
 └─ R11
```

The scheduler stores the current task's PSP value before selecting the next task.

### Restore Context

After the next task is selected:

* PSP is restored
* Registers R4-R11 are recovered
* Execution resumes from the new task

---

## Memory Layout

The project uses a custom linker script.

### Flash

```text
0x08000000
│
├── Vector Table
├── .text
├── .rodata
└── Initial .data image
```

### SRAM

```text
0x20000000
│
├── .data
├── .bss
├── Task Stacks
└── Main Stack
```

---

## Boot Sequence

1. MCU Reset
2. Vector table loads MSP
3. Reset_Handler executes
4. .data copied from Flash to SRAM
5. .bss section zero initialized
6. Scheduler initialization
7. Tasks created
8. SysTick started
9. Round Robin scheduling begins

---

## Build

```bash
make
```

Output:

```text
final.elf
final.bin
```

---

## Flash

Using OpenOCD:

```bash
openocd -f board/st_nucleo_f4.cfg
```

Using GDB:

```bash
target remote localhost:3333
monitor reset halt
load
continue
```

---

## Future Improvements

* Priority-based scheduling
* Dynamic task creation
* Semaphore support
* Mutex implementation
* Event flags
* Message queues
* Tickless scheduling
* Memory management subsystem

---

