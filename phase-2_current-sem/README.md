# Phase 2: Current Semester

This folder contains the current semester work of the BTP. The focus in this phase is the move from firmware-based side-channel analysis to hardware-oriented design and evaluation on the ChipWhisperer CW305 FPGA platform.

---

## Technical Focus

- Target board: ChipWhisperer CW305 Artix-7 FPGA
- Algorithm target: Ascon-128
- Implementation flow: Vitis HLS 2024.2
- Main side-channel direction: CPA with Hamming Distance
- Main research direction: compare HLS-generated hardware with pure RTL in future work

---

## Purpose of This Phase

This phase extends the previous semester work into hardware security. The key idea is:

- start from clean reference C code,
- convert it into synthesizable hardware using HLS,
- prepare the FPGA execution flow,
- and build the path toward FPGA-side side-channel analysis.

This is the major transition from attacking firmware instructions to studying leakage from actual hardware structure.

---

## Folder Structure

```text
phase-2_current-sem/
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

## `docs/`

This folder stores the formal output documents of the current semester.

### `docs/final-report/`
Current files:
- `BTP_report_Rupesh.pdf`
- `BTP_final.pptx`

Purpose:
- store the final current-semester BTP report
- store the presentation material for this phase

### `docs/instruction-guide/`
Current files:
- `BTP_Instructions_rupesh.pdf`

Purpose:
- store the step-by-step guide for the implementation flow
- preserve the project execution methodology in clean written form

---

## `src/hls/`

This folder stores the main HLS-side source files used in the project.

Current files:
- `api.h`
- `ascon_core.c`
- `main.c`
- `permutations.h`
- `ascon_test.exe`

### Source file roles

- `api.h`
  - size definitions and top-level interface declaration

- `ascon_core.c`
  - merged Ascon encrypt/decrypt logic
  - main hardware synthesis source

- `main.c`
  - functional testbench-style program
  - used to verify encrypt/decrypt flow

- `permutations.h`
  - state structure and helper functions
  - supports the permutation operations used by the core

Important note:
- `ascon_test.exe` is an executable artifact and not part of the core source design. The main source set is the four code files listed above.

---

## `scripts/`

This folder stores the execution and automation helpers.

### `scripts/hls/`
Current files:
- `run_exploration.tcl`

Purpose:
- automate design-space exploration in Vitis HLS
- create multiple HLS solutions such as baseline, unrolled, pipelined, and dataflow

### `scripts/notebooks/`
Current files:
- `Ascon_Hardware_Test.ipynb`

Purpose:
- keep the prepared notebook for CW305 communication and testing
- hold the board setup flow for programming, clocking, and register interaction

---

## What Is Already Done

- HLS-ready merged Ascon hardware code is prepared
- source files are separated properly
- HLS automation script is available
- CW305 hardware test notebook is available
- final report PDF is prepared
- instruction guide PDF is prepared
- presentation file is prepared

---

## What Is Not Yet Done

This folder also represents the next steps of the BTP, but those parts are still pending:

- physical CW305 trace capture
- FPGA-side CPA using real measured traces
- pure RTL implementation
- direct HLS vs RTL leakage comparison

So this phase includes both completed implementation work and the structured base for the next practical security stage.

---

## Why This Folder Matters

This is the main technical folder of the current BTP phase. It contains the code, automation, and written outputs needed to explain:

- how Ascon-128 was adapted for HLS,
- how the HLS exploration was performed,
- how the FPGA flow is prepared,
- and how the project will move toward hardware side-channel evaluation.

For project review, this folder is the main evidence of the shift from software security experiments to hardware security research.
