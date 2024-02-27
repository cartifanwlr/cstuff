/*
 * 86Box    A hypervisor and IBM PC system emulator that specializes in
 *          running old operating systems and software designed for IBM
 *          PC systems and compatibles from 1981 through fairly recent
 *          system designs based on the PCI bus.
 *
 *          This file is part of the 86Box distribution.
 *
 *          Emulation of the Novell Advanced NetWare 286 2.0a SFT II key card.
 *          
 *          Based on documentation by Michal Necasek.
 *
 *
 * Authors: cfwlr,
 *
 *          Copyright 2024 cfwlr.
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#define HAVE_STDARG_H
#include <86box/86box.h>
#include <86box/io.h>
#include <86box/device.h>
#include <86box/plat_unused.h>
#include <86box/other.h>

/*  The serial number for Michal Necasek's copy of SFT Netware 2.0 is 000651771131. 
    The number itself is encoded in BCD format and must be bitflipped when read. The first 8 digits (4 bytes)
    are the serial proper and is stored in registers 23Ch through 23Fh. The last 4 digits (2 bytes) are the 
    application number and is stored in registers 23Ah and 23Bh. The way the serial is stored is scrambled likely
    for technical reasons.

    Here it is implemented like the actual card, returning fixed values no matter what. */
static uint8_t
netware_key_read(uint16_t addr, void *priv)
{
    uint8_t val = 0x00;

    switch (addr)
    {
        /* Application number. */
        case (0x023a):
            val = 0x31; /* Bit 5 high, bit 4 high */
            break;
        
        case (0x023b):
            val = 0x11; /* Bit 5 low, bit 4 low */
            break;
        
        /* Serial number. */
        case (0x023c):
            val = 0x16; /* Bit 2 low, bit 1 low */
            break;
        
        case (0x023d):
            val = 0x07; /* Bit 0 high, bit 3 low */
            break;
        
        case (0x023e):
            val = 0x07; /* Bit 0 low, bit 3 high */
            break;

        case (0x023f):
            val = 0x05; /* Bit 1 high, bit 2 high */
            break;
    }

    return (val ^ 0xff);
}

static void
netware_key_close(void *priv)
{
    uint8_t *dev = (uint8_t *) priv;

    io_removehandler(0x023a, 0x0006, netware_key_read, NULL, NULL, NULL, NULL, NULL, NULL);

    free(dev);
}

static void *
netware_key_init(UNUSED(const device_t *info))
{   
    /* The device is so simple, we don't need a specific type. */
    uint8_t *dev = (uint8_t *) calloc(1, sizeof(uint8_t));

    io_sethandler(0x023a, 0x0006, netware_key_read, NULL, NULL, NULL, NULL, NULL, NULL);

    return dev;
}

const device_t netware_key_device = {
    .name          = "Novell Advanced NetWare 286 2.0a SFT II Key Card",
    .internal_name = "netware_key",
    .flags         = DEVICE_ISA,
    .local         = 0,
    .init          = netware_key_init,
    .close         = netware_key_close,
    .reset         = NULL,
    { .available = NULL },
    .speed_changed = NULL,
    .force_redraw  = NULL,
    .config        = NULL
};