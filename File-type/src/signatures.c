#include "signatures.h"
#include <stddef.h>
#include <stdint.h>

static uint8_t zip_magic[] = {0x50, 0x4B, 0x03, 0x04};
static uint8_t zip_empty_magic[] = {0x50, 0x4B, 0x05, 0x06};
static uint8_t zip_spanned_magic[] = {0x50, 0x4B, 0x07, 0x08};

static uint8_t rar_v1_magic[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00};
static uint8_t rar_v5_magic[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x01, 0x00};

const sig_t sig_table[] = {
    // .ZIP
    {
        .name = "Zip",
        .sig = zip_magic,
        .len = sizeof(zip_magic)
    },
    {
        .name = "Zip - empty",
        .sig = zip_empty_magic,
        .len = sizeof(zip_empty_magic)
    },
    {
        .name = "Zip - spanned",
        .sig = zip_spanned_magic,
        .len = sizeof(zip_spanned_magic)
    },
    // .RAR
    {
        .name = "rar v1.50 onwards",
        .sig = rar_v1_magic,
        .len = sizeof(rar_v1_magic)
    },
    {
        .name = "rar v5.00 onwards",
        .sig = rar_v5_magic,
        .len = sizeof(rar_v5_magic)
    }
};

const sig_t NULL_SIG = {
    .name = NULL,
    .sig = 0,
    .len = 0
};

size_t sig_table_len() {
    return sizeof(sig_table)/sizeof(sig_t);
}