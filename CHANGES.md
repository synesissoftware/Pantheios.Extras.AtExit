# Pantheios.Extras.AtExit - Changes <!-- omit in toc -->


## 0.1.4-beta4 - 1st November 2026

* testing:
  * `File:` labels under **examples** name the project-relative path;
  * `File:` labels under **test** name the project-relative path;
* build:
  * the **Check test names** job runs **STLSoft** **check_unit_test_names.rb** over **examples** and **test**;


## 0.1.4-beta3 - 27th October 2026

* Defined `HAS_xTests` and `HAS_XTESTS` when **xTests** is detected;


## 0.1.4-beta2 - 14th October 2026

* Advanced the library version to **0.1.4-beta2** (`PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_2`, `PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS` **0x82**);
* Migrated the version low-byte macro to **`PANTHEIOS_EXTRAS_ATEXIT_VER_RELSTATUS`**, retaining **`PANTHEIOS_EXTRAS_ATEXIT_VER_ALPHABETA`** as a documentation-skip alias;
* Gold-copied tip **`run_all_examples.*`** / **`run_all_scratch_tests.*`** / **`run_all_unit_tests.sh`** from **misc-dev-scripts** `cmake-helpers` `@0754c23` (discovery exclusions; scratch **`--skip-interactive`**);
* Set **`test.scratch.versions`** **`PROGRAM_NAME`** to **`test.scratch.versions`**;
* Added **`.github/actions/install-sis-deps`**; **ci-cell** uses **`${{ env.SIS_DEPS }}`**, execute-bit restore after artifact download, and Windows **`shell: cmd`** dogfood of **`run_all_*.cmd`**;


## 0.1.4-beta1 - 9th October 2026

* Applied **misc-dev-scripts** **0.6.0** editor/Git/`.sis` drop-in templates on **boilerplate**;
* Restored historical **.gitignore** patterns as a sorted union with **misc-dev-scripts** gold section layout;
* Modernised CMake helpers to the Phase 4b dialect (`SisClr_*` / `-A`, `sis_cmake_build`, no MinGW-from-`MSYSTEM`), retaining **`--stlsoft-root-dir`** as a project-specific **prepare_cmake.sh** flag;
* Native Windows **`run_all_*.cmd`** runners (no Bash wrap); aggregate **`run_all_automated_tests.*`**, with **`run_all_unit_tests.*`** now unit-only;
* Renamed the scratch version-reporter target to **`test.scratch.versions`**;
* Updated the **ci-cell.yml** component-test job to call **run_all_component_tests.sh**, since **run_all_unit_tests.sh** is now unit-only;
* Added `PANTHEIOS_EXTRAS_ATEXIT_VER_0_1_4_BETA_1` and updated unit test **test.unit.version** accordingly;


## 0.1.3 - 31st August 2026

* Retargeted the current line from **0.1.2-alpha1** to **0.1.3**;
* Asserted **`pantheios_extras_atexit_init()`** `reserved0` / `reserved1` as `NULL` / `0`;
* Example **example.c.1** checks **`add`** return values; unit tests cover **`add`** without **`init`**, **`add`** after **`uninit`**, and version macros;
* Added a **README.md** rationale for why libc `atexit()` is insufficient and what this library is for;


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
