#include "gsl_wrapper.h"
#include "image_wrapper.h"

void save_matrix_to_file(char *path, gsl_matrix* matrix) {
	FILE* f = fopen(path, "w");
	fprintf(f, "%zu\n", matrix->size1);
	fprintf(f, "%zu\n", matrix->size2);
	for (int j = 0; j < matrix->size2; j++)
	for (int i = 0; i < matrix->size2; i++)
		fprintf(f, "%f\n", gsl_matrix_get(matrix, i, j));
	fclose(f);
}

void save_vector_to_file(char *path, gsl_vector* vector) {
	FILE* f = fopen(path, "w");
	fprintf(f, "%zu\n", vector->size);
	for (int i = 0; i < vector->size; i++)
		fprintf(f, "%f\n", gsl_vector_get(vector, i));
	fclose(f);
}

gsl_matrix* load_matrix_from_file(char *path) {
	FILE* f = fopen(path, "r");
	size_t size1, size2;
	fscanf(f, "%zu\n", &size1);
	fscanf(f, "%zu\n", &size2);
	gsl_matrix* matrix = gsl_matrix_alloc(size1, size2);
	float value;
	for (int j = 0; j < matrix->size2; j++)
	for (int i = 0; i < matrix->size2; i++) {
		fscanf(f, "%f\n", &value);
		gsl_matrix_set(matrix, i, j, value);
	}
	fclose(f);
	return matrix;
}

gsl_vector* load_vector_from_file(char *path) {
	FILE* f = fopen(path, "r");
	size_t size;
	fscanf(f, "%zu\n", &size);
	gsl_vector* vector = gsl_vector_alloc(size);
	float value;
	for (int i = 0; i < vector->size; i++) {
		fscanf(f, "%f\n", &value);
		gsl_vector_set(vector, i, value);
	}
	fclose(f);
	return vector;
}

gsl_matrix **matrices_from_image(char *path, int channels) {
  stbi_image image;
  stbi_load_simple(path, &image, channels);

  gsl_matrix **matrices = malloc(channels * sizeof *matrices);
  for (int i = 0; i < channels; i++)
    matrices[i] = gsl_matrix_alloc(image.width, image.height);
  for (int j = 0; j < image.height; j++)
    for (int i = 0; i < image.width; i++)
      for (int c = 0; c < channels; c++)
        gsl_matrix_set(
            matrices[c], i, j,
            (double)image.data[channels * (i + j * image.width) + c]);
  stbi_image_free(image.data);
  return matrices;
}


void matrices_to_image(gsl_matrix **matrices, char *path, int channels) {
  unsigned char image_bytes[(*matrices)->size1*(*matrices)->size2*channels];
  for (int j = 0; j < (*matrices)->size2; j++)
    for (int i = 0; i < (*matrices)->size1; i++)
      for (int c = 0; c < channels; c++)
        image_bytes[channels * (i + j * (*matrices)->size1) + c] = gsl_matrix_get(matrices[c], i, j);
  stbi_write_png(path, (*matrices)->size1, (*matrices)->size2, channels, image_bytes,
                 (*matrices)->size1 * channels);
}

void print_matrix(const gsl_matrix *A) {
  for (size_t j = 0; j < A->size2; j++) {
    for (size_t i = 0; i < A->size1; i++) {
      printf("%f\t", gsl_matrix_get(A, i, j));
    }
    printf("\n");
  }
}

void print_vector(const gsl_vector *v) {
  for (size_t i = 0; i < v->size; i++) {
    printf("%f\t", gsl_vector_get(v, i));
  }
  printf("\n");
}

void matrix_svc(gsl_matrix *U, gsl_vector *S, gsl_matrix *V, gsl_matrix *A) { 
  for (size_t j = 0; j < A->size2; j++) {
    for (size_t i = 0; i < A->size1; i++) {
      double value = 0;
      for (size_t k = 0; k < A->size2; k++) {
	value +=
        gsl_matrix_get(U, i, k)*
        gsl_vector_get(S, k)*
        gsl_matrix_get(V, j, k);
	if(gsl_vector_get(S, k) == 0) k=A->size2;
      }
      gsl_matrix_set(A, i, j, value);
    }
  }
}
