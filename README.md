# BTP Hardware Security

This repository is organized as a two-phase Bachelor of Technology project in hardware security and side-channel analysis.

The work is split semester-wise:

- `phase-1_last-sem/`: previous semester work on ChipWhisperer Nano and firmware-side attacks
- `phase-2_current-sem/`: current semester work on CW305, Ascon-128, HLS-based hardware generation, and the prepared next stage for FPGA-side evaluation

This structure is meant to keep the full BTP journey clear. Phase 1 shows the base work that built the required side-channel attack understanding. Phase 2 shows the move from software targets to hardware targets.

---

## Repository Overview

```text
BTP_Hardware_security/
├── README.md
├── phase-1_last-sem/
│   ├── README.md
│   └── report/
│       ├── Chipwhisperer_report_tutorial_rupesh.pdf
│       └── Presentation_chipwhisperer.pdf
└── phase-2_current-sem/
    ├── README.md
    ├── docs/
    │   ├── final-report/
    │   │   ├── BTP_final.pptx
    │   │   └── BTP_report_Rupesh.pdf
    │   └── instruction-guide/
    │       └── BTP_Instructions_rupesh.pdf
    ├── src/
    │   └── hls/
    │       ├── api.h
    │       ├── ascon_core.c
    │       ├── ascon_test.exe
    │       ├── main.c
    │       └── permutations.h
    └── scripts/
        ├── hls/
        │   └── run_exploration.tcl
        └── notebooks/
            └── Ascon_Hardware_Test.ipynb
```

---

## Phase 1 Overview

`phase-1_last-sem/` contains the first semester work. This phase focused on learning ChipWhisperer basics and performing side-channel analysis on a firmware target.

### Main focus
- Target board: ChipWhisperer Nano
- Target type: STM32F0 microcontroller
- Algorithm focus: AES
- Attack focus: SPA, DPA, and CPA
- Leakage model used: Hamming Weight

### What this phase contributed
- basic understanding of power trace capture
- practical understanding of leakage from firmware execution
- use of power traces to study data-dependent behavior
- CPA experience using AES S-box intermediate values and Pearson Correlation

This phase is important because it forms the direct technical base for the current semester work.

---

## Phase 2 Overview

`phase-2_current-sem/` contains the current semester work. This phase moves from firmware security to hardware security.

### Main focus
- Target board: ChipWhisperer CW305 Artix-7 FPGA
- Algorithm focus: Ascon-128
- Hardware generation flow: Vitis HLS 2024.2
- Core idea: convert clean C reference code into synthesizable hardware
- Current attack direction: CPA using Hamming Distance
- Main research direction: study leakage in HLS-generated hardware and later compare it with pure RTL

### What is already completed in this phase
- merged HLS-ready Ascon top-level core
- supporting HLS source files
- design-space exploration Tcl script
- CW305 hardware-test notebook
- final report PDF
- instruction guide PDF
- phase presentation file

### What is still future work
- physical CW305 execution and trace capture
- FPGA-side CPA on captured traces
- pure RTL implementation
- HLS versus RTL leakage comparison under the same conditions

---

## Detailed Structure

### `phase-1_last-sem/report/`
This folder stores the main outputs from the previous semester.

Current files:
- `Chipwhisperer_report_tutorial_rupesh.pdf`
- `Presentation_chipwhisperer.pdf`

Purpose:
- preserve the completed report from the Nano-based work
- preserve the presentation material used to explain the first semester progress

---

### `phase-2_current-sem/docs/`
This folder stores formal written outputs from the current semester.

#### `phase-2_current-sem/docs/final-report/`
Current files:
- `BTP_report_Rupesh.pdf`
- `BTP_final.pptx`

Purpose:
- store the final BTP report for the current semester
- store the presentation file related to the current phase

#### `phase-2_current-sem/docs/instruction-guide/`
Current files:
- `BTP_Instructions_rupesh.pdf`

Purpose:
- store the step-by-step project guide
- document the implementation and execution flow clearly for later reuse

---

### `phase-2_current-sem/src/hls/`
This folder stores the main HLS-side source code used in the current project.

Current files:
- `api.h`
- `ascon_core.c`
- `main.c`
- `permutations.h`
- `ascon_test.exe`

Purpose of important source files:

- `api.h`
  - defines key sizes and interface declarations
  - declares the unified `ascon_core(...)` top function

- `ascon_core.c`
  - contains the merged encrypt/decrypt hardware-oriented Ascon logic
  - includes the HLS interface pragmas
  - is the main source used for HLS synthesis

- `main.c`
  - acts as a testbench-style file
  - checks encrypt then decrypt behavior
  - helps validate functional correctness before hardware-level evaluation

- `permutations.h`
  - contains type definitions, state structure, byte-word conversion helpers, and permutation-related support code

Note:
- `ascon_test.exe` is a generated executable artifact, not source code. It is useful for local testing, but it is not part of the core source set.

---

### `phase-2_current-sem/scripts/`
This folder stores the automation and execution-side scripts.

#### `phase-2_current-sem/scripts/hls/`
Current files:
- `run_exploration.tcl`

Purpose:
- automates HLS design-space exploration
- runs multiple solutions such as baseline, unrolled, pipelined, and dataflow

#### `phase-2_current-sem/scripts/notebooks/`
Current files:
- `Ascon_Hardware_Test.ipynb`

Purpose:
- stores the prepared notebook for CW305 board communication
- contains the planned commands for FPGA programming, voltage setup, PLL setup, register write/read flow, and later hardware checking

---

## How the Two Phases Connect

This repo is intentionally split into two phases because the project evolved in a clear academic sequence:

1. learn side-channel concepts on a microcontroller target
2. apply CPA practically on firmware AES
3. move to FPGA hardware as the next research step
4. implement Ascon-128 in HLS-generated hardware
5. prepare for FPGA-side CPA and later HLS-vs-RTL comparison

So the structure is not only for storage. It also reflects the technical growth of the BTP.

---

## Current Status Summary

### Completed
- previous semester Nano-based report and presentation
- current semester report and instruction guide
- HLS-ready Ascon source files
- HLS automation script
- CW305 test notebook preparation

### Pending
- final physical board evaluation
- side-channel trace capture on CW305
- RTL implementation
- HLS vs RTL comparison

---

## Notes for Use

- Phase 1 should be read first if someone wants to understand the base side-channel workflow.
- Phase 2 should be read for the hardware transition, HLS structure, and the current implementation path.
- The source code in `phase-2_current-sem/src/hls/` is the main code set relevant to the current semester work.
- The scripts in `phase-2_current-sem/scripts/` support synthesis automation and hardware execution planning.

This structure is designed to be simple, academic, and easy to explain during project review.
