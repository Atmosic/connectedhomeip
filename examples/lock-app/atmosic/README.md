# Atmosic Matter Lock Example Application

The Atmosic Lock Example demonstrates how to remotely control a door lock
device with one basic bolt. It uses buttons to test changing the lock and device
states and LEDs to show the state of these changes. You can use this example as
a reference for creating your own application.

The example is based on
[Matter](https://github.com/project-chip/connectedhomeip) and Atmosic
Technologies' OpenAir SDK, and was created to facilitate testing and
certification of a Matter device communicating over a low-power, 802.15.4 Thread
network.

The example behaves as a Matter accessory, that is a device that can be paired
into an existing Matter network and can be controlled by this network. In the
case of Thread, this device works as a Thread Sleepy End Device.

<hr>

## Overview

This example is running on Atmosic Technologies'
[OpenAir](https://github.com/Atmosic/openair)
and [Zephyr RTOS](https://zephyrproject.org/).

By default, the Matter accessory device has IPv6 networking disabled. You must
pair it with the Matter controller over Bluetooth® LE to get the configuration
from the controller to use the device within a Thread or Wi-Fi network. You have
to make the device discoverable manually (for security reasons). See
[Bluetooth LE advertising](#bluetooth-le-advertising) to learn how to do this.
The controller must get the commissioning information from the Matter accessory
device and provision the device into the network.

The sample uses buttons for changing the lock and device states, and LEDs to
show the state of these changes. You can test it in the following ways:

-   Standalone, using a single EVK that runs the door lock application.

-   Remotely over the Thread protocol, which
    requires more devices, including a Matter controller that you can configure
    either on a PC or a mobile device.

### Bluetooth LE advertising

In this example, to commission the device onto a Matter network, it must be
discoverable over Bluetooth LE. For security reasons, you must start Bluetooth
LE advertising manually after powering up the device by pressing:

-   On ATMEVK-3425 and ATMEVK-3430e: **Button 2**.

### Bluetooth LE rendezvous

In this example, the commissioning procedure is done over Bluetooth LE between a
Matter device and the Matter controller, where the controller has the
commissioner role.

To start the rendezvous, the controller must get the commissioning information
from the Matter device. The data payload is encoded within a QR code and printed to
the UART console.

#### Thread provisioning

The provisioning operation, which is the Last part of the rendezvous procedure,
involves sending the Thread network credentials from the Matter
controller to the Matter device. As a result, the device joins the Thread
network and can communicate with other devices in the network.

<hr>

## Requirements

The application requires a specific revision of the OpenAir SDK to work
correctly. See [Setting up the environment](#setting-up-the-environment) for
more information.

### Supported devices

The example supports building and running on the following devices:

| Hardware platform                                                                         | Build target               | Platform image                                                                                                                                   |
| ----------------------------------------------------------------------------------------- | -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| [ATMEVK-3425](https://atmosic.com/support_developer_kits/)                                | `ATMEVK-3425-PQK-2`        | <details><summary>ATMEVK-3425</summary></details>                                                                                                |
| [ATMEVK-3430e](https://atmosic.com/support_developer_kits/)                               | `ATMEVK-3430e-WQN-2`       | <details><summary>ATMEVK-3430e</summary></details>                                                                                               |

For all EVKs, JP25 and JP27 need to be installed in order to enable the
buttons and the LEDs.

<hr>

## Device UI

This section lists the User Interface elements that you can use to control and
monitor the state of the device. These correspond to PCB components on the
platform image.

### LEDs

This section describes all behaviors of LEDs located on platform image.

**LED 1 - Red** shows the overall state of the device and its connectivity. The
following states are possible:

-   _Short Flash On (50 ms on/950 ms off)_ &mdash; The device is in the
    unprovisioned (unpaired) state and is waiting for a commissioning
    application to connect.

-   _Rapid Even Flashing (100 ms on/100 ms off)_ &mdash; The device is in the
    unprovisioned state and a commissioning application is connected through
    Bluetooth LE.

-   _Short Flash Off (950ms on/50ms off)_ &mdash; The device is fully
    provisioned, but does not yet have full connectivity for Thread
    network.

-   _Solid On_ &mdash; The device is fully provisioned.

**LED 2 - Yellow** simulates the lock bolt and shows the state of the lock.
The following states are possible:

-   _Solid On_ &mdash; The bolt is extended and the door is locked.

-   _Off_ &mdash; The bolt is retracted and the door is unlocked.

-   _Rapid Even Flashing (100 ms on/100 ms off during 2 s)_ &mdash; The
    simulated bolt is in motion from one position to another.

    Additionally, the LED starts blinking evenly (500 ms on/500 ms off) when the
    Identify command of the Identify cluster is received on the endpoint 1. The
    command’s argument can be used to specify the duration of the effect.

**LED 3 - Blue** blinks when the factory reset procedure is initiated.

### Buttons

This section describes a reaction to pressing or holding buttons located on the
platform image.

**Button 1** can be used for the following purposes:

-   _Pressed for less than 3 s_ &mdash; Initiates the OTA software update
    process. This feature is disabled by default, but can be enabled by
    following the
    [Building with Device Firmware Upgrade support](#building-with-device-firmware-upgrade-support)
    instructions.

-   _Pressed for more than 3 s_ &mdash; initiates the factory reset of the
    device. Releasing the button within the 3-second window cancels the factory
    reset procedure.

**Button 2** &mdash; Pressing the button once changes the lock state to the
opposite one.

-   On ATMEVK-3425 and ATMEVK-3430e:

    -   If pressed for less than three seconds, it changes the lock state to the
        opposite one.

    -   If pressed for more than three seconds, it
        enables Bluetooth LE advertising for the predefined period of time (15
        minutes by default), and makes the device discoverable over Bluetooth
        LE.

**SEGGER J-Link USB port** can be used to get logs from the device or
communicate with it using the
[command line interface](../../../docs/guides/nrfconnect_examples_cli.md).

<hr>

## Setting up the environment

FIXME

Now you can proceed with the [Building](#building) instruction.

<hr>

## Building

Complete the following steps, regardless of the method used for setting up the
environment:

1.  Navigate to the example's directory:

        $ cd examples/lock-app/atmosic

2.  Run the following command to build the example, with _build-target_ replaced
    with the build target name of the Atmosic Technologies' kit you own, for
    example `ATMEVK-3430e-WQN-2`:

         $ west build -b build-target

    You only need to specify the build target on the first build. See
    [Requirements](#requirements) for the build target names of compatible kits.

The output `zephyr.hex` file will be available in the `build/zephyr/` directory.

### Removing build artifacts

If you're planning to build the example for a different kit or make changes to
the configuration, remove all build artifacts before building. To do so, use the
following command:

    $ rm -r build

### Building with release configuration

To build the example with release configuration that disables the diagnostic
features like logs and command-line interface, run the following command:

    $ west build -b build-target -- -DCONF_FILE=prj_release.conf

Remember to replace _build-target_ with the build target name of the Atmosic
Technologies' kit you own.

<hr>

## Configuring the example

The Zephyr ecosystem is based on Kconfig files and the settings can be modified
using the menuconfig utility.

To open the menuconfig utility, run the following command from the example
directory:

    $ west build -b build-target -t menuconfig

Remember to replace _build-target_ with the build target name of the Atmosic
Technologies' kit you own.

Changes done with menuconfig will be lost if the `build` directory is deleted.
To make them persistent, save the configuration options in the `prj.conf` file.

### Example build types

The example uses different configuration files depending on the supported
features. Configuration files are provided for different build types and they
are located in the application root directory.

The `prj.conf` file represents a debug build type. Other build types are covered
by dedicated files with the build type added as a suffix to the prj part, as per
the following list. For example, the release build type file name is
`prj_release.conf`. If a board has other configuration files, for example
associated with partition layout or child image configuration, these follow the
same pattern.

Before you start testing the application, you can select one of the build types
supported by the sample. This sample supports the following build types,
depending on the selected board:

-   debug -- Debug version of the application - can be used to enable additional
    features for verifying the application behavior, such as logs or
    command-line shell.
-   release -- Release version of the application - can be used to enable only
    the necessary application functionalities to optimize its performance.

For more information, see the
[Configuring nRF Connect SDK examples](../../../docs/guides/nrfconnect_examples_configuration.md)
page.

<hr>

## Flashing and debugging

To flash the application to the device, use the west tool and run the following
command from the example directory:

        $ west flash --erase

If you have multiple development kits connected, west will prompt you to pick
the correct one.

To debug the application on target, run the following command from the example
directory:

        $ west debug

<hr>

## Testing the example

Check the [CLI tutorial](../../../docs/guides/nrfconnect_examples_cli.md) to
learn how to use command-line interface of the application.

### Testing using Linux CHIPTool

Read the [CHIP Tool user guide](../../../docs/guides/chip_tool_guide.md) to see
how to use [CHIP Tool for Linux or mac OS](../../chip-tool/README.md) to
commission and control the application within a Matter-enabled Thread or Wi-Fi
network.

### Testing using Android CHIPTool

Read the
[Android commissioning guide](../../../docs/guides/nrfconnect_android_commissioning.md)
to see how to use [CHIPTool](../../../examples/android/CHIPTool/README.md) for
Android smartphones to commission and control the application within a
Matter-enabled Thread or Wi-Fi network.
