# mktiupgrade

Build Texas Instruments calculator OS upgrades from ROM dumps.

For additional info, see mktiupgrade.1.txt (or run man mktiupgrade if the man
pages are installed on your system).

## Compiling

Install cmake, make, asciidoc, and some other stuff.

On Windows, use cmake and Visual Studio, or MinGW. You'll have to read the docs
yourself to figure it out.

On Linux, Mac, and Cygwin, install cmake, a C compiler, make, and asciidoc. Run:

    $ cmake .
    $ make
    # make install
