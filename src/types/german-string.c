/* TODO:
    1. Implement:
        - gerstr_find_substring,
        - gerstr_compare_with_cstring,
        - gerstr_compare_with_gerstring,
        - gerstr_to_lowercase,
        - gerstr_to_uppercase,
        - gerstr_copy_from_cstring
        - gerstr_copy_from_gerstring,
        - gerstr_concatenate_cstring,
        - gerstr_concatenate_gerstring
    2. Change function parameter types to support non-nullable values
    3. Place debug asserts
*/

#include "../header.h"
#include <stdint.h>
#include "./german-string.h"

static inline uint16_t cstring_get_length(const char *restrict src);

static inline bool copy_short_cstring(GermanString *self, uint16_t length, const char *restrict src);
static inline bool copy_long_cstring(GermanString *self, uint16_t length, const char *restrict src);
static inline bool copy_from_cstring(GermanString *self, uint16_t length, const char *restrict src);



GermanString gerstr_init_empty(void) {
    return (GermanString){0};
}



GermanString gerstr_init_from_cstring(const char *restrict src) {
    if (src == nullptr)
        return (GermanString){0};

    GermanString newString = {0};
    uint32_t srcLength = cstring_get_length(src);
    int result = copy_from_cstring(&newString, srcLength, src);

    DEBUG_ASSERT_(result == true);

    return newString;
}



GermanString gerstr_init_from_gerstring(const GermanString *src) {
    if (src == nullptr)
        return (GermanString){0};

    GermanString newString = { .length = src->length, 0 };
    unsigned char *allocated;

    // Short string:
    if (newString.length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < newString.length; index++)
            newString.content[index] = src->content[index];
        return newString;
    }

    // Long string
    allocated = malloc(newString.length * sizeof(unsigned char));
    if (allocated == nullptr)
        return (GermanString){0};

    const uint16_t REST_LENGTH = newString.length - GERMAN_STRING_PREFIX_SIZE;

    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++)
        newString.prefix[index] = src->prefix[index];

    newString.rest = allocated;
    for (uint16_t index = 0; index < REST_LENGTH; index++)
        newString.rest[index] = src->rest[index];

    return newString;
}



int gerstr_to_cstring(const GermanString *self, char **dest) {
    if (self == nullptr)
        return -1;

    char *allocated = malloc(sizeof(unsigned char) * self->length);
    if (allocated == nullptr)
        return -2;

    *dest = allocated;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++)
            *allocated++ = self->content[index];
        *allocated = '\0';
        return 0;
    }

    // Long string
    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;

    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++)
        *allocated++ = self->prefix[index];

    for (uint16_t index = 0; index < REST_LENGTH; index++)
        *allocated++ = self->rest[index];

    *allocated = '\0';

    return 0;
}



int gerstr_to_cstring_buffered(const GermanString *self, char *dest) {
    // Assume the user has allocated enough memory
    if (self == nullptr || dest == nullptr)
        return -1;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++)
            *dest++ = self->content[index];
        *dest = '\0';
        return 0;
    }

    // Long string
    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;

    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++)
        *dest++ = self->prefix[index];

    for (uint16_t index = 0; index < REST_LENGTH; index++)
        *dest++ = self->rest[index];

    *dest = '\0';

    return 0;
}



bool gerstr_is_lowercase(const GermanString *self) {
    if (self == nullptr)
        return false;

    unsigned char tmp;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            tmp = self->content[index];
            // Found uppercase, return `false`
            if ('A' <= tmp && tmp <= 'Z')
                return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        tmp = self->prefix[index];
        if ('A' <= tmp && tmp <= 'Z')
            return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        tmp = self->rest[index];
        if ('A' <= tmp && tmp <= 'Z')
            return false;
    }

    return true;
}



bool gerstr_is_uppercase(const GermanString *self) {
    if (self == nullptr)
        return false;

    unsigned char tmp;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            tmp = self->content[index];
            // Found lowercase, return `false`
            if ('a' <= tmp && tmp <= 'z')
                return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        tmp = self->prefix[index];
        if ('a' <= tmp && tmp <= 'z')
            return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        tmp = self->rest[index];
        if ('a' <= tmp && tmp <= 'z')
            return false;
    }

    return true;
}



bool gerstr_is_alphabetic(const GermanString *self) {
    if (self == nullptr)
        return false;

    unsigned char tmp;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            tmp = self->content[index];
            if ('A' >= tmp && tmp >= 'Z')
                continue;
            if ('a' >= tmp && tmp >= 'z')
                continue;
            // Didn't found any alphabetic character, return `false`
            return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        tmp = self->prefix[index];
        if ('A' >= tmp && tmp >= 'Z')
            continue;
        if ('a' >= tmp && tmp >= 'z')
            continue;
        return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        tmp = self->rest[index];
        if ('A' >= tmp && tmp >= 'Z')
            continue;
        if ('a' >= tmp && tmp >= 'z')
            continue;
        return false;
    }

    return true;
}



bool gerstr_is_numeric(const GermanString *self) {
    if (self == nullptr)
        return false;

    unsigned char tmp;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            tmp = self->content[index];
            if ('0' >= tmp || tmp >= '9')
                return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        tmp = self->prefix[index];
        if ('0' >= tmp || tmp >= '9')
            return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        tmp = self->rest[index];
        if ('0' >= tmp || tmp >= '9')
            return false;
    }

    return true;
}



bool gerstr_is_hexadecimal(const GermanString *self) {
    if (self == nullptr)
        return false;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            unsigned char tmp = self->content[index];
            if ('0' <= tmp && tmp <= '9')
                continue;
            if ('A' <= tmp && tmp <= 'F')
                continue;
            if ('a' <= tmp && tmp <= 'f')
                continue;
            // Didn't found any hexadecimal digit, return `false`
            return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        unsigned char tmp = self->prefix[index];
        if ('0' <= tmp && tmp <= '9')
            continue;
        if ('A' <= tmp && tmp <= 'F')
            continue;
        if ('a' <= tmp && tmp <= 'f')
            continue;
        return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        unsigned char tmp = self->rest[index];
        if ('0' <= tmp && tmp <= '9')
            continue;
        if ('A' <= tmp && tmp <= 'F')
            continue;
        if ('a' <= tmp && tmp <= 'f')
            continue;
        return false;
    }

    return true;
}



bool gerstr_is_alphanumeric(const GermanString *self) {
    if (self == nullptr)
        return false;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++) {
            unsigned char tmp = self->content[index];
            if ('0' <= tmp && tmp <= '9')
                continue;
            if ('A' <= tmp && tmp <= 'Z')
                continue;
            if ('a' <= tmp && tmp <= 'z')
                continue;
            // Didn't found any hexadecimal digit, return `false`
            return false;
        }
        return true;
    }

    // Long string
    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++) {
        unsigned char tmp = self->prefix[index];
        if ('0' <= tmp && tmp <= '9')
            continue;
        if ('A' <= tmp && tmp <= 'Z')
            continue;
        if ('a' <= tmp && tmp <= 'z')
            continue;
        return false;
    }

    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    for (uint16_t index = 0; index < REST_LENGTH; index++) {
        unsigned char tmp = self->rest[index];
        if ('0' <= tmp && tmp <= '9')
            continue;
        if ('A' <= tmp && tmp <= 'Z')
            continue;
        if ('a' <= tmp && tmp <= 'z')
            continue;
        return false;
    }

    return true;
}



/* Helper functions */

static inline uint16_t cstring_get_length(const char *restrict src) {
    uint16_t count = 0;
    while (*src++)
        ++count;
    return count;
}



static inline bool copy_short_cstring(GermanString *self, uint16_t length, const char *restrict src) {
    uint16_t index = 0;

    if (self == nullptr || src == nullptr)
        return false;

    if (length > GERMAN_STRING_MAX_SHORT)
        return false;

    while (index < length)
        self->content[index++] = *src++;

    return true;
}



static inline bool copy_long_cstring(GermanString *self, uint16_t length, const char *restrict src) {
    if (self == nullptr || src == nullptr)
        return false;

    uint16_t index = 0;
    unsigned char *allocated = malloc(length * sizeof(unsigned char));

    if (allocated == nullptr)
        return false;

    while (index < GERMAN_STRING_PREFIX_SIZE)
        self->prefix[index++] = *src++;

    length -= index; // Length reduced by 6 on 64-bit systems, 10 on 32-bit systems
    index = 0;

    while (index < length)
        allocated[index++] = *src++;

    // Assume `rest` isn't initialized
    self->rest = allocated;

    return true;
}



static inline bool copy_from_cstring(GermanString *self, uint16_t length, const char *restrict src) {
    if (length <= GERMAN_STRING_MAX_SHORT)
        return copy_short_cstring(self, length, src);
    return copy_long_cstring(self, length, src);
}
