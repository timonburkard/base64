# base64

A small C program for encoding/decoding data as Base64.

## Build

```sh
./build.sh
```

The executable is created as `base64` resp. `base64.exe` in the project root.

## Usage

<pre>
$ ./base64 --help
Encode/decode data in base64 format

<u>Usage:</u> base64 &lt;COMMAND&gt;

<u>Commands:</u>
  encode     encode something as base64
  decode     decode something from base64

<u>Options:</u>
  -h, --help     Print help
  -V, --version  Print version
</pre>

### Encode

<pre>
$ ./base64 encode --help
encode something as base64

<u>Usage:</u> base64 encode &lt;FILE&gt; [OPTIONS]

<u>Arguments:</u>
  &lt;FILE&gt;  File to hex dump or '-' for stdin

<u>Options:</u>
      --text  Input is a text string instead of a file
  -h, --help  Print help
</pre>

### Decode

_Not yet implemented_

## Examples

### Encode

Encode a file:

```sh
base64 encode path/to/file
```

Encode a text string:

```sh
base64 encode "foobar" --text
```

### Decode

_Not yet implemented_

## Tests

Configure and build the project, then run the CTest suite:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
