#include "libmx.h"
#include "string.h"
#include "assert.h"

char *mx_replace_substr(const char *s1, const char *s2, const char *s3)
{
    if (!s1 || !s2 || !s3)
        return 0;
    size_t s1_len = strlen(s1);
    if (!s1_len)
        return (char *)s1;
    size_t s2_len = strlen(s2);
    if (!s2_len)
        return (char *)s1;
    /*
     * Two-pass approach: figure out how much space to allocate for
     * the new string, pre-allocate it, then perform replacement(s).
     */
    size_t count = 0;
    const char *p = s1;
    assert(s2_len); /* otherwise, strstr(s1,s2) will return s1. */
    do {
        p = strstr(p, s2);
        if (p) {
            p += s2_len;
            ++count;
        }
    } while (p);
    if (!count)
        return (char *)s1;
    assert(s1_len >= count * s2_len);
    assert(count);
    size_t s1_without_s2_len = s1_len - count * s2_len;
    size_t s3_len = strlen(s3);
    size_t s1_with_s3_len = s1_without_s2_len + count * s3_len;
    if (s3_len &&
        ((s1_with_s3_len <= s1_without_s2_len) || (s1_with_s3_len + 1 == 0)))
        /* Overflow. */
        return 0;
    
    char *s1_with_s3 = (char *)malloc(s1_with_s3_len + 1); /* w/ terminator */
    if (!s1_with_s3)
        /* ENOMEM, but no good way to signal it. */
        return 0;
    
    char *dst = s1_with_s3;
    const char *start_substr = s1;
    size_t i;
    for (i = 0; i != count; ++i) {
        const char *end_substr = strstr(start_substr, s2);
        assert(end_substr);
        size_t substr_len = end_substr - start_substr;
        memcpy(dst, start_substr, substr_len);
        dst += substr_len;
        memcpy(dst, s3, s3_len);
        dst += s3_len;
        start_substr = end_substr + s2_len;
    }
    /* copy remainder of s1, including trailing '\0' */
    size_t remains = s1_len - (start_substr - s1) + 1;
    assert(dst + remains == s1_with_s3 + s1_with_s3_len + 1);
    memcpy(dst, start_substr, remains);
    assert(strlen(s1_with_s3) == s1_with_s3_len);
    return s1_with_s3;
}
