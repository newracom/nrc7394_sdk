# README.md

# NRC7394 J-Link Materials

## 1. Overview

This package contains J-Link and Ozone-related materials for NRC7394 development and debugging.

The package includes:

* J-Link device support files
* Ozone project configuration
* Boot configuration utility
* Example boot configuration JSON

These materials are intended for firmware development, debugging, and flash programming.

---

## 2. Package Structure

```text
J-Link Materials/
├─ README.md
├─ VERSION.md
│
├─ jlink/
│  ├─ FlashNRCXXXX.elf
│  └─ JLinkDevices.xml
│
├─ ozone/
│  └─ project_example.jdebug
│
└─ boot_config/
   ├─ nrc7394_boot_config.exe
   └─ boot_config.json
```

---

## 3. J-Link Device Support Files

Location:

```text
jlink/
```

Files:

* `FlashNRCXXXX.elf`
* `JLinkDevices.xml`

These files are required for:

* Device recognition in J-Link tools
* External flash programming support

### Installation

Copy the files into the SEGGER J-Link installation directory.

Example:

```text
C:\Program Files\SEGGER\JLink\
```

---

## 4. Ozone Project File

Location:

```text
ozone/
```

File:

* `project_example.jdebug`

This file provides an example Ozone debug project configuration for NRC7394.

---

## 5. Boot Configuration Tool

Location:

```text
boot_config/
```

Files:

* `nrc7394_boot_config.exe`
* `boot_config.json`

The boot configuration tool is used to configure boot-time behavior of the firmware.

Supported configuration options:

* `jlink_enable`
* `wdt_disable`
* `crc_check_skip`

Example:

```json
{
  "jlink_enable": 1,
  "wdt_disable": 1,
  "crc_check_skip": 1
}
```

### Usage

1. Reset the board into XIP write (download) mode
2. Disconnect any active console terminal
3. Run the following command:

```bash
nrc7394_boot_config.exe <serial port> <boot_config.json path>
```

Example:

```bash
nrc7394_boot_config.exe COM3 boot_config.json
```

---

## 6. Notes

* These materials are intended for development and debugging purposes
* Disabling watchdog or CRC checks may reduce firmware safety and stability
* Restore default settings for production firmware when necessary
