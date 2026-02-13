# 🔌👻 RutOS Daemon

> A Tuya IoT daemon for Teltonika RUTX routers running RutOS (OpenWRT-based), packaged as two separate OpenWRT `.ipk` packages.

---

## Overview

`RutOS Daemon` is a C-based daemon that runs on Teltonika RUTX routers and reports device data to the Tuya IoT cloud. It is built against the RutOS SDK (OpenWRT) and cross-compiled for ARM Cortex-A7.

The project ships as two independent packages:

| Package | Description |
|---------|-------------|
| **`tuyad`** | The daemon — communicates with the Tuya IoT cloud and sends router data (e.g. RAM usage) via ubus |
| **`libtuyad`** | The Tuya IoT C SDK, packaged as a shared library — auto-downloaded from upstream during build |

---

## Requirements

- Teltonika RUTX router running RutOS
- RutOS SDK installed at: `~/Documents/RUTX_R_GPL_00.07.13.1/rutos-ipq40xx-rutx-sdk`
- SSH access to the router (default: `root@192.168.1.1`)
- [Tuya IoT Platform](https://iot.tuya.com) credentials (Device ID, Device Secret, Product ID)

---

## Building

Run the following from **inside the RutOS SDK folder**:

```bash
# Clean and compile both packages
make package/tuyad/clean
make package/tuyad/compile
```

> Make sure you've cloned this repo and copied `libtuyad/` and `tuyad/` into the SDK's package folder before building.

---

## Deploying to the Device

From inside the SDK folder on your **dev PC** (`[$]`):

```bash
# Copy packages to the router
scp bin/packages/arm_cortex-a7_neon-vfpv4/base/libtuyad_1.0.1-1_arm_cortex-a7_neon-vfpv4.ipk root@192.168.1.1:~
scp bin/packages/arm_cortex-a7_neon-vfpv4/base/tuyad_1.0.0-1_arm_cortex-a7_neon-vfpv4.ipk root@192.168.1.1:~
```

SSH into the router (`[#]`) and confirm the files are present:

```bash
ssh root@192.168.1.1
ls ~
```

Then install both packages **in order**:

```bash
opkg install libtuyad_1.0.1-1_arm_cortex-a7_neon-vfpv4.ipk
opkg install tuyad_1.0.0-1_arm_cortex-a7_neon-vfpv4.ipk
```

On first run, the daemon will prompt you to enter your **Device ID**, **Device Secret**, and **Product ID** from the Tuya IoT platform.

---

## Usage

```bash
# Restart the daemon
/etc/init.d/tuyad restart

# Stop the daemon
/etc/init.d/tuyad stop

# View daemon logs
logread
```

If you entered incorrect credentials, fix them with `uci` or simply restart the daemon to re-enter them.

---

## Uninstalling

On the router (`[#]`), from `[root@RUTX08:~#]`:

```bash
# Remove packages
opkg remove tuyad
opkg remove libtuyad

# Remove package files
rm -f libtuyad_1.0.1-1_arm_cortex-a7_neon-vfpv4.ipk
rm -f tuyad_1.0.0-1_arm_cortex-a7_neon-vfpv4.ipk
```

> Make sure you are in the home directory (`~`) when removing files, otherwise the `rm` commands will fail.

---

## Architecture

- The **Tuya SDK source** is auto-downloaded from the upstream remote during build — it is not bundled in this repository
- The daemon uses **ubus** to query live router data (e.g. RAM usage) and forwards it to the Tuya cloud
- No global variables are used for passing data between functions
- All daemon activity is written to the **system log**, viewable via `logread`

---

## Contributions
Contributions are welcome! If you'd like to improve the project or add new features, please submit a pull request.

## Author

This project is maintained by [Tadas](https://github.com/t4d4s). Feel free to reach out with any questions or feedback.
