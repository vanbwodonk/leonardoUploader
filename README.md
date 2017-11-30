# A simple binary for Arduino Leonardo Upload

This is a very simple binary file to upload firmware .hex into Arduino Leonardo.

## Features

- Auto reset with 1200 baud

## Requirements

### AVRDUDE
AVRDUDE is a utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming technique (ISP). Under ubuntu 16.04 just install with this:
```
sudo apt-get install avrdude
```

## Installation

```
git clone https://github.com/vanbwodonk/leonardoUploader.git
cd leonardoUploader
make
sudo make install
```

## Usage

```
leonardoUploader [PORT] [FILE.hex]
```
example
```
leonardoUploader /dev/ttyACM0 Blink.ino.hex
```
