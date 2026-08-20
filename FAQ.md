# Pantheios.Extras.AtExit - FAQ <!-- omit in toc -->

The FAQ list is under (constant) development. If you post a question on the
Issues forum (https://github.com/synesissoftware/Pantheios.Extras.AtExit/issues)
it will be used to create one.


## Table of Contents <!-- omit in toc -->

- [Q1: "How do I build Pantheios.Extras.AtExit?"](#q1-how-do-i-build-pantheiosextrasatexit)
- [Q2: "How do I install Pantheios.Extras.AtExit?"](#q2-how-do-i-install-pantheiosextrasatexit)
- [Q3: "How do I use Pantheios.Extras.AtExit?"](#q3-how-do-i-use-pantheiosextrasatexit)
- [Q4: "Why does a second init fail after uninit?"](#q4-why-does-a-second-init-fail-after-uninit)


# FAQs: <!-- omit in toc -->

## Q1: "How do I build Pantheios.Extras.AtExit?"

See [INSTALL.md](./INSTALL.md) for the recommended **CMake** flow
(**prepare_cmake.sh**, then **build_cmake.sh**).

For a minimal core-only build with no external dependencies:

```bash
$ ./prepare_cmake.sh --disable-testing --disable-examples -m
```

For a full build (including tests), install **STLSoft** 1.11 and **xTests**
first, then:

```bash
$ ./prepare_cmake.sh -m
```

Execute `$ ./prepare_cmake.sh --help` for the full set of options.


## Q2: "How do I install Pantheios.Extras.AtExit?"

See [INSTALL.md](./INSTALL.md).


## Q3: "How do I use Pantheios.Extras.AtExit?"

Include **pantheios/extras/atexit.h** and link against
**libpantheios.extras.atexit** (the **CMake** target is
`Pantheios.Extras.AtExit::core`).

Call `pantheios_extras_atexit_init(NULL, 0)` once, then
`pantheios_extras_atexit_add()` for each callback. Callbacks run in LIFO
order from `pantheios_extras_atexit_uninit()` or, if you do not uninit, from
the registered libc `atexit` hook. `pfn` must be non-`NULL` (`assert`).


## Q4: "Why does a second init fail after uninit?"

`pantheios_extras_atexit_init()` registers one libc `atexit` handler. That
registration cannot be undone. `uninit()` drains and frees the callback
list so the hook is a no-op, but a second `init` still returns `EBUSY`.


<!-- ########################### end of file ########################### -->
