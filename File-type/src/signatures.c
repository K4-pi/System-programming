#include "signatures.h"
#include <stdint.h>

static const uint8_t zip_magic[] = {0x50, 0x4B, 0x03, 0x04};
static const uint8_t zip_empty_magic[] = {0x50, 0x4B, 0x05, 0x06};
static const uint8_t zip_spanned_magic[] = {0x50, 0x4B, 0x07, 0x08};

const sig_t zip_sig = {
    .name = "Zip",
    .sig = zip_magic,
    .len = sizeof(zip_magic)
};

const sig_t zip_empty_sig = {
    .name = "Zip - empty",
    .sig = zip_empty_magic,
    .len = sizeof(zip_empty_magic)
};

const sig_t zip_spanned_sig = {
    .name = "Zip - spanned",
    .sig = zip_spanned_magic,
    .len = sizeof(zip_spanned_magic)
};
