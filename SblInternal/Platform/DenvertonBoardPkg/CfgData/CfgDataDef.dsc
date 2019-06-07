[PcdsDynamicVpd.Tmp]

  # !BSF DEFT:{CFGHDR_TMPL:START}
    gCfgData.CfgHeader   |      * | 0x04 | {0x01:2b, ((_LENGTH_$(1)_+8)/4):10b, $(2):4b, $(3):4b, _TAG_$(1)_:12b}
    gCfgData.CondValue   |      * | 0x04 | 0x00000000
  # !BSF DEFT:{CFGHDR_TMPL:END}


[PcdsDynamicVpd.Upd]
  #
  # This section is not used by the normal build process
  # However, FSP will use dedicated tool to handle it and generate a
  # VPD similar binary block (User Configuration Data). This block will
  # be accessed through a generated data structure directly rather than
  # PCD services. This is for size consideration.
  # Format:
  #   gCfgData.Updxxxxxxxxxxxxn      | OFFSET | LENGTH | VALUE
  # Only simple data type is supported
  #

  #
  # Comments with !BSF will be used to generate BSF file
  # Comments with !HDR will be used to generate H header file
  #

  # Global definitions in BSF
  # !BSF PAGES:{PLT::"Platform", MEM::"Memory Settings", SIL::"Silicon Settings", GIO::"GPIO Settings"}
  # !BSF BLOCK:{NAME:"QEMU Platform", VER:"0.1"}

  # CFG HDR Format
	#   UINT32  ConditionNum   :  2;      // [1:0]   #of condition dwords present
	#   UINT32  Length         : 10;      // [11:2]  total size of item (in dwords)
	#   UINT32  Flags          :  4;      // [15:12] unused/reserved so far
	#   UINT32  Version        :  4;      // [19:16] item (payload) format version
	#   UINT32  Tag            : 12;      // [31:20] identifies item (in payload)

  # !BSF FIND:{CFGD}
  gCfgData.Signature              | 0x0000 | 0x04 | {'CFGD'}
  gCfgData.HeaderLength           |      * | 0x01 | 0x10
  gCfgData.Reserved               |      * | 0x03 | {0,0,0}
  gCfgData.UsedLength             |      * | 0x04 | _LENGTH_
  gCfgData.TotalLength            |      * | 0x04 | 0x1000

  # ---------------------------------------------------------------------------------------
  !include Platform/CommonBoardPkg/CfgData/CfgData_Platform.dsc


  # !BSF SUBT:{CFGHDR_TMPL:PLATFORM_CFG_DATA:0:0}
  # !HDR EMBED:{PLATFORM_CFG_DATA:TAG_280:START}
  # !BSF NAME:{Payload ID}
  # !BSF TYPE:{EditNum, HEX, (0x00000000,0xFFFFFFFF)}
  # !BSF HELP:{Specify payload ID}
  gCfgData.PayloadId             |      * | 0x04 | 0x52444C4C

  # !HDR EMBED:{PLATFORM_CFG_DATA:TAG_280:END}
  gCfgData.Reserved              |      * | 0x00 | 0x0000

  # ---------------------------------------------------------------------------------------
  # !BSF PAGE:{MEM}

  # !BSF SUBT:{CFGHDR_TMPL:MEMORY_CFG_DATA:0:0}
  # !HDR EMBED:{MEMORY_CFG_DATA:TAG_180:START}
  # !BSF NAME:{Memory Test 1}
  # !BSF TYPE:{EditNum, HEX, (0x00000000,0xFFFFFFFF)}
  # !BSF HELP:{Memory Test 1}
  gCfgData.MemTest1               |      * | 0x04 | 0x11223344

  # !HDR EMBED:{MEMORY_CFG_DATA:TAG_180:END}
  # !BSF NAME:{Memory Test 9}
  # !BSF TYPE:{EditNum, HEX, (0x00000000,0xFFFFFFFF)}
  # !BSF HELP:{Memory Test 9}
  gCfgData.MemTest2               |      * | 0x04 | 0x11223346


  # ---------------------------------------------------------------------------------------
  # !BSF PAGE:{SIL}

  # !BSF SUBT:{CFGHDR_TMPL:SILICON_CFG_DATA:0:0}
  # !HDR EMBED:{SILICON_CFG_DATA:TAG_200:START}
  # !BSF NAME:{Silicon Test 1}
  # !BSF TYPE:{EditNum, HEX, (0x00000000,0xFFFFFFFF)}
  # !BSF HELP:{Silicon Test 1}
  gCfgData.SiliconTest1           |      * | 0x04 | 0x11223347

  # !HDR EMBED:{SILICON_CFG_DATA:TAG_200:END}
  # !BSF NAME:{Silicon Test 9}
  # !BSF TYPE:{EditNum, HEX, (0x00000000,0xFFFFFFFF)}
  # !BSF HELP:{Silicon Test 9}
  gCfgData.SiliconTest2           |      * | 0x04 | 0x11223348


  # ---------------------------------------------------------------------------------------
  # !BSF PAGE:{GEN}
  # ---------------------------------------------------------------------------------------
  !include Platform/CommonBoardPkg/CfgData/CfgData_Common.dsc

