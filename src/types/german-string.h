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
        };
    };
};

typedef struct GermanString GermanString;



GermanString gerstr_init_empty(void);

GermanString gerstr_init_from_cstring(const char *restrict src);

GermanString gerstr_init_from_gerstring(const GermanString *restrict src);



int gerstr_to_cstring(const GermanString *self, char **dest);

int gerstr_to_cstring_buffered(const GermanString *self, char *dest);



bool gerstr_is_lowercase(const GermanString *self);

bool gerstr_is_upperacse(const GermanString *self);

bool gerstr_is_alphabetic(const GermanString *self);

bool gerstr_is_numeric(const GermanString *self);

bool gerstr_is_hexadecimal(const GermanString *self);

bool gerstr_is_alphanumeric(const GermanString *self);



uint32_t gerstr_find_substring(const GermanString *self, const char *substring);

int gerstr_compare_with_cstring(const GermanString *self, const char *src);

int gerstr_compare_with_gerstring(const GermanString *self, const GermanString *src);



int gerstr_to_lowercase(GermanString *self);

int gerstr_to_uppercase(GermanString *self);



int gerstr_copy_from_cstring(GermanString *self, const char *src);

int gerstr_copy_from_gerstring(GermanString *self, const GermanString *src);

int gerstr_concatenate_cstring(GermanString *self, const char *src);

int gerstr_concatenate_gerstring(GermanString *self, const GermanString *src);

#endif /* DANCLER_GERMAN_STRING_ */
