# Pantheios.Extras.AtExit - Changes <!-- omit in toc -->


## 0.1.3 - 23rd August 2026

* Retargeted the current line from **0.1.2-alpha1** to **0.1.3**;
* Asserted **`pantheios_extras_atexit_init()`** `reserved0` / `reserved1` as `NULL` / `0`;


## 0.1.2-alpha1 - 21st August 2026

* Modernised library version macros to computed `PANTHEIOS_EXTRAS_ATEXIT_VER` (`VER_MAJOR` / `VER_MINOR` / `VER_PATCH` / `VER_ALPHABETA`, with `VER_REVISION` alias) targeting **0.1.2-alpha1**;
* Added **ctest_cmake.sh** and **run_all_unit_tests.cmd**;
* Ensured C/C++ sources end with a blank line after the end-of-file marker, and used `char* argv[]` in the unit-test `main`;
* Renamed the scratch program implementation to **main.c**;
* Recorded functionality-review items in **TODO.md**; deferred applying them, and deferred the helper **MSYSTEM**/MinGW rewrite until the **HELPER-SCRIPTS-C-CXX.md** contract is frozen;


## 0.1.1 - 16th August 2026

* Recovered **Pantheios.Extras.AtExit** from Hautacam (`pantheios/extras/AtExit/0.1`, Created 30th December 2011) as a nested compiled C library;
* Added **CMake** packaging, **.sis** helper-script identity, modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**), and install-smoke as a C consumer;
* Replaced the unshippable GCC atomic typedef with C11 `<stdatomic.h>` `atomic_int` where available, else MSVC `InterlockedIncrement`/`Decrement`, else GCC/Clang `__sync_*`;
* Dropped the recovered `#error` that excluded Clang/AppleClang;
* Distinguished initialisation from an empty callback list via a dedicated `s_initialised` flag (first `add` is what sets `s_head`);
* Implemented `pantheios_extras_atexit_uninit()` to drain remaining callbacks (LIFO), free nodes, and leave the libc `atexit` hook as a no-op (libc still cannot unregister that hook, so a second `init` remains `EBUSY`);
* Added C example and **xTests** unit coverage for init / re-init / `add` / `uninit` drain;


<!-- ########################### end of file ########################### -->
