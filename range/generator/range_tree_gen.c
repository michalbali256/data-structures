#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX (1000*1000*1000)
#define TEST_COUNT (10*1000)
#define MAX_SIZE (100*1000)
#define DIM 2

#define SWAP(T, a, b) do { \
    T *_a = &(a); \
    T *_b = &(b); \
    T _tmp = *_a; \
    *_a = *_b; \
    *_b = _tmp; \
  } while (0)

/*
 * This is the xoroshiro128+ random generator, designed in 2016 by David Blackman
 * and Sebastiano Vigna, distributed under the CC-0 license. For more details,
 * see http://vigna.di.unimi.it/xorshift/.
 */
static uint64_t rng_state[2];

static uint64_t rng_rotl(const uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

static uint64_t rng_next_u64(void)
{
	uint64_t s0 = rng_state[0], s1 = rng_state[1];
	uint64_t result = s0 + s1;
	s1 ^= s0;
	rng_state[0] = rng_rotl(s0, 55) ^ s1 ^ (s1 << 14);
	rng_state[1] = rng_rotl(s1, 36);
	return result;
}

static uint32_t rng_next_u32(void)
{
	return rng_next_u64() >> 11;
}

static void rng_setup(unsigned int seed)
{
	rng_state[0] = seed * 0xdeadbeef;
	rng_state[1] = seed ^ 0xc0de1234;
	for (int i=0; i<100; i++)
		rng_next_u64();
}

/*** The RNG ends here ***/


void query(void) {
  printf("C");
  int a[DIM];
  int b[DIM];
  int i = DIM;

  while (i-- > 0) {
    a[i] = rng_next_u32() % MAX;
    b[i] = rng_next_u32() % MAX;
    if (a[i] > b[i]) { int c = a[i]; a[i] = b[i]; b[i] = c; }
  }

  for (i = DIM; i-- > 0;) printf(" %d", a[i]);
  for (i = DIM; i-- > 0;) printf(" %d", b[i]);
  printf("\n");
}


void insert_uniform(int unused_1, int unused_2) {
  printf("I");
  for (int i = DIM; i-- > 0; ) printf(" %d", rng_next_u32() % MAX);
  printf("\n");
}

void insert_sequential(int i, int s) {
  printf("I");
  for (int j = 0; j < DIM; j++) printf(" %d", i * (MAX / s));
  printf("\n");
}


void usage(const char *prog) {
  fprintf(stderr, "Usage %s SEED TEST\n\nTEST is one of:\n"
    "  -s Sequential test\n"
    "  -u Uniform test\n", prog
  );
  exit(1);
}

int main(int argc, char** argv) {
  int opt, seed = -1, seq_test = 0, rand_test = 0;

  for (int i = 1; i < argc; ++i)
  {
	  if (!strcmp(argv[i], "-s"))
		  seed = atoi(argv[++i]);
	  else if (!strcmp(argv[i], "-q"))
		  seq_test = 1;
	  else if (!strcmp(argv[i], "-u"))
		  rand_test = 1;
	  else
		  usage(argv[0]);
	  
  }

  if (seq_test == rand_test) usage(argv[0]);

  char *ops = malloc(MAX_SIZE / 2 + TEST_COUNT / 2);

  rng_setup(seed);
  void (*insert)(int, int) = seq_test ? insert_sequential : insert_uniform;

  for (int s = 100; s < MAX_SIZE; s *= 1.2) {
    int i = 0, j = 0;
    printf("# %d\n", s);

    int ops_size = s / 2 + TEST_COUNT / 2;
    memset(ops, 0, s / 2);
    memset(ops + s / 2, 1, TEST_COUNT / 2);
    for (int k = s / 2; k < ops_size; k++)
      SWAP(char, ops[k], ops[rng_next_u32() % (k + 1)]);

    while (i < (s + 1) / 2) insert(i++, s);
    for (int k = 0; k < ops_size; k++) {
      if (ops[k]) query();
      else insert(i++, s);
    }

    for (int j = TEST_COUNT / 2; j < TEST_COUNT; j++) query();
  }

  free(ops);

  return 0;
}

