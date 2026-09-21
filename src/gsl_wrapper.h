#ifndef GSL_WRAPPER_H
#define GSL_WRAPPER_H

#include <gsl/gsl_linalg.h>

void print_matrix(const gsl_matrix *A);
void print_vector(const gsl_vector *v);
gsl_matrix **matrices_from_image(char *path, int channels);
void matrices_to_image(gsl_matrix **matrices, char *path, int channels);
void matrix_svc(gsl_matrix *U, gsl_vector *S, gsl_matrix *V, gsl_matrix *A); 

void save_matrix_to_file(char *path, gsl_matrix* matrix);
void save_vector_to_file(char *path, gsl_vector* vector);
gsl_matrix* load_matrix_from_file(char *path);
gsl_vector* load_vector_from_file(char *path);

#endif // GSL_WRAPPER_H
