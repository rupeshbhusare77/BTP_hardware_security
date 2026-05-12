# Phase 1: 7th Semester

This folder contains the 7th semester work of the BTP. The focus in this phase was on learning and applying side-channel attacks on a firmware target using the ChipWhisperer Nano platform.

---

## Technical Focus

- Target board: ChipWhisperer Nano
- Target device: STM32F0 microcontroller
- Main cryptographic target: AES
- Main attacks studied: SPA, DPA, CPA
- Leakage model used in the advanced attack stage: Hamming Weight

---

## Purpose of This Phase

This phase built the base understanding required for the later hardware-security work. It covered:

- how to set up ChipWhisperer for trace capture
- how firmware operations leak through power traces
- how secret-dependent processing can be studied statistically
- how AES intermediate values can be attacked using CPA

This phase is the foundation of the current semester work. Without this step, the move to FPGA hardware attacks would not be properly grounded.

---

## Folder Contents

```text
phase-1_7th-sem/
├── README.md
└── report/
    ├── Chipwhisperer_report_tutorial_rupesh.pdf
    └── Presentation_chipwhisperer.pdf
```

### `report/`
This folder stores the main deliverables from the 7th semester.

Current files:
- `Chipwhisperer_report_tutorial_rupesh.pdf`
- `Presentation_chipwhisperer.pdf`

### Meaning of these files

- `Chipwhisperer_report_tutorial_rupesh.pdf`
  - the main written report for the previous semester
  - covers the Nano-based work and attack learning path

- `Presentation_chipwhisperer.pdf`
  - the presentation material for Phase 1
  - useful for summarizing previous semester progress quickly

---

## Academic Importance

Phase 1 is not only old work storage. It is the first technical part of the full BTP journey. It explains:

- where the side-channel attack understanding started
- how CPA was first studied practically
- why the project later moved to FPGA-based hardware

This makes it an important reference when explaining the full BTP progression to reviewers or faculty.
