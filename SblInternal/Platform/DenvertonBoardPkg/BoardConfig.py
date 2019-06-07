## @file
# This file is used to provide board specific image information.
#
#  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#

##
# Import Modules
#
import os
import sys

sys.dont_write_bytecode = True
sys.path.append (os.path.join('..', '..'))
from BuildLoader import BaseBoard, STITCH_OPS, FLASH_REGION_TYPE

class Board(BaseBoard):
	def __init__(self, *args, **kwargs):

		super(Board, self).__init__(*args, **kwargs)

		self.VERINFO_IMAGE_ID     = 'SB_HCUV '
		self.VERINFO_MAJOR_VER    = 0
		self.VERINFO_MINOR_VER    = 1
		self.VERINFO_SVN          = 1
		self.VERINFO_BUILD_DATE   = '05/20/2017'

		self.BOARD_NAME           = 'dnv'
		self.BOARD_PKG_NAME       = 'DenvertonBoardPkg'
		self.SILICON_PKG_NAME     = 'DenvertonPkg'

		self.PCI_IO_BASE          = 0x00002000
		self.PCI_MEM32_BASE       = 0x80000000
		self.ACPI_PM_TIMER_BASE   = 0x1808

		self.FLASH_BASE_ADDRESS   = 0xFF000000
		self.FLASH_BASE_SIZE      = (self.FLASH_LAYOUT_START - self.FLASH_BASE_ADDRESS)

		self.HAVE_FIT_TABLE       = 1
		self.FIT_ENTRY_MAX_NUM    = 4

		self.ENABLE_CRYPTO_SHA_NI = 1

		self.STAGE1A_SIZE         = 0x00008000
		self.STAGE1B_SIZE         = 0x00052000
		self.STAGE2_SIZE          = 0x00028000

		FREE_TEMP_RAM_TOP         = 0xFF000000 - self.STAGE1B_SIZE

		self.STAGE1B_XIP          = 0
		self.STAGE1B_FD_SIZE      = 0x00098000
		self.STAGE1B_FD_BASE      = FREE_TEMP_RAM_TOP - self.STAGE1B_FD_SIZE
		self.STAGE1B_LOAD_BASE    = FREE_TEMP_RAM_TOP

		self.HAVE_VERIFIED_BOOT   = 1
		self.HAVE_MEASURED_BOOT   = 0

		# For Stage2, it is always compressed.
		# if STAGE2_LOAD_HIGH is 1, STAGE2_FD_BASE will be ignored
		self.STAGE2_FD_BASE       = 0x01000000
		self.STAGE2_FD_SIZE       = 0x00030000

		self.STAGE1_STACK_SIZE    = 0x00002000
		self.STAGE1_DATA_SIZE     = 0x00006000

		self.PAYLOAD_EXE_BASE     = 0x00800000
		self.PAYLOAD_SIZE         = 0x000E0000
		self.UCODE_SIZE           = 0x00008000
		self.MRCDATA_SIZE         = 0x00010000

		self.PLD_HEAP_SIZE        = 0x00400000

		self.SLIMBOOTLOADER_SIZE  = 0x380000

		self.SPI_IAS_REGION_TYPE = FLASH_REGION_TYPE.BIOS

		self.SPI_IAS1_SIZE        = 0x200000

		# OS_PK | FWU_PK | CFG_PK | FWU_PLD | PLD | Stage2 | Stage1B
		# Stage1B is verified by ACM
		self.VERIFIED_BOOT_HASH_MASK  = 0x00000056
		if self.ENABLE_FWU:
			self.VERIFIED_BOOT_HASH_MASK  |= 0x00000028

		self.CFGDATA_SIZE         = 0x00002000
		self.CFG_DATABASE_SIZE    = self.CFGDATA_SIZE
		self._CFGDATA_INT_FILE    = ['CfgDataInt_Brd0.dlt']
		self._CFGDATA_EXT_FILE    = ['CfgDataExt_Brd1.dlt']

	def GetDscLibrarys (self):
		dsc_libs = {}
		# These libraries will be added into the DSC files
		dsc_libs['IA32'] = [
			'LoaderLib|Platform/CommonBoardPkg/Library/LoaderLib/LoaderLib.inf',
			'SerialPortLib|Silicon/$(SILICON_PKG_NAME)/Library/SerialPortLib/SerialPortLib.inf',
			'PlatformHookLib|Silicon/$(SILICON_PKG_NAME)/Library/PlatformHookLib/PlatformHookLib.inf',
			'GpioLib|Silicon/$(SILICON_PKG_NAME)/Library/GpioLib/GpioLib.inf',
			'SpiFlashLib|Silicon/$(SILICON_PKG_NAME)/Library/SpiFlashLib/SpiFlashLib.inf'
		]
		return dsc_libs

	def GetImageLayout (self):
		ias1_flag = 0 if self.SPI_IAS1_SIZE > 0 else STITCH_OPS.MODE_FILE_IGNOR
		img_list = [
				('SlimBootloader.bin', [
          ('SPI_IAS1.bin',    ''        , self.SPI_IAS1_SIZE,  STITCH_OPS.MODE_FILE_PAD | ias1_flag, STITCH_OPS.MODE_POS_TAIL),
					('PAYLOAD.bin',  'Lz4', self.PAYLOAD_SIZE,   STITCH_OPS.MODE_FILE_PAD, STITCH_OPS.MODE_POS_TAIL),
					('MRCDATA.bin',   '',    self.MRCDATA_SIZE,   STITCH_OPS.MODE_FILE_NOP, STITCH_OPS.MODE_POS_TAIL),
					('UCODE.bin',    '',     self.UCODE_SIZE, STITCH_OPS.MODE_FILE_PAD, STITCH_OPS.MODE_POS_TAIL),
					('STAGE2.fd',    'Lz4', self.STAGE2_SIZE,      STITCH_OPS.MODE_FILE_PAD, STITCH_OPS.MODE_POS_TAIL),
					('STAGE1B.fd',   'Lz4',  self.STAGE1B_SIZE,  STITCH_OPS.MODE_FILE_PAD, STITCH_OPS.MODE_POS_TAIL),
					('STAGE1A.fd',   '',    self.STAGE1A_SIZE,  STITCH_OPS.MODE_FILE_NOP, STITCH_OPS.MODE_POS_TAIL)]
			  )
			]
		return img_list


