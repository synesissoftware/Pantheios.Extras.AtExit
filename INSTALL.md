# Pantheios.Extras.AtExit - Installation and Use <!-- omit in toc -->

**Pantheios.Extras.AtExit** is a classic-form C library, insofar as it has
implementation files in its **src** directory and header files in its
**include/pantheios/extras** directory. Thus, once "installed", one must
simply include **pantheios/extras/atexit.h** and compile-in or link-in the
implementation.

The **C API** has no non-standard dependencies. Building the project's tests
additionally requires **STLSoft** and **xTests**.


## Table of Contents <!-- omit in toc -->

- [CMake](#cmake)
- [Bundled](#bundled)


## CMake

The primary choice for installation is by use of **CMake**.

1. Obtain the latest distribution of **Pantheios.Extras.AtExit**, from
   https://github.com/synesissoftware/Pantheios.Extras.AtExit/, e.g.

   ```bash
   $ mkdir -p ~/open-source
   $ cd ~/open-source
   $ git clone https://github.com/synesissoftware/Pantheios.Extras.AtExit/
   ```

2. Prepare the CMake configuration, via the **prepare_cmake.sh** script.

   For a minimal core-only install (no **STLSoft** / **xTests** required):

   ```bash
   $ cd ~/open-source/Pantheios.Extras.AtExit
   $ ./prepare_cmake.sh --disable-testing --disable-examples -v
   ```

   For a full build including examples and tests, install **STLSoft** 1.11
   (and **xTests** for tests) via their own **CMake** scripts first, then:

   ```bash
   $ cd ~/open-source/Pantheios.Extras.AtExit
   $ ./prepare_cmake.sh -v
   ```

   If **STLSoft** is available as a source tree rather than an installed
   **CMake** package, pass its root with `--stlsoft-root-dir` / `-s`.

   (**Hint**: execute `$ ./prepare_cmake.sh --help` for more information.)

3. Run a build of the generated **CMake**-derived build files via the
   **build_cmake.sh** script, as in:

   ```bash
   $ ./build_cmake.sh
   ```

   (**NOTE**: if you provide the flag `--run-make` (=== `-m`) in step 2 then
   you do not need this step.)

4. As a check (when testing was not disabled), execute the built unit-test
   programs via **run_all_unit_tests.sh**, as in:

   ```bash
   $ ./run_all_unit_tests.sh
   ```

5. Install the library on the host, via `cmake`, as in:

   ```bash
   $ sudo cmake --install ${SIS_CMAKE_BUILD_DIR:-./_build} --config Release
   ```

6. Then to use the library, it is a simple matter as follows:

   1. Assuming a simplest possible program to verify the installation:

      ```c
      /* main.c */
      #include <pantheios/extras/atexit.h>

      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>

      static void
      on_exit_fn(void* param)
      {
          printf("callback %p\n", param);
      }

      int main(void)
      {
          int const r = pantheios_extras_atexit_init(NULL, 0);

          if (0 != r)
          {
              fprintf(stderr, "%s\n", strerror(r));

              return EXIT_FAILURE;
          }

          pantheios_extras_atexit_add(on_exit_fn, (void*)1);
          pantheios_extras_atexit_uninit();

          return EXIT_SUCCESS;
      }
      ```

   2. Compile your project against **Pantheios.Extras.AtExit**:

      Due to the installation step (step 5 above) there is no requirement
      for an explicit include directory:

      ```bash
      $ cc -c main.c
      ```

   3. Link your project against **Pantheios.Extras.AtExit**:

      ```bash
      $ cc main.o -lpantheios.extras.atexit
      ```

   4. Test your project:

      ```bash
      $ ./a.out
      callback 0x1
      $
      ```

   Consumers that use **CMake** may instead depend on the installed package:

   ```cmake
   find_package(Pantheios.Extras.AtExit REQUIRED)
   target_link_libraries(your_target PRIVATE Pantheios.Extras.AtExit::core)
   ```


## Bundled

**Pantheios.Extras.AtExit** is small enough that it may be bundled into
other projects. In that case:

* add **Pantheios.Extras.AtExit**'s **include** directory to your project's include path;
* compile **src/atexit.api.c** into your build (or link a previously built **libpantheios.extras.atexit**); and
* `#include <pantheios/extras/atexit.h>`.


<!-- ########################### end of file ########################### -->
