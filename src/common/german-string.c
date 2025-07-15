/* TODO:
    - Test for edge cases pls
*/

#include "../header.h"
#include "./german-string.h"

static inline uint16_t cstring_get_length(const char src[static restrict 1]);

static inline bool copy_short_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]);
static inline bool copy_long_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]);
static inline bool copy_from_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]);



GermanString gerstr_init_empty(void) {
    return (GermanString){0};
}



GermanString gerstr_init_from_cstring(const char src[static restrict 1]) {
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    GermanString newString = {0};
    uint32_t srcLength = cstring_get_length(src);
    int result = copy_from_cstring(&newString, srcLength, src);

    DEBUG_ASSERT_(result == true, "String hasn\'t been properly initialized");

    return newString;
}



GermanString gerstr_init_from_gerstring(const GermanString src[static restrict 1]) {
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    GermanString newString = { .length = src->length };
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



bool gerstr_uninit(GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

    if (self->length > GERMAN_STRING_MAX_SHORT)
        free(self->rest); // Free heap-allocated space for long strings

    self->length = 0;

    return true;
}



bool gerstr_uninit_zero(GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

    uint16_t index = 0;
    if (self->length > GERMAN_STRING_MAX_SHORT) {
        while (index < self->length - GERMAN_STRING_PREFIX_SIZE)
            self->rest[index++] = '\0';
        free(self->rest); // Free heap-allocated space for long strings
    }

    index = 0;
    while (index <= GERMAN_STRING_MAX_SHORT)
        self->content[index++] = '\0';

    self->length = 0;

    return true;
}



bool gerstr_to_cstring(const GermanString self[static restrict 1], char *dest[static restrict self->length]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(dest != nullptr, "Passed parameter `dest` is NULL; expected a non-NULL");

    char *allocated = malloc(sizeof(unsigned char) * self->length);
    if (allocated == nullptr)
        return false;

    *dest = allocated;

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++)
            *allocated++ = self->content[index];
        *allocated = '\0';
        return true;
    }

    // Long string
    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;

    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++)
        *allocated++ = self->prefix[index];

    for (uint16_t index = 0; index < REST_LENGTH; index++)
        *allocated++ = self->rest[index];

    *allocated = '\0';

    return true;
}



bool gerstr_to_cstring_buffered(const GermanString self[static restrict 1], char dest[static restrict self->length]) {
    // Assume the user has allocated enough memory
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(dest != nullptr, "Passed parameter `dest` is NULL; expected a non-NULL");

    // Short string
    if (self->length <= GERMAN_STRING_MAX_SHORT) {
        for (uint16_t index = 0; index < self->length; index++)
            *dest++ = self->content[index];
        *dest = '\0';
        return true;
    }

    // Long string
    const uint16_t REST_LENGTH = self->length - GERMAN_STRING_PREFIX_SIZE;

    for (uint16_t index = 0; index < GERMAN_STRING_PREFIX_SIZE; index++)
        *dest++ = self->prefix[index];

    for (uint16_t index = 0; index < REST_LENGTH; index++)
        *dest++ = self->rest[index];

    *dest = '\0';

    return true;
}



bool gerstr_is_lowercase(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_is_uppercase(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_is_alphabetic(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_is_numeric(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_is_hexadecimal(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_is_alphanumeric(const GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_find_substring(const GermanString self[static restrict 1], const char substring[static restrict 1], uint16_t foundAt[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(substring != nullptr, "Passed parameter `substring` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(foundAt != nullptr, "Passed parameter `foundAt` is NULL; expected a non-NULL");

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



int gerstr_compare_with_cstring(const GermanString self[static restrict 1], const char src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

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



int gerstr_compare_with_gerstring(const GermanString self[static restrict 1], const GermanString src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

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



bool gerstr_to_lowercase(GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_to_uppercase(GermanString self[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

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



bool gerstr_copy_from_cstring(GermanString self[static restrict 1], const char src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    if (self->length > GERMAN_STRING_MAX_SHORT)
        free(self->rest);

    *self = gerstr_init_from_cstring(src);

    if (self->length == 0)
        return false;

    return true;
}



bool gerstr_copy_from_gerstring(GermanString self[static restrict 1], const GermanString src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    if (self->length > GERMAN_STRING_MAX_SHORT)
        free(self->rest);

    *self = gerstr_init_from_gerstring(src);

    if (self->length == 0)
        return false;

    return true;
}



bool gerstr_concatenate_cstring(GermanString self[static restrict 1], const char src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    const uint16_t SRC_LENGTH = cstring_get_length(src);
    const uint16_t NEW_LENGTH = self->length + SRC_LENGTH;

    // Short string
    if (NEW_LENGTH <= GERMAN_STRING_MAX_SHORT) {
        uint16_t index = self->length;
        while (index < NEW_LENGTH)
            self->content[index++] = *src++;
        self->length = NEW_LENGTH;
        return true;
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
            return false;

        self->rest = allocated;

        index = 0;
        while (index < tmpLength)
            *allocated++ = temporary[index++];

        while (index < NEW_LENGTH)
            *allocated++ = *src++;

        return true;
    }

    // Long string, still long string
    unsigned char *reallocated = (unsigned char*)realloc(
        self->rest,
        NEW_LENGTH - GERMAN_STRING_PREFIX_SIZE
    );

    if (reallocated == nullptr)
        return false;

    self->rest = reallocated;
    uint16_t charsAt = self->length;
    while (charsAt++ < NEW_LENGTH)
        *reallocated++ = *src++;

    return true;
}



bool gerstr_concatenate_gerstring(GermanString self[static restrict 1], const GermanString src[static restrict 1]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    const uint16_t NEW_LENGTH = self->length + src->length;

    // Short string
    if (NEW_LENGTH <= GERMAN_STRING_MAX_SHORT) {
        uint16_t srcIndex = 0;
        while (self->length <= NEW_LENGTH)
            self->content[self->length++] = src->content[srcIndex++];
        self->length = NEW_LENGTH;
        return true;
    }

    // Long string, still long string
    if (self->length < GERMAN_STRING_MAX_SHORT) {
        unsigned char *reallocated = realloc(
            self->rest,
            NEW_LENGTH - GERMAN_STRING_PREFIX_SIZE
        );

        if (reallocated == nullptr)
            return false;

        self->rest = reallocated;

        // `src` is a short string
        if (src->length <= GERMAN_STRING_MAX_SHORT) {
            uint16_t charsAt = self->length;
            uint16_t srcIndex = 0;
            while (srcIndex < src->length)
                self->rest[charsAt++] = src->content[srcIndex++];
            self->length = NEW_LENGTH;
            return true;
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
        return true;
    }

    // Long string, used to be short
    unsigned char temporary[sizeof(void*)] = {0};
    uint16_t tmpLength = 0;
    uint16_t index = GERMAN_STRING_PREFIX_SIZE;
    while (index < self->length)
        temporary[tmpLength++] = self->content[index++];

    unsigned char *allocated = (unsigned char*)malloc(tmpLength + src->length);
    if (allocated == nullptr)
        return false;

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
        return true;
    }

    uint16_t srcIndex = 0;
    while (srcIndex < GERMAN_STRING_PREFIX_SIZE)
        self->rest[index++] = src->prefix[srcIndex++];

    srcIndex = 0;
    while (srcIndex < src->length - GERMAN_STRING_PREFIX_SIZE)
        self->rest[index++] = src->rest[srcIndex++];

    self->length = NEW_LENGTH;
    return true;
}



/* Helper functions */

static inline uint16_t cstring_get_length(const char src[static restrict 1]) {
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");
    uint16_t count = 0;
    while (*src++)
        ++count;
    return count;
}



static inline bool copy_short_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

    uint16_t index = 0;

    if (length > GERMAN_STRING_MAX_SHORT)
        return false;

    while (index < length)
        self->content[index++] = *src++;

    return true;
}



static inline bool copy_long_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `src` is NULL; expected a non-NULL");

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



static inline bool copy_from_cstring(GermanString self[static restrict 1], uint16_t length, const char src[static restrict length]) {
    DEBUG_ASSERT_(self != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");
    DEBUG_ASSERT_(src != nullptr, "Passed parameter `self` is NULL; expected a non-NULL");

    if (length <= GERMAN_STRING_MAX_SHORT)
        return copy_short_cstring(self, length, src);
    return copy_long_cstring(self, length, src);
}
