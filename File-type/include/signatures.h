#ifndef SIGNATURES_H_
#define SIGNATURES_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
    char *name;
    uint8_t *sig;
    size_t len;
} sig_t;

size_t sig_table_len();

// extern const sig_t zip_sig;
// extern const sig_t zip_empty_sig;
// extern const sig_t zip_spanned_sig;

extern const sig_t sig_table[];
extern const sig_t NULL_SIG;

#endif
