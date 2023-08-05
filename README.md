# Embedded Dart

A *very* naive attempt at embedding precompiled AOT Dart code in a shared library.

## Why?

Dart is an incredibly powerful and versatile language which many developers love. Why should its benefits be limited to those writing Dart or Flutter applications?
Embedding Dart code in a shared library would enable the use of Dart anywhere and further help solidify its place as the go-to language for cross-platform development!
Write once, run *anywhere* - that's the dream!

## Running

> **NOTE**: The code in this repo is **not** working yet. Any help in getting it running is appreciated!

Make sure you have a local clone of the Dart SDK and have built it using the command (replacing `arm64` with your current architecture, if necessary):

> See the Dart team's [Building the SDK][] wiki for more details.

```
./tools/build.py --no-goma --mode release --arch arm64 create_sdk
```

> And update the `DART_SDK_ROOT` and `DART_SDK_OUT` variables in `EmbeddedDart/CMakeLists.txt` as necessary.

Create an AOT snapshot of the main entrypoint:

```
dart compile aot-snapshot bin/embedded_dart.dart
```

> And update the path to the AOT ELF in `EmbeddedDart/main.cpp:22`.

Finally, build & run the C++ project located in `EmbeddedDart/`.

[Building the SDK]: https://github.com/dart-lang/sdk/wiki/Building
