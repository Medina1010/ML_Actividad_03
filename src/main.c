#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "gsl_wrapper.h"
#include "image_wrapper.h"

#define LOG(MSG) printf("[LOG]: " MSG "\n")

void svd_svc_image(char *input_path, char *output_path, int channels);

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  //svd_svc_image("../res/Image_01.png", "../res/Image_01_feo.png", 1);
  //svd_svc_image("../res/Image_02.png", "../res/Image_02_feo.png", 1);
  //svd_svc_image("../res/Image_03.png", "../res/Image_03_feo.png", 1);
  //svd_svc_image("../res/Image_04.png", "../res/Image_04_feo.png", 1);
  //svd_svc_image("../res/Image_05.png", "../res/Image_05_feo.png", 1);
  //svd_svc_image("../res/Image_06.png", "../res/Image_06_feo.png", 1);
  int channels = 1;
  gsl_matrix **matrices = matrices_from_image("../res/Image_01.png", channels);

  save_matrix_to_file("../res/image_01_A.mat", matrices[0]);
  gsl_matrix* matrix = load_matrix_from_file("../res/image_01_A.mat");
  matrices_to_image(&matrix, "../res/image_01_baw.png", channels);
  for(int i = 0; i < channels; i++)
	  gsl_matrix_free(matrices[i]);
  gsl_matrix_free(matrix);
  return 0;
}

void svd_svc_image(char *input_path, char *output_path, int channels) {
  printf("[LOG]: Doing process for \"%s\"... ", input_path);
  gsl_matrix **matrices = matrices_from_image(input_path, channels);
  printf("DONE\n");

  gsl_vector *work = gsl_vector_alloc((*matrices)->size2);
  gsl_matrix *V[channels];
  gsl_vector *S[channels];
  for (int i = 0; i < channels; i++) {
    V[i] = gsl_matrix_alloc((*matrices)->size2, (*matrices)->size2);
    S[i] = gsl_vector_alloc((*matrices)->size2);
  }

  for (int i = 0; i < channels; i++) {
    printf("[LOG]: Doing decomposition for channel %d/%d... ", i + 1, channels);
    gsl_linalg_SV_decomp(matrices[i], V[i], S[i], work);
    printf("DONE\n");

    printf("[LOG]: removing sv's less than 5%% for channel %d/%d... ", i + 1,
           channels);
    double sv_total = 0;
    for (int j = 0; j < (*S)->size; j++)
      sv_total += gsl_vector_get(S[i], j);
    double sv_sum = 0;
    int index;
    for (int j = 0; j < (*S)->size; j++) {
      if (sv_sum > sv_total * 0.95f) {
        gsl_vector_set(S[i], j, 0);
      }
      if (gsl_vector_get(S[i], j) != 0) {
        index = j + 1;
        sv_sum += gsl_vector_get(S[i], j);
      }
    }
    printf("DONE, removed from %d to %zu\n", index, (*S)->size);

    printf("[LOG]: Doing composition of channels %d/%d... ", i + 1, channels);
    gsl_matrix *A = gsl_matrix_alloc((*matrices)->size1, (*matrices)->size2);
    matrix_svc(matrices[i], S[i], V[i], A);
    printf("DONE\n");

    gsl_matrix *aux = matrices[i];
    matrices[i] = A;
    gsl_matrix_free(aux);
  }

  printf("[LOG]: Saving the result into \"%s\"... ", output_path);
  matrices_to_image(matrices, output_path, channels);
  printf("DONE\n");

  printf("[LOG]: freeing the memory... ");
  gsl_vector_free(work);
  for (int i = 0; i < channels; i++) {
    gsl_matrix_free(matrices[i]);
    gsl_matrix_free(V[i]);
    gsl_vector_free(S[i]);
  }
  printf("DONE\n");
}
