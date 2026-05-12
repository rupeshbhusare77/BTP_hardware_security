# 1. Create the HLS project and set the top function
open_project ascon_hardware_dse
set_top ascon_core

# 2. Add your C source file (Headers are automatically linked)
add_files ascon_core.c

# ==========================================================
# SOLUTION 1: BASELINE
# Pure C translation with no extra hardware optimizations.
# ==========================================================
open_solution "solution1_baseline"
set_part {xc7a100tftg256-2}
create_clock -period 10 -name default
csynth_design

# ==========================================================
# SOLUTION 2: UNROLLED
# Copies the hardware inside the loop so it runs in parallel.
# ==========================================================
open_solution "solution2_unrolled"
set_part {xc7a100tftg256-2}
create_clock -period 10 -name default
set_directive_unroll -factor 2 "ascon_core/data_loop"
csynth_design

# ==========================================================
# SOLUTION 3: PIPELINED
# Turns the loop into an "assembly line" for massive speed.
# ==========================================================
open_solution "solution3_pipelined"
set_part {xc7a100tftg256-2}
create_clock -period 10 -name default
set_directive_pipeline "ascon_core/data_loop"
csynth_design

# ==========================================================
# SOLUTION 4: DATAFLOW
# Allows separate functions in the code to run at the same time.
# ==========================================================
open_solution "solution4_dataflow"
set_part {xc7a100tftg256-2}
create_clock -period 10 -name default
set_directive_dataflow "ascon_core"
csynth_design

# Close the project and exit the terminal gracefully
close_project
exit