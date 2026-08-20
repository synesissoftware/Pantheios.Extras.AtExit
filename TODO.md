# Pantheios.Extras.AtExit - TODO <!-- omit in toc -->


## Functional improvements


### High

* [ ] Document (and optionally enforce) **`add` after `uninit`**: the libc `atexit` hook stays registered, so later **`add`** callbacks still run at process exit; docs currently imply the hook is a permanent no-op after drain;
* [ ] Document (or change) drain-while-locked: callbacks run under the spinlock, so a callback that calls **`add`** / **`uninit`** deadlocks; either forbid re-entrancy or copy the list, unlock, then invoke;


### Medium

* [ ] Serialise **`init`**: `s_initialised` is a plain `int` and `init` is not under the lock, so two threads can register two `atexit` hooks;
* [ ] Align **`reserved0`** / **`reserved1`**: header says they must be `NULL` / `0`, but the implementation ignores them — `assert` or drop the requirement;
* [ ] Stop treating **`atexit()`** failure as an `errno` / **`strerror()`** code; `EBUSY` / `ENOMEM` are errno values, `atexit` failure often is not;


### Low

* [ ] Document **`add` without `init`**: the list grows, but process exit will not drain it unless **`uninit`** is called;
* [ ] Initialise C11 `atomic_int s_mx` with **`ATOMIC_VAR_INIT(0)`** if compilers warn on `= 0`;
* [ ] Tests: **`add`** without **`init`** then **`uninit`**; **`add`** after **`uninit`**; version-macro unit test; keep process-exit coverage as scratch (or one automated case);
* [ ] Example: check **`add`** return values;


### Enhancements

* [ ] C++ RAII / `scope` wrapper;
* [ ] Unix-only pthread synchronisation scratch (with a Windows equivalent if revived);


## Performance improvements

* \<none>


## Packaging improvements

* [ ] Defer rewriting helper `MSYSTEM` → `mingw32-make` / MinGW-generator detection until the **HELPER-SCRIPTS-C-CXX.md** contract is frozen (same defect class as other Synesis C/C++ helpers);
* [ ] Split the unit-test implementation from its entry TU (then name the entry **entry.c**); until then keep the single-file **test.unit.atexit.api.c**;


<!-- ########################### end of file ########################### -->
