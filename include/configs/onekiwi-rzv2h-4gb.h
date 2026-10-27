/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2022 Renesas Electronics Corporation
 * Copyright (C) 2025 OneKiwi Technology Co., Ltd
 */

#ifndef __ONEKIWI_RZV2H_4GB_H
#define __ONEKIWI_RZV2H_4GB_H

#include <asm/arch/rmobile.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
/* RZ/V2H use GIC-v3 */
#define CONFIG_GICV3
#define GICD_BASE	0x14900000
#define GICR_BASE	0x14940000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

/* SDHI clock freq */
#define CONFIG_SH_SDHI_FREQ			133000000

#define DRAM_RSV_SIZE				0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(0x80000000u - DRAM_RSV_SIZE) // Bank 0: 2GB (minus 128MB TF-A)
#define CONFIG_SYS_LOAD_ADDR		0x58000000
#define CONFIG_LOADADDR				CONFIG_SYS_LOAD_ADDR // Default load address for tfpt,bootp...
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(0x80000000u - DRAM_RSV_SIZE)

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

#define CONFIG_SYS_MEMTEST_START	0x60000000
#define CONFIG_SYS_MEMTEST_END		0xB8000000

//#define CONFIG_SYS_DRAM_TEST
/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		1048576

/* ENV setting */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"usb_pgood_delay=2000\0" \
	"bootm_size=0x10000000\0" \
	"ocaaddr=0x80000000 \0" \
	"ocabin=OpenCV_Bin.bin \0" \
	"codaddr=0x87D00000 \0" \
	"codbin=Codec_Bin.bin \0" \
	"prodemmcbootargs=setenv bootargs rw rootwait earlycon console=ttySC0,115200 cgroup_disable=memory root=/dev/mmcblk0p2 \0" \
	"prodsd0bootargs=setenv bootargs rw rootwait earlycon console=ttySC0,115200 cgroup_disable=memory root=/dev/mmcblk0p2 \0" \
	"prodsd1bootargs=setenv bootargs rw rootwait earlycon console=ttySC0,115200 cgroup_disable=memory root=/dev/mmcblk1p2 \0" \
	"produsbbootargs=setenv bootargs rw rootwait earlycon console=ttySC0,115200 cgroup_disable=memory root=/dev/sda2 \0" \
	"bootimage=booti 0x48080000 - 0x48000000 \0" \
	"emmcload0=ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run prodemmcbootargs \0" \
	"sd0load0=ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run prodsd0bootargs \0" \
	"sd1load0=ext4load mmc 1:2 0x48080000 boot/Image;ext4load mmc 1:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run prodsd1bootargs \0" \
	"sd1load=ext4load mmc 1:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 1:2 ${codaddr} boot/${codbin}; ext4load mmc 1:2 0x48080000 boot/Image;ext4load mmc 1:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run prodsd1bootargs \0" \
	"emmcload=ext4load mmc 0:2 ${ocaaddr} boot/${ocabin}; ext4load mmc 0:2 ${codaddr} boot/${codbin}; ext4load mmc 0:2 0x48080000 boot/Image;ext4load mmc 0:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run prodemmcbootargs \0" \
	"usbload=ext4load usb 0:2 ${ocaaddr} boot/${ocabin}; ext4load usb 0:2 ${codaddr} boot/${codbin}; ext4load usb 0:2 0x48080000 boot/Image;ext4load usb 0:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run produsbbootargs \0" \
	"bootusb=usb start; run usbload; run bootimage \0" \
	"usbload0=ext4load usb 0:2 0x48080000 boot/Image;ext4load usb 0:2 0x48000000 boot/onekiwi-rzv2h-4gb.dtb;run produsbbootargs \0" \
	"bootcmd_check=if mmc dev 1; then run sd1load; else run emmcload; fi \0"

#define CONFIG_BOOTCOMMAND	"run bootcmd_check;run bootimage"

/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI

#endif /* __ONEKIWI_RZV2H_4GB_H */
