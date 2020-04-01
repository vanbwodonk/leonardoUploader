# A simple binary for Arduino Leonardo Upload

This is a very simple binary file to upload firmware .hex into Arduino Leonardo/Micro (ATmega32u4 with CDC bootloader). Tested with Ubuntu 16.04 and Raspbian Stretch.

## Features

- Auto reset with 1200 baud

## Requirements

### AVRDUDE - Linux
AVRDUDE is a utility to download/upload/manipulate the ROM and EEPROM contents 
of AVR microcontrollers using the in-system programming technique (ISP). 

Under ubuntu 16.04 just install with this:

```
sudo apt-get install avrdude
```

Under Arch/Manjaro:
```
sudo pacman -S avrdude
```

### AVRDUDE - Win32

Only available AVRDUDE distribution is 32-bit in case of windows.

Here is the locaiton it can be downloaded from:

https://download.savannah.gnu.org/releases/avrdude/

Look for `avrdude-6.3-mingw32.zip`	size **218K**
released on `17-Feb-2016 10:03`

We have included the same in the `win32` directory.
One can extract this file the same directory.

**Note:** If you do not have the `avrdude` program in path then
`leonardoUploader` would not work.

## Installation - Linux

```
git clone https://github.com/vanbwodonk/leonardoUploader.git
cd leonardoUploader/linux
make
sudo make install
```

## Installation - Win32

### Pre-requsite : Need MinGW installed

https://sourceforge.net/projects/mingw/files/Installer/

Install using the `mingw-get-setup.exe` program.

Select the following:

 * `mingw-developer-toolkit`
 * `mingw32-base`
 * `mingw-gcc-g++`
 * `msys-base`

### Avrdude in PATH

Need the AVRDUDE in path so that `leonardoUploader`
can perform the operations.

Follow the steps outlined [`AVRDUDE - Win32`](https://github.com/vanbwodonk/leonardoUploader#avrdude---win32).

### Then:

Open the MSYS Terminal : `C:\MinGW\msys\1.0\msys.bat`

And type:

```
git clone https://github.com/boseji/leonardoUploader.git
cd leonardoUploader/win32
make
```

### Next:

Add the directory location `leonardoUploader/win32` to Windows `PATH` variable 
to have direct commandline access.

## Usage

```
leonardoUploader [PORT] [FILE.hex]
```
### Example

```
leonardoUploader /dev/ttyACM0 Blink.ino.hex
```

or for Windows

```
leonardoUploader COM10 Blink.ino.hex
```

# License

[GNU General Public License, version 2](https://www.gnu.org/licenses/gpl-2.0.html)

Original Work by [***Arif Darmawan***](https://github.com/vanbwodonk)
Modified and updated for Windows by [*@boseji*](https://github.com/boseji)

## For AVRdude refer to:

[AVRdude](https://savannah.nongnu.org/projects/avrdude)

Original Work by [***Joreg Wunsh***](https://savannah.nongnu.org/users/joerg_wunsch)
