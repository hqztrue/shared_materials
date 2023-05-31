// https://duck.ac/submission/17692

#pragma GCC target("avx2,fma")
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

const int n = 1024, n_a = n + 32, n_b = n + 64;
const int n4 = n / 4, n_b4 = n_b / 4;

using vec = __attribute((vector_size(32))) double;

void matrix_multiply(int _n, const double *a, const double *b, double *C) {
	const int i_step = 256;
	const int k_step = 32;
	const int j_step = 64;
	static double A[n * n_a], B[n * n_b];
	for (int i = 0; i < n; i++) {
		memcpy(A + i * n_a, a + i * n, n << 3);
		memcpy(B + i * n_b, b + i * n, n << 3);
	}
	for (int is = 0; is < n; is += i_step)
		for (int ks = 0, ie = is + 256; ks < n; ks += k_step)
			for (int js = 0; js < n; js += j_step)
				for(int i = is, je = js + 64; i < ie; i += 4) {
					const double *ai = A + i * n_a;
					for(int j = js; j < je; j += 8) {
						auto cij = (vec*)(C + i * n + j);
						auto bks = (vec*)(B + ks * n_b + j);
						auto aiks = ai + ks;
						vec c00, c01, c10, c11, c20, c21, c30, c31;
						c00 = cij[n4 * 0], c01 = cij[n4 * 0 + 1];
						c10 = cij[n4 * 1], c11 = cij[n4 * 1 + 1];
						c20 = cij[n4 * 2], c21 = cij[n4 * 2 + 1];
						c30 = cij[n4 * 3], c31 = cij[n4 * 3 + 1];
						vec b00 = bks[0], b01 = bks[1], a0, a1, a2, a3;
						a0 = vec{} + aiks[n_a * 0];
						a1 = vec{} + aiks[n_a * 1];
						a2 = vec{} + aiks[n_a * 2];
						a3 = vec{} + aiks[n_a * 3];
						for(int k = 15; k; k--) {
							vec b10 = bks[n_b4], b11 = bks[n_b4 + 1];
							c00 += a0 * b00, c01 += a0 * b01, a0 = vec{} + aiks[n_a * 0 + 1];
							c10 += a1 * b00, c11 += a1 * b01, a1 = vec{} + aiks[n_a * 1 + 1];
							c20 += a2 * b00, c21 += a2 * b01, a2 = vec{} + aiks[n_a * 2 + 1];
							c30 += a3 * b00, c31 += a3 * b01, a3 = vec{} + aiks[n_a * 3 + 1];
							bks += n_b4 << 1, aiks += 2, b00 = bks[0], b01 = bks[1];
							c00 += a0 * b10, c01 += a0 * b11, a0 = vec{} + aiks[n_a * 0];
							c10 += a1 * b10, c11 += a1 * b11, a1 = vec{} + aiks[n_a * 1];
							c20 += a2 * b10, c21 += a2 * b11, a2 = vec{} + aiks[n_a * 2];
							c30 += a3 * b10, c31 += a3 * b11, a3 = vec{} + aiks[n_a * 3];
						}
						vec b10 = bks[n_b4], b11 = bks[n_b4 + 1];
						c00 += a0 * b00, c01 += a0 * b01, a0 = vec{} + aiks[n_a * 0 + 1];
						c10 += a1 * b00, c11 += a1 * b01, a1 = vec{} + aiks[n_a * 1 + 1];
						c20 += a2 * b00, c21 += a2 * b01, a2 = vec{} + aiks[n_a * 2 + 1];
						c30 += a3 * b00, c31 += a3 * b01, a3 = vec{} + aiks[n_a * 3 + 1];
						c00 += a0 * b10, c01 += a0 * b11;
						c10 += a1 * b10, c11 += a1 * b11;
						c20 += a2 * b10, c21 += a2 * b11;
						c30 += a3 * b10, c31 += a3 * b11;
						cij[n4 * 0] = c00, cij[n4 * 0 + 1] = c01;
						cij[n4 * 1] = c10, cij[n4 * 1 + 1] = c11;
						cij[n4 * 2] = c20, cij[n4 * 2 + 1] = c21;
						cij[n4 * 3] = c30, cij[n4 * 3 + 1] = c31;
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

