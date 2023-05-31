// 43 GFLOPS, 49~50 ms (?)

#pragma GCC target("avx2,fma")
#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
#include <x86intrin.h>
using namespace std;

const int n=1024;
#define n_pad_a (1024 + 32)
#define n_pad_b (1024 + 64)

static inline void memcpy_1024(double *dst, const double *src) {
	__asm__ volatile (
		"movq %0, %%r15\n"  // src
		"movq %1, %%r14\n"  // dst
		"movq $32, %%r13\n"
		: :
		"r"(src), "r"(dst)
		:
	);
	
	__asm__ volatile (
		".align 8\n"
		"1:\n"
		"vmovapd 0(%r15), %ymm0\n"
		"vmovapd 32(%r15), %ymm1\n"
		"vmovapd 64(%r15), %ymm2\n"
		"vmovapd 96(%r15), %ymm3\n"
		"vmovapd 128(%r15), %ymm4\n"
		"vmovapd 160(%r15), %ymm5\n"
		"vmovapd 192(%r15), %ymm6\n"
		"vmovapd 224(%r15), %ymm7\n"
		"addq $256, %r15\n"
		"vmovapd %ymm0, 0(%r14)\n"
		"vmovapd %ymm1, 32(%r14)\n"
		"vmovapd %ymm2, 64(%r14)\n"
		"vmovapd %ymm3, 96(%r14)\n"
		"vmovapd %ymm4, 128(%r14)\n"
		"vmovapd %ymm5, 160(%r14)\n"
		"vmovapd %ymm6, 192(%r14)\n"
		"vmovapd %ymm7, 224(%r14)\n"
		"addq $256, %r14\n"
		"decq %r13\n"
		"jne 1b\n"
	);
	
	__asm__ volatile ("" : : :
		"%r15","%r14","%r13",
		"%ymm0","%ymm1","%ymm2","%ymm3",
		"%ymm4","%ymm5","%ymm6","%ymm7"
	);
}

static inline void init_arr_a(const double *src, double *dst) {
	for (int i = 0; i < n; i++) {
		memcpy_1024(dst + i * n_pad_a, src + i * n);
	}
}

static inline void init_arr_b(const double *src, double *dst) {
	for (int i = 0; i < n; i++) {
		memcpy_1024(dst + i * n_pad_b, src + i * n);
	}
}

static inline void kernel_256_32_64(const double *A, const double *B, double *C,
	int i_start, int k_start, int j_start) {
	int i_end = i_start + 256;
	int k_end = k_start + 32;
	int j_end = j_start + 64;
	
	// 4 * 32 * 64
	for (int j_block_id = 0; j_block_id < 1; j_block_id++, j_start += 64) {
		
		for (int i = i_start; i < i_end; i += 4) {
			const double *ai = A + i * n_pad_a;
			
			for (int _j = 0, j = j_start; _j < 8; _j++, j += 8) {
				
				__asm__ volatile (
					"movq %0, %%r15\n"  // cij
					"movq %1, %%r14\n"  // bk_s
					"movq %2, %%r13\n"  // a0_addr
					"movq $15, %%r12\n"
					: :
					"r"(C + i * n + j),
					"r"(B + k_start * n_pad_b + j),
					"r"(ai + k_start)
					:
				);
				
				__asm__ volatile (
					"vmovapd (%r15), %ymm0\n"  // c00
					"vmovapd 32(%r15), %ymm1\n"  // c01
					"vmovapd 8192(%r15), %ymm2\n"  // c10
					"vmovapd 8224(%r15), %ymm3\n"  // c11
					"vmovapd 16384(%r15), %ymm4\n"  // c20
					"vmovapd 16416(%r15), %ymm5\n"  // c21
					"vmovapd 24576(%r15), %ymm6\n"  // c30
					"vmovapd 24608(%r15), %ymm7\n"  // c31
				);
				
				__asm__ volatile (
					"vmovapd (%r14), %ymm14\n"  // b0
					"vmovapd 32(%r14), %ymm15\n"  // b1
					"vbroadcastsd (%r13), %ymm10\n"  // a0
					"vbroadcastsd 8448(%r13), %ymm11\n"  // a1
					"vbroadcastsd 16896(%r13), %ymm12\n"  // a2
					"vbroadcastsd 25344(%r13), %ymm13\n"  // a3
					
					".align 8\n"
					"1:\n"
					"vmovapd 8704(%r14), %ymm8\n"  // next b0
					"vmovapd 8736(%r14), %ymm9\n"  // next b1
					"vfmadd231pd %ymm10, %ymm14, %ymm0\n"  // c00 += a0 * b0
					"vfmadd231pd %ymm10, %ymm15, %ymm1\n"  // c01 += a0 * b1
					"vbroadcastsd 8(%r13), %ymm10\n"  // a0
					"vfmadd231pd %ymm11, %ymm14, %ymm2\n"  // c10 += a1 * b0
					"vfmadd231pd %ymm11, %ymm15, %ymm3\n"  // c11 += a1 * b1
					"vbroadcastsd 8456(%r13), %ymm11\n"  // a1
					"vfmadd231pd %ymm12, %ymm14, %ymm4\n"  // c20 += a2 * b0
					"vfmadd231pd %ymm12, %ymm15, %ymm5\n"  // c21 += a2 * b1
					"vbroadcastsd 16904(%r13), %ymm12\n"  // a2
					"vfmadd231pd %ymm13, %ymm14, %ymm6\n"  // c30 += a3 * b0
					"vfmadd231pd %ymm13, %ymm15, %ymm7\n"  // c31 += a3 * b1
					"vbroadcastsd 25352(%r13), %ymm13\n"  // a3
					
					"addq $17408, %r14\n"  // bk_s += (1024+64)*2
					"addq $16, %r13\n"  // a0_addr += 2
					"vmovapd (%r14), %ymm14\n"  // next b0
					"vmovapd 32(%r14), %ymm15\n"  // next b1
					"vfmadd231pd %ymm10, %ymm8, %ymm0\n"  // c00 += a0 * b0
					"vfmadd231pd %ymm10, %ymm9, %ymm1\n"  // c01 += a0 * b1
					"vbroadcastsd (%r13), %ymm10\n"  // a0
					"vfmadd231pd %ymm11, %ymm8, %ymm2\n"  // c10 += a1 * b0
					"vfmadd231pd %ymm11, %ymm9, %ymm3\n"  // c11 += a1 * b1
					"vbroadcastsd 8448(%r13), %ymm11\n"  // a1
					"vfmadd231pd %ymm12, %ymm8, %ymm4\n"  // c20 += a2 * b0
					"vfmadd231pd %ymm12, %ymm9, %ymm5\n"  // c21 += a2 * b1
					"vbroadcastsd 16896(%r13), %ymm12\n"  // a2
					"vfmadd231pd %ymm13, %ymm8, %ymm6\n"  // c30 += a3 * b0
					"vfmadd231pd %ymm13, %ymm9, %ymm7\n"  // c31 += a3 * b1
					"vbroadcastsd 25344(%r13), %ymm13\n"  // a3
					
					"decq %r12\n"
					"jne 1b\n"
					
					"vmovapd 8704(%r14), %ymm8\n"  // next b0
					"vmovapd 8736(%r14), %ymm9\n"  // next b1
					"vfmadd231pd %ymm10, %ymm14, %ymm0\n"  // c00 += a0 * b0
					"vfmadd231pd %ymm10, %ymm15, %ymm1\n"  // c01 += a0 * b1
					"vbroadcastsd 8(%r13), %ymm10\n"  // a0
					"vfmadd231pd %ymm11, %ymm14, %ymm2\n"  // c10 += a1 * b0
					"vfmadd231pd %ymm11, %ymm15, %ymm3\n"  // c11 += a1 * b1
					"vbroadcastsd 8456(%r13), %ymm11\n"  // a1
					"vfmadd231pd %ymm12, %ymm14, %ymm4\n"  // c20 += a2 * b0
					"vfmadd231pd %ymm12, %ymm15, %ymm5\n"  // c21 += a2 * b1
					"vbroadcastsd 16904(%r13), %ymm12\n"  // a2
					"vfmadd231pd %ymm13, %ymm14, %ymm6\n"  // c30 += a3 * b0
					"vfmadd231pd %ymm13, %ymm15, %ymm7\n"  // c31 += a3 * b1
					"vbroadcastsd 25352(%r13), %ymm13\n"  // a3
					
					"vfmadd231pd %ymm10, %ymm8, %ymm0\n"  // c00 += a0 * b0
					"vfmadd231pd %ymm10, %ymm9, %ymm1\n"  // c01 += a0 * b1
					"vfmadd231pd %ymm11, %ymm8, %ymm2\n"  // c10 += a1 * b0
					"vfmadd231pd %ymm11, %ymm9, %ymm3\n"  // c11 += a1 * b1
					"vfmadd231pd %ymm12, %ymm8, %ymm4\n"  // c20 += a2 * b0
					"vfmadd231pd %ymm12, %ymm9, %ymm5\n"  // c21 += a2 * b1
					"vfmadd231pd %ymm13, %ymm8, %ymm6\n"  // c30 += a3 * b0
					"vfmadd231pd %ymm13, %ymm9, %ymm7\n"  // c31 += a3 * b1
				);
				
				__asm__ volatile (
					"vmovapd %ymm0, (%r15)\n"  // c00
					"vmovapd %ymm1, 32(%r15)\n"  // c01
					"vmovapd %ymm2, 8192(%r15)\n"  // c10
					"vmovapd %ymm3, 8224(%r15)\n"  // c11
					"vmovapd %ymm4, 16384(%r15)\n"  // c20
					"vmovapd %ymm5, 16416(%r15)\n"  // c21
					"vmovapd %ymm6, 24576(%r15)\n"  // c30
					"vmovapd %ymm7, 24608(%r15)\n"  // c31
				);
				
				__asm__ volatile ("" : : :
					"%r15","%r14","%r13","%r12",
					"%ymm0","%ymm1","%ymm2","%ymm3",
					"%ymm4","%ymm5","%ymm6","%ymm7",
					"%ymm8","%ymm9","%ymm10","%ymm11",
					"%ymm12","%ymm13","%ymm14","%ymm15"
				);
			}
		}
	}
}

void matrix_multiply(int n, const double *_A, const double *_B, double *C) {
	const int i_step = 256;
	const int k_step = 32;
	const int j_step = 64;  // 16 * 4
	
	static double A[1024 * n_pad_a];
	static double B[1024 * n_pad_b];
	init_arr_a(_A, A);
	init_arr_b(_B, B);
	
	memset(C, 0, n * n * sizeof(double));
	
	for (int i_start = 0; i_start < n; i_start += i_step) {
		for (int k_start = 0; k_start < n; k_start += k_step) {
			for (int j_start = 0; j_start < n; j_start += j_step) {
				kernel_256_32_64(A, B, C, i_start, k_start, j_start);
			}
		}
	}
}

double a[n*n],b[n*n],c[n*n];
int main(){
	for (int i = 0; i < n * n; i++) {
        a[i] = 1.*rand() / RAND_MAX;
        b[i] = 1.*rand() / RAND_MAX;
    }
    int t1=clock();
    for (int i=0;i<125;++i)
	matrix_multiply(n,a,b,c);
    printf("time=%d\n",clock()-t1);
    return 0;
}
