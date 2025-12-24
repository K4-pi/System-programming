#ifndef SIGNATURES_H_
#define SIGNATURES_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
    const char *name;
    const uint8_t *sig;
    size_t len;
} sig_t;

extern const sig_t zip_sig;
extern const sig_t zip_empty_sig;
extern const sig_t zip_spanned_sig;

#endif
