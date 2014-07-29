mktiupgrade (1)
==============

mktiupgrade - Build Texas Instruments calculator OS upgrades from ROM dumps

Installation
------------

**Linux, Mac**:

1. Install cmake and asciidoc
2. `cmake .`
3. `make`
4. `make install`

**Windows**

Install cygwin with cmake, asciidoc, gcc, and make. Then, follow the Linux
instructions.

Synopsis
--------

'mktiupgrade' [options] _infile_ _outfile_ [pages...]

Description
-----------

Builds (and optionally signs) upgrade files to be sent to TI calculators from ROM
dumps. _infile_ should be a ROM dump with the OS, and _outfile_ is the 73u, 8xu, or
8cu file to write the resulting upgrade to. Each page (specified in hexadecimal)
will be extracted from the ROM dump and included with the upgrade. Additional
pages may be automatically included if needed.

Options
-------

*-d, \--device* <device>::
	Specifies the target device type. If omitted, it will be inferred by the size
	of the ROM dump. The following options are valid:

	* TI-73
	* TI-83+
	* TI-83+SE
	* TI-84+
	* TI-84+SE
	* TI-84+CSE

*-k, \--key* <key file>::
	Specify the key file to sign the upgrade with. If omitted (and -s is not
	specified), the upgrade will be unsigned.

*-n, \--key-name* <name>::
	Specify the name of the key, to be written to the OS header, in hexadecimal.
	If not included, it will be inferred from the key file name (i.e. "0A.key").
	Specify this option *after* the key file.

*-p, \--print*::
	Prints information about the upgrade before writing it.

*-r, \--hw-revision* <revision>::
	Specify the maximum hardware revision. The default is 5.

*-s, \--signature* <signature file>::
	Instead of calculating the signature while writing the upgrade file, instead
	use this signature file. This option overrides -k. You should specify -n
	manually. The default value is 0A if you choose not to.

*-v, \--version* <version>::
	The upgrade version, in the format "major.minor". Each part can be between 0
	and 255, inclusive. The default is "1.0".

Supported Devices
-----------------

The following Texas Instruments calculators are supported:

* TI-73
* TI-83+
* TI-83+ Silver Edition
* TI-84+
* TI-84+ Silver Edition
* TI-84+ Color Silver Edition

Signing Keys
------------

The Texas Instruments cryptographic signing keys may be found at
<http://brandonw.net/calculators/keys/>. These keys do not work on all
calculators, and you may need to use an additional exploit to load your operating
system on newer models. An example of this process can be found in KnightOS,
availble at <https://github.com/KnightOS/KnightOS>.

Examples
--------

mktiupgrade input.rom output.8xu 00 01 02 03 4F::
	Makes an upgrade from pages 00-03 and 4F of _input.rom_, then writes it to
	_output.8xu_, unsigned.

mktiupgrade -k 0A.key -v 2.3 input.rom output.8xu 00 01 02 03 4F::
	Builds and signs an upgrade with the 0A key, and marks it as version "2.3".

mktiupgrade -s exploit.sig -n 0F input.rom output.8cu 00 01 02 03::
	Builds an upgrade and uses the contents of _exploit.sig_ as the signature, and
	indicates that the key is the 0F key. The result is written to _output.8cu_.

Authors
-------

Maintained by Drew DeVault <sir@cmpwn.com>, who is assisted by other open
source contributors. For more information about mktiupgrade development, see
<https://github.com/KnightOS/mktiupgrade>.
