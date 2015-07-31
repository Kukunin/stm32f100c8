# stm32f100c8 boilerplate

This is IDE-agnostic boilerplate for STM32F100C8 microcontroller. It can be adjusted to other STM32F10x controllers, or even more.

## Prerequirements

You still need to get the [STM32F10x Standard Peripherals Library](https://ru.wikipedia.org/wiki/STM32F10x_Standard_Peripherals_Library) library <sub>([download](http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stsw-stm32054.zip))</sub> in order to compile and run initialization code directly.

Make sure you updated `SPL_BASE_PATH` in Makefile to point your installation of that library.

Also, you need to have `make` and `arm-none-eabi-toolchain`. In Archlinux it took me just to type `yaourt -S gcc-arm-none-eabi-bin` into the console.

That's all.

## Compiling

Just run `make`. Also, you can use `make flash` to flash the firmware onto controller.

As always, `make clean` removes all compiled objects.

Use any comfortable editor/IDE to write your firmware code under `src/` subfolder.

Have a fun!
