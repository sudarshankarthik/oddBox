#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


static uint64_t state[4];

static inline uint64_t rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}


// xoshiro256ss PRNG to generate random numbers
uint64_t get_next_u64(void)
{
    const uint64_t result = rotl(state[1] * 5, 7) * 9;

    const uint64_t t = state[1] << 17;

    state[2] ^= state[0];
    state[3] ^= state[1];
    state[1] ^= state[2];
    state[0] ^= state[3];

    state[2] ^= t;
    state[3] = rotl(state[3], 45);

    return result;
}

uint64_t splitmix64(uint64_t *x)
{
    uint64_t z = (*x += 0x9E3779B97F4A7C15ULL);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
    return z ^ (z >> 31);
}

void init_rng(void)
{
    uint64_t seed =
        (uint64_t)time(NULL) ^
        (uint64_t)clock() ^
        (uintptr_t)&state ^
        0x9E3779B97F4A7C15ULL;

    // Initialize state[]
    for (int i = 0; i < 4; i++)
        state[i] = splitmix64(&seed);

    // Make sure state is non-zero
    if ((state[0] | state[1] | state[2] | state[3]) == 0)
        state[0] = 1;
}

void fill_u64_buff(uint64_t* buffer, size_t buff_len)
{
    for (size_t i = 0; i < buff_len; ++i) 
    {
        buffer[i] = get_next_u64();
    }
}

