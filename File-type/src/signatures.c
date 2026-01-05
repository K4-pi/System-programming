#include "signatures.h"
#include <stddef.h>
#include <stdint.h>

static uint8_t zip_magic[] = {0x50, 0x4B, 0x03, 0x04};
static uint8_t zip_empty_magic[] = {0x50, 0x4B, 0x05, 0x06};
static uint8_t zip_spanned_magic[] = {0x50, 0x4B, 0x07, 0x08};
static uint8_t rar_v1_magic[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00};
static uint8_t rar_v5_magic[] = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x01, 0x00};
static uint8_t gz_magic[] = {0x1F, 0x8B};
static uint8_t xz_magic[] = {0xFD, 0x37, 0x7A, 0x58, 0x5A, 0x00};
static uint8_t tar_magic[] = {0x75, 0x73, 0x74, 0x61, 0x72, 0x00, 0x30, 0x30};
static uint8_t elf_magic[] = {0x7F, 0x45, 0x4C, 0x46};
static uint8_t png_magic[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
static uint8_t pdf_magic[] = {0x25, 0x50, 0x44, 0x46, 0x2D};
static uint8_t mz_magic[] = {0x4D, 0x5A};

const sig_t sig_table[] = {
    {
        .name = "PDF",
        .sig = pdf_magic,
        .len = sizeof(pdf_magic)
    },
    {
        .name = "Mz (exe/dll)",
        .sig = mz_magic,
        sizeof(mz_magic)
    },
    {
        .name = "Tar",
        .sig = tar_magic,
        .len = sizeof(tar_magic)
    },
    {
        .name = "Xz",
        .sig = xz_magic,
        .len = sizeof(xz_magic)
    },
    {
        .name = "Gz",
        .sig = gz_magic,
        .len = sizeof(gz_magic)
    },
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
    {
        .name = "rar v1.50 onwards",
        .sig = rar_v1_magic,
        .len = sizeof(rar_v1_magic)
    },
    {
        .name = "rar v5.00 onwards",
        .sig = rar_v5_magic,
        .len = sizeof(rar_v5_magic)
    },
    {
        .name = "Elf",
        .sig = elf_magic,
        .len = sizeof(elf_magic)
    },
    {
        .name = "PNG",
        .sig = png_magic,
        .len = sizeof(png_magic)
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