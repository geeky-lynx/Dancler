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
    4. Test for edge cases pls
*/

#include "../header.h"
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



bool gerstr_find_substring(const GermanString *self, const char *substring, uint16_t *foundAt) {
    if (self == nullptr || substring == nullptr)
        return false;

    uint16_t index = 0;
    uint16_t charactersLeft = self->length;
    const unsigned char *iter = self->content;
    const unsigned char *tmp = (const unsigned char*)substring;

    if (self->length > GERMAN_STRING_MAX_SHORT)
        goto search_through_long_string_;

    // Short string
    while (*tmp) {
        if (charactersLeft--)
            return false;

        if (*iter == *tmp)
            tmp++;

        else {
            index = iter - self->content + 1;
            tmp = (const unsigned char*)substring;
        }

        iter++;
    }

    *foundAt = index;
    return true;


    // Long string
    search_through_long_string_:

    while (*tmp && iter >= self->content + GERMAN_STRING_PREFIX_SIZE) {
        if (charactersLeft--)
            return false;

        if (*iter == *tmp)
            tmp++;

        else {
            index = iter - self->prefix + 1;
            tmp = (const unsigned char*)substring;
        }

        iter++;
    }

    iter = self->rest;

    while (*tmp) {
        if (charactersLeft--)
            return false;

        if (*iter == *tmp)
            tmp++;

        else {
            index = iter - self->rest + 1 + GERMAN_STRING_PREFIX_SIZE;
            tmp = (const unsigned char*)substring;
        }

        iter++;
    }

    *foundAt = index;
    return true;
}



int gerstr_compare_with_cstring(const GermanString *self, const char *src) {
    if (self == nullptr || src == nullptr)
        return -1;

    const char *iterLeft = (const char*)self->content;
    const char *iterRight = src;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        while (*iterLeft && *iterRight) {
            if (*iterLeft != *iterRight)
                return *iterLeft - *iterRight;
            iterLeft++;
            iterRight++;
        }
        return *iterLeft - *iterRight;
    }

    int prefixCharsLeft = GERMAN_STRING_PREFIX_SIZE;
    while (*iterLeft && *iterRight && prefixCharsLeft--) {
        if (*iterLeft != *iterRight)
            return *iterLeft - *iterRight;
        iterLeft++;
        iterRight++;
    }

    iterLeft = (const char*)self->rest;
    while (*iterLeft && *iterRight && prefixCharsLeft--) {
        if (*iterLeft != *iterRight)
            return *iterLeft - *iterRight;
        iterLeft++;
        iterRight++;
    }

    return *iterLeft - *iterRight;
}



int gerstr_compare_with_gerstring(const GermanString *self, const GermanString *src) {
    if (self->length != src->length)
        return -1;

    uint16_t index = 0;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        while (index < self->length) {
            if (self->content[index] != src->content[index])
                return self->content[index] - src->content[index];
            index++;
        }
        return 0;
    }

    // Long string
    while (index < GERMAN_STRING_MAX_SHORT) {
        if (self->prefix[index] != src->prefix[index])
            return self->prefix[index] - src->prefix[index];
        index++;
    }

    index = 0;
    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;
    while (index < REST_LENGTH) {
        if (self->rest[index] != src->rest[index])
            return self->rest[index] - src->rest[index];
        index++;
    }

    return 0;
}



bool gerstr_to_lowercase(GermanString *self) {
    if (self == nullptr)
        return false;

    uint16_t index = 0;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        while (index < self->length) {
            unsigned char tmp = self->content[index];
            self->content[index++] |= ' ' * ('A' <= tmp && tmp <= 'Z');
        }

        return true;
    }

    // Long string
    while (index < GERMAN_STRING_PREFIX_SIZE) {
        unsigned char tmp = self->prefix[index];
        self->prefix[index++] |= ' ' * ('A' <= tmp && tmp <= 'Z');
    }

    index = 0;
    while (index < self->length - GERMAN_STRING_PREFIX_SIZE) {
        unsigned char tmp = self->rest[index];
        self->rest[index++] |= ' ' * ('A' <= tmp && tmp <= 'Z');
    }

    return true;
}



bool gerstr_to_uppercase(GermanString *self) {
    if (self == nullptr)
        return false;

    uint16_t index = 0;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        while (index < self->length) {
            unsigned char tmp = self->content[index];
            self->content[index++] &= ~(' ' * ('a' <= tmp && tmp <= 'z'));
        }

        return true;
    }

    // Long string
    while (index < GERMAN_STRING_PREFIX_SIZE) {
        unsigned char tmp = self->prefix[index];
        self->prefix[index++] &= ~(' ' * ('a' <= tmp && tmp <= 'z'));
    }

    index = 0;
    while (index < self->length - GERMAN_STRING_PREFIX_SIZE) {
        unsigned char tmp = self->rest[index];
        self->rest[index++] &= ~(' ' * ('a' <= tmp && tmp <= 'z'));
    }

    return true;
}



int gerstr_copy_from_cstring(GermanString *self, const char *src) {
    if (self == nullptr || src == nullptr)
        return -1;

    if (self->length > GERMAN_STRING_MAX_SHORT)
        free(self->rest);

    *self = gerstr_init_from_cstring(src);

    if (self->length == 0)
        return -1;

    return 0;
}



int gerstr_copy_from_gerstring(GermanString *self, const GermanString *src) {
    if (self == nullptr || src == nullptr)
        return -1;

    if (self->length > GERMAN_STRING_MAX_SHORT)
        free(self->rest);

    *self = gerstr_init_from_gerstring(src);

    if (self->length == 0)
        return -1;

    return 0;
}



int gerstr_concatenate_cstring(GermanString *self, const char *src) {
    if (self == nullptr || src == nullptr)
        return -1;

    const uint16_t SRC_LENGTH = cstring_get_length(src);
    const uint16_t NEW_LENGTH = self->length + SRC_LENGTH;

    // Short string
    if (NEW_LENGTH <= GERMAN_STRING_MAX_SHORT) {
        uint16_t index = self->length;
        while (index < NEW_LENGTH)
            self->content[index++] = *src++;
        self->length = NEW_LENGTH;
        return 0;
    }

    // Long string, used to be short
    if (self->length <= GERMAN_STRING_PREFIX_SIZE) {
        unsigned char temporary[sizeof(void*)] = {0};
        uint16_t tmpLength = 0;
        uint16_t index = GERMAN_STRING_PREFIX_SIZE;
        while (index < self->length)
            temporary[tmpLength++] = self->content[index++];

        unsigned char *allocated = (unsigned char*)malloc(tmpLength + SRC_LENGTH);
        if (allocated == nullptr)
            return -1;

        self->rest = allocated;

        index = 0;
        while (index < tmpLength)
            *allocated++ = temporary[index++];

        while (index < NEW_LENGTH)
            *allocated++ = *src++;

        return 0;
    }

    // Long string, still long string
    unsigned char *reallocated = (unsigned char*)realloc(
        self->rest,
        NEW_LENGTH - GERMAN_STRING_PREFIX_SIZE
    );

    if (reallocated == nullptr)
        return -1;

    self->rest = reallocated;
    uint16_t charsAt = self->length;
    while (charsAt++ < NEW_LENGTH)
        *reallocated++ = *src++;

    return 0;
}



int gerstr_concatenate_gerstring(GermanString *self, const GermanString *src) {
    if (self == nullptr || src == nullptr)
        return -1;

    const uint16_t NEW_LENGTH = self->length + src->length;

    // Short string
    if (NEW_LENGTH <= GERMAN_STRING_MAX_SHORT) {
        uint16_t srcIndex = 0;
        while (self->length <= NEW_LENGTH)
            self->content[self->length++] = src->content[srcIndex++];
        self->length = NEW_LENGTH;
        return 0;
    }

    // Long string, still long string
    if (self->length < GERMAN_STRING_MAX_SHORT) {
        unsigned char *reallocated = realloc(
            self->rest,
            NEW_LENGTH - GERMAN_STRING_PREFIX_SIZE
        );

        if (reallocated == nullptr)
            return -1;

        self->rest = reallocated;

        // `src` is a short string
        if (src->length <= GERMAN_STRING_MAX_SHORT) {
            uint16_t charsAt = self->length;
            uint16_t srcIndex = 0;
            while (srcIndex < src->length)
                self->rest[charsAt++] = src->content[srcIndex++];
            self->length = NEW_LENGTH;
            return 0;
        }

        // `src` is a long string
        uint16_t charsAt = self->length;
        uint16_t srcIndex = 0;
        while (srcIndex < GERMAN_STRING_PREFIX_SIZE)
            self->rest[charsAt++] = src->prefix[srcIndex++];

        srcIndex = 0;
        while (srcIndex < src->length - GERMAN_STRING_PREFIX_SIZE)
            self->rest[charsAt++] = src->content[srcIndex++];

        self->length = NEW_LENGTH;
        return 0;
    }

    // Long string, used to be short
    unsigned char temporary[sizeof(void*)] = {0};
    uint16_t tmpLength = 0;
    uint16_t index = GERMAN_STRING_PREFIX_SIZE;
    while (index < self->length)
        temporary[tmpLength++] = self->content[index++];

    unsigned char *allocated = (unsigned char*)malloc(tmpLength + src->length);
    if (allocated == nullptr)
        return -1;

    self->rest = allocated;

    index = 0;
    while (index < tmpLength) {
        self->rest[index] = temporary[index];
        index++;
    }

    if (src->length <= GERMAN_STRING_MAX_SHORT) {
        uint16_t srcIndex = 0;
        while (srcIndex < src->length)
            self->rest[index++] = src->content[srcIndex++];

        self->length = NEW_LENGTH;
        return 0;
    }

    uint16_t srcIndex = 0;
    while (srcIndex < GERMAN_STRING_PREFIX_SIZE)
        self->rest[index++] = src->prefix[srcIndex++];

    srcIndex = 0;
    while (srcIndex < src->length - GERMAN_STRING_PREFIX_SIZE)
        self->rest[index++] = src->rest[srcIndex++];

    self->length = NEW_LENGTH;
    return 0;


    return 0;
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
