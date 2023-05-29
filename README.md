# CMakeResources demo test

Sample project demonstrating using CMake resources to distribute port allocations for
an example test. Ideally use port 0 to just get a random port allocated but if you
have a use case for a deterministic port that won't be duplicated across tests then
this ~~barely~~ works.

```bash
cmake -S . -B build --preset\=default -DCMAKE_EXPORT_COMPILE_COMMANDS\=ON -DCMAKE_COLOR_DIAGNOSTICS\=ON
cmake --build build --preset\=default --parallel\=18
env CLICOLOR_FORCE\=1 GTEST_COLOR\=1 ctest --test-dir build --preset\=default --output-on-failure --schedule-random test
```

CTest will schedule upto 16 tests in parallel but because the portoffset resource in
CMakeResources.txt only has 3 slots no more than 3 tests with a dependence on that
resource will be defined. The project defines 15 tests all of the [same
executable](tests/main.t.cc) and all it does is start up, read the resource
environment, bind to a port **succesfully** and then wait a bit before exiting. To
confirm the test never steps over port allocations you can try adding a modulo chock
to the port read to make it step over itself.
