================================================================================
Intel® Slim Bootloader Release Notes for Denverton-NS SoC.

Release name: Intel® Slim Bootloader POC for DENVERTON-NS
January 2019

================================================================================

================================================================================
RELEASE NOTES CONTENTS
================================================================================
1.   OVERVIEW
2.   RELEASE INFORMATION
3.   BUILD ENVIRONMENT OPERATING SYSTEM
4.   BUILD INSTRUCTIONS
5.   FLASHING
6.   VALIDATION
7.   OS BOOT
8.   PERFORMANCE
9.   DOCUMENTATION


================================================================================
1.  OVERVIEW
================================================================================
This package is a Proof of Concept example used to demonstrate 
Intel® Slim Bootloader support for Denverton-NS SoC based platform.


================================================================================
2.  RELEASE INFORMATION
================================================================================
The open source Intel® Slim Bootloader distribution used in this release package
is taken from following location:

  Repo      : https://github.com/slimbootloader/slimbootloader
  Commit ID : 1f972af0cd96c359deec199aeef811c975fcbf55

  Note: To reduce the current package size, unrequired directories/files have been
        removed.

The Intel® FSP binaries used in this release package are from following:

  Repo      : https://github.com/IntelFsp/FSP/tree/master/DenvertonNSFspBinPkg
  Commit ID : 0a0f8cc237eb42c14d3cb6da79194f90e307cf37


================================================================================
3.  BUILD ENVIRONMENT OPERATING SYSTEM
================================================================================
- Windows 8.1/10 used for all development and testing.
- Tools
  - Visual Studio     2015
  - IASL              20160422-32
  - OpenSSL           v1.0.2
  - Nasm              2.12.02
  - Python            Python 2.7

  NOTE : Please refer to the following for more details on the Tool installation:
        https://slimbootloader.github.io/getting-started/build-host-setup.html#building-on-windows


================================================================================
4.  BUILD INSTRUCTIONS
================================================================================
  a) Unpack the Demo.7z included in release distribution into a new folder.

     This unpacks source files into a directory named Demo. Change Dir to 'Demo' (cd Demo)

  b) Build Intel® Slim Bootloader for Denverton:

      > python SblBuild.py build dnv
          (Append '-r' for release build. Default is debug build)

        This creates the final BIOS region image @: Demo\Outputs\dnv\SlimBootloader.bin.
          - This image is NOT a full IFWI image.

  c) Clean build

      > python SblBuild.py clean


================================================================================
5.  FLASHING
================================================================================

  There is no stitch tool provided with this release package. The build generates
  a SlimBootloader.bin of size 0x380000 (3.5 MiB). In order to flash a bootable image
  on your board, do

    1. Backup your original contents from SPI Flash using Flash Programmer Tool.
    2. Flash the SlimBootloader.bin to the top 3.5 MiB of the SPI Flash (i.e. replace image in the BIOS region)
        - Example : If your flash size is 16MiB, you should flash the SlimBootloader.bin at address 0xC80000.
                    

  The final image on SPI Flash should look like following:

                  ------------------------------> 0x1000000 (SPI Flash top)
                  |  SlimBootloader.bin     |
                  ------------------------------> 0x1000000 - 0x380000 ( = 0xC80000)
                  |                         |
                  |       Rest of           |
                  |         IFWI            |
                  |                         |
                  ------------------------------> 0x0000000 (SPI Flash bottom)


================================================================================
6.  VALIDATION
================================================================================
  No official validation performed on this release package as this is a POC.

  Below listed basic testing has been performed:
    - Booting to Intel® Slim Bootloader Shell
    - Loading and jumping to Linux Kernel
    - Booting to Linux Kernel Shell
  
  Following test setup was used for the above basic testing:

    - SUT (System Under Test)
      - Harcuvar (HCV) platform
      - DNV SoC (SKU : QLHJ)
        - Stepping : Bx
      - DIMM 0 Channel 0 populated - 4 GiB


================================================================================
7.  OS BOOT
================================================================================
  An 'iasimage1.bin' kernel image is provided in the release package, which gets built into
  SlimBootloader.bin and resides on SPI Flash. The OS loader, a part of the Intel® Slim Bootloader
  identifies this and jumps to this kernel by default.

  This boot behavior can be configured according to different images/boot-media etc.
  Please refer to the following documentation for more details on this feature:
    https://slimbootloader.github.io/developer-guides/boot-options.html
    https://slimbootloader.github.io/how-tos/change-boot-option.html#change-boot-options

  NOTE : 'iasimage1.bin' in this release package is the MINIMAL BUILD image generated from
          the vanila kernel available at kernel.org.


================================================================================
8.  PERFORMANCE
================================================================================
  Source code in the release package is configured for getting optimal boot performance.
  Some examples to configure for achieving better numbers:
    1. Scrub partial memory
    2. Set MTRRs to cache 16 MiB BIOS region
    3. Use Lz4 decompression
    4. Set Fast read mode for SPI


================================================================================
9.  DOCUMENTATION
================================================================================
  Please find more documentation for Intel® Slim Bootloader at the following location:
      > https://slimbootloader.github.io/