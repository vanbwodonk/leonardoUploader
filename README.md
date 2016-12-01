# A simple binary for Arduino Leonardo Upload

This is a very simple binary file to upload firmware .hex into Arduino Leonardo.

## Features

- Auto reset with 1200 baud

## Installation

```
https://github.com/vanbwodonk/leonardoUploader.git
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
