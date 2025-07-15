/*  Warning: Not C89-compatible!
    This header is for this project only,
    not made for reuse in other projects
    If you want to use this somewhere
    outside of this repo, you'll have to
    modify both definitions & implementations.
    It's written in C23 standard
*/

/*  Note: This German String is modified
    from the original to be more suitable
    for this project's use case
*/

#ifndef DANCLER_GERMAN_STRING_
#define DANCLER_GERMAN_STRING_ 1

#include <stdint.h>



#define GERMAN_STRING_MAX_SHORT 14
#define GERMAN_STRING_PREFIX_SIZE (GERMAN_STRING_MAX_SHORT - sizeof(void*))



struct GermanString {
    /* 32-bit padding, 128-bit size */
    uint16_t length;
    union {
        unsigned char content[GERMAN_STRING_MAX_SHORT];
        struct {
            unsigned char prefix[GERMAN_STRING_PREFIX_SIZE];
            unsigned char *rest;
        } __attribute__((packed));
    };
} __attribute__((packed));

typedef struct GermanString GermanString;



GermanString gerstr_init_empty(void);

GermanString gerstr_init_from_cstring(const char src[static restrict 1]);

GermanString gerstr_init_from_gerstring(const GermanString src[static restrict 1]);

bool gerstr_uninit(GermanString self[static restrict 1]);

bool gerstr_uninit_zero(GermanString self[static restrict 1]);



bool gerstr_to_cstring(const GermanString self[static restrict 1], char *dest[static restrict self->length]);

bool gerstr_to_cstring_buffered(const GermanString self[static restrict 1], char dest[static restrict self->length]);



bool gerstr_is_lowercase(const GermanString self[static restrict 1]);

bool gerstr_is_upperacse(const GermanString self[static restrict 1]);

bool gerstr_is_alphabetic(const GermanString self[static restrict 1]);

bool gerstr_is_numeric(const GermanString self[static restrict 1]);

bool gerstr_is_hexadecimal(const GermanString self[static restrict 1]);

bool gerstr_is_alphanumeric(const GermanString self[static restrict 1]);



bool gerstr_find_substring(const GermanString self[static restrict 1], const char substring[static restrict 1], uint16_t foundAt[static restrict 1]);

int gerstr_compare_with_cstring(const GermanString self[static restrict 1], const char src[static restrict 1]);

int gerstr_compare_with_gerstring(const GermanString self[static restrict 1], const GermanString src[static restrict 1]);



bool gerstr_to_lowercase(GermanString self[static restrict 1]);

bool gerstr_to_uppercase(GermanString self[static restrict 1]);



bool gerstr_copy_from_cstring(GermanString self[static restrict 1], const char src[static restrict 1]);

bool gerstr_copy_from_gerstring(GermanString self[static restrict 1], const GermanString src[static restrict 1]);

bool gerstr_concatenate_cstring(GermanString self[static restrict 1], const char src[static restrict 1]);

bool gerstr_concatenate_gerstring(GermanString self[static restrict 1], const GermanString src[static restrict 1]);

#endif /* DANCLER_GERMAN_STRING_ */
