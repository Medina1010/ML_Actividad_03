#include <stdlib.h>
#include <gsl/gsl_linalg.h>


void print_matrix(const gsl_matrix* A, size_t m, size_t n) {
	for(size_t j = 0; j < n; j++) {
		for(size_t i = 0; i < m; i++) {
			printf("%f\t", gsl_matrix_get(A, i, j));
		}
		printf("\n");
	}
}

void print_vector(const gsl_vector* v, size_t m) {
		for(size_t i = 0; i < m; i++) {
			printf("%f\t", gsl_vector_get(v, i));
		}
		printf("\n");
}

int main (void) {
	const size_t M = 3, N = 2;
	gsl_vector* work = gsl_vector_alloc(N);
	gsl_matrix* A = gsl_matrix_alloc(M, N);
	gsl_matrix_set(A, 0, 0, 1);
	gsl_matrix_set(A, 0, 1, 0);
	gsl_matrix_set(A, 1, 0, 1);
	gsl_matrix_set(A, 1, 1, 1);
	gsl_matrix_set(A, 2, 1, 3);
	printf("A\n");
	print_matrix(A, M, N);
	gsl_matrix* V = gsl_matrix_alloc(N, N);
	gsl_vector* S = gsl_vector_alloc(N);

	gsl_linalg_SV_decomp(
			A,
			V,
			S,
			work);

	printf("U\n");
	print_matrix(A, M, N);
	printf("diag S\n");
	print_vector(S, N);
	printf("V\n");
	print_matrix(V, N, N);
	gsl_vector_free(work);
	gsl_matrix_free(A);
	gsl_matrix_free(V);
	gsl_vector_free(S);
	return 0;
}
