# Pantheios.Extras.AtExit <!-- omit in toc -->

Standalone C library that registers multiple `atexit`-style callbacks (function + `void*` parameter) under the **Pantheios.Extras** namespace.

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/Pantheios.Extras.AtExit.svg)](https://github.com/synesissoftware/Pantheios.Extras.AtExit/releases/latest)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/Pantheios.Extras.AtExit)](https://github.com/synesissoftware/Pantheios.Extras.AtExit/commits/master)
[![CI](https://github.com/synesissoftware/Pantheios.Extras.AtExit/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/Pantheios.Extras.AtExit/actions/workflows/ci.yml)


## Table of Contents <!-- omit in toc -->

- [Introduction](#introduction)
  - [Why at-exit functionality](#why-at-exit-functionality)
  - [Dependencies](#dependencies)
- [Installation](#installation)
- [Components](#components)
  - [C API / core library](#c-api--core-library)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies-1)
    - [Development dependencies](#development-dependencies)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**Pantheios.Extras.AtExit** is a small compiled **C** library in the [Pantheios](http://pantheios.org/) extras namespace. Unlike most/all of the other Pantheios Extras libraries, it is **not** a Pantheios (or STLSoft) dependency: the core target needs only the C standard library.

Its raison d'être is to provide a richer alternative to the standard C library's `atexit()`, with an explicit callback list so client code can register many `(function, void* param)` pairs that are invoked in **LIFO** order — either when `pantheios_extras_atexit_uninit()` drains the list, or later via the single libc `atexit` hook registered at init. Importantly. each callback is also accompanied by a `void*` parameter that is given back to the callback when it is invoked, thereby enabling stateful cleanup.

`pantheios_extras_atexit_init()` must be called at most once per process. Later calls fail (`EBUSY`) even after `uninit()`, because libc `atexit` handlers cannot be unregistered. After a drain, the registered hook is a no-op.


### Why at-exit functionality

C programs often need last-chance cleanup: flushing diagnostics, releasing process-wide resources, or tearing down library state that has no natural owner once `main` has returned. libc `atexit()` is the portable hook for that, but it is a poor *unit of currency* for libraries and layered applications:

* Handlers are `void (*)(void)`. Any context must live in globals, which couples unrelated components and makes reuse harder;
* The number of handlers is small and shared (`ATEXIT_MAX`, often 32). A library that registers one slot per subsystem, sink, or module can exhaust the table for the rest of the process;
* There is no unregister. A component that is done *before* process exit cannot drop its handler, and a second registration is another scarce slot;

**Pantheios.Extras.AtExit** exists so that many callers can each register `(function, void* param)` without consuming a libc slot per callback. The library takes **one** `atexit` registration at `init` and maintains its own LIFO list. `uninit` drains that list early when the process is still in a well-defined state; if `uninit` is not used, the same list runs from the libc hook at exit.

That is the same protocol as other **Pantheios.Extras** helpers: keep the core logging library free of this concern, and give C clients a small, stdlib-only facility instead of rolling an ad-hoc static list in every program.


### Dependencies

| Component    | Implemented in | Use in                                | Dependencies |
| ------------ | -------------- | ------------------------------------- | ------------ |
| Core library | C              | C — via **pantheios/extras/atexit.h** | C standard library |
| Examples (C) | C              | —                                     | — |
| Tests (C)    | C              | —                                     | [STLSoft](https://github.com/synesissoftware/STLSoft/), [xTests](https://github.com/synesissoftware/xTests/) |


## Installation

Detailed instructions — via **CMake**, via bundling — are provided in the accompanying [INSTALL.md](./INSTALL.md) file.


## Components

### C API / core library

```C
int
pantheios_extras_atexit_init(
    void*       reserved0
,   unsigned    reserved1
);

void
pantheios_extras_atexit_uninit(
    void
);

int
pantheios_extras_atexit_add(
    void    (*pfn)(void* param)
,   void*   param
);
```

`reserved0` / `reserved1` are unused and must be passed as `NULL` / `0`.


## Examples

Examples are provided in the `examples` directory.


## Project Information


### Where to get help

[GitHub Page](https://github.com/synesissoftware/Pantheios.Extras.AtExit)


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/Pantheios.Extras.AtExit.


### Dependencies

* none for the core library;


#### Development dependencies

* [STLSoft](https://github.com/synesissoftware/STLSoft/);
* [xTests](https://github.com/synesissoftware/xTests/);


### Related projects

* [Pantheios](https://github.com/synesissoftware/Pantheios);
* [Pantheios.Extras.DiagUtil](https://github.com/synesissoftware/Pantheios.Extras.DiagUtil);
* [Pantheios.Extras.Main](https://github.com/synesissoftware/Pantheios.Extras.Main);


### License

**Pantheios.Extras.AtExit** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->
