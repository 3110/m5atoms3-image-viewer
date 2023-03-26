[日本語版](README_ja_JP.md)

# Image Viewer for ATOMS3

This program is an image viewer for [ATOMS3](https://shop.m5stack.com/products/atoms3-dev-kit-w-0-85-inch-screen?variant=43676991258881) to display images on [SPIFFS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/storage/spiffs.html). There are two modes: "Manual mode," where images are displayed each time a button is pressed, and "Automatic mode," where images are displayed at regular intervals.

You can compile this program on the [PlatformIO IDE](https://platformio.org/platformio-ide) environment.

## How to transfer the image files

The capacity of SPIFFS is 7 MiB allocated with the partition table `no_ota_8MB.csv` in this repository.

Place the 128 x 128 image files(PNG, JPEG, or BMP) to be displayed in the `data` directory.

You can transfer your image files in the `data` directory by selecting "Upload from the PlatformIO menu or invoking the command `pio run --target uploadfs`.

## Config file

If you transfer the following configuration file `data/image-viewer.json` to SPIFFS with your image files, you can specify whether the automatic mode is on or off and the interval of switching image files in the automatic mode. If there is no configuration file, the automatic mode(`AutoMode`) is off(`false`), and the interval(`AutoModeInterval`) is 3000 milliseconds by default.

```json
{
  "AutoMode": false,
  "AutoModeInterval": 3000
}
```

## How to use this program

When ATOMS3 is started, the image files on SPIFFS are displayed in order. The orientation of the screen changes automatically according to the orientation of ATOMS3.

There are two ways to display images:

1. Manual mode  
   Switch images every time you push the button on ATOMS3.
2. Automatic mode  
   Switch images at regular intervals.

The default mode is the mode you specify in the configuration file. If you boot ATOMS3 while holding down the button, it will be forced to the automatic mode instead of your configuration.

After booting ATOMS3, the following will appear on the screen. If there is no configuration file, the information on `Config:` will not appear.

```text
Image Viewer v0.0.2
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
Mode:
 Manual, Auto or Auto(Forced)
Image Files:
 ImageFile1
 ImageFile2
 ...
 ImageFileN
```

There are no image files on SPIFFS, the following will appear:

```text
Image Viewer v0.0.2
Config:
 /image-viewer.json
 AutoMode: false
 Interval: 3000ms
Mode:
 Manual, Auto or Auto(Forced)
No image files found
```

The list of image files above is displayed for a time(the default is 3 seconds), and the image files on SPIFFS are displayed according to the display mode.
