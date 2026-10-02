#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../malloc.h"

#define N 10000

void test_alignment()
{
	for (int i = 1; i < 1000; i++)
	{
		void* p = malloc(i);

		if ((uintptr_t)p % 16 != 0)
		{
			printf("❌ ALIGN FAIL size=%d ptr=%p\n", i, p);
			exit(1);
		}

		free(p);
	}
	printf("✅ alignment OK\n");
}

void test_basic()
{
	void* a = malloc(100);
	void* b = malloc(200);
	void* c = malloc(300);

	free(b);
	free(a);
	free(c);

	printf("✅ basic free OK\n");
}

void test_split()
{
	void* a = malloc(1000);
	free(a);

	void* b = malloc(100);
	void* c = malloc(100);

	if (b == c)
	{
		printf("❌ split FAIL (same pointer)\n");
		exit(1);
	}

	free(b);
	free(c);

	printf("✅ split OK\n");
}

void test_coalesce()
{
	void* a = malloc(50);
	void* b = malloc(10);
	void* c = malloc(10);

	free(b);
	free(a);
	// free(c);

	void* d = malloc(20);


	if (d != a)
	{
		printf("❌ coalesce FAIL\n");
		exit(1);
	}

	free(d);
	free(c);

	printf("✅ coalesce OK\n");
}

void test_reuse()
{
	void* a = malloc(100);
	free(a);

	void* b = malloc(100);

	if (a != b)
	{
		printf("⚠️ reuse not optimal (not critical)\n");
	}
	else
	{
		printf("✅ reuse OK\n");
	}

	free(b);
}

void test_edges()
{
	void* a = malloc(1);
	void* b = malloc(1);
	void* c = malloc(1);

	free(a); // first
	free(c); // last
	free(b); // middle

	printf("✅ edge cases OK\n");
}

void test_stress()
{
	void* ptrs[N];

	for (int i = 0; i < N; i++)
	{
		size_t size = rand() % 512 + 1;
		ptrs[i] = malloc(size);

		if (!ptrs[i])
		{
			printf("❌ malloc failed at %d\n", i);
			exit(1);
		}

		// touch memory
		((char*)ptrs[i])[0] = 42;
	}

	for (int i = 0; i < N; i++)
	{
		free(ptrs[i]);
	}

	printf("✅ stress OK\n");
}

void test_fragmentation()
{
	void* a = malloc(100);
	void* b = malloc(200);
	void* c = malloc(300);

	free(b);

	void* d = malloc(150); // должен влезть в b

	if (!d)
	{
		printf("❌ fragmentation FAIL\n");
		exit(1);
	}

	free(a);
	free(c);
	free(d);

	printf("✅ fragmentation OK\n");
}

void test_big() {
	void* a = malloc(300*1024*1024);
	void* b = malloc(200*1024*1024);
	free(a);
	void* c = malloc(100*1024*1024);


	if (a != c)
	{
		printf("❌ big FAIL ");
		printf("Comment: there is checked the situation when zones are saved when, but I'm doing mman fore each large allocation and delete zone if it was freed.\n");
		exit(1);
	}

	free(b);
	free(c);

	printf("✅ big OK\n");
}

int main()
{
//	printf("==== MALLOC TEST START ====\n");

	test_alignment();
	test_basic();
	test_split();
	test_coalesce();
	test_reuse();
	test_edges();
	test_fragmentation();
	test_stress();
	test_big();

	printf("==== ALL TESTS PASSED ====\n");

	return 0;
}
