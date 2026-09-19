#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "gsl_wrapper.h"
#include "image_wrapper.h"

#define LOG(MSG) printf("[LOG]: "MSG"\n")

void svd_svc_image(char* input_path, char* output_path, int channels);

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  //svd_svc_image("../res/Image_01.png", "../res/Image_01_feo.png", 1);
  //svd_svc_image("../res/Image_02.png", "../res/Image_02_feo.png", 1);
  //svd_svc_image("../res/Image_03.png", "../res/Image_03_feo.png", 1);
  //svd_svc_image("../res/Image_04.png", "../res/Image_04_feo.png", 1);
  //svd_svc_image("../res/Image_05.png", "../res/Image_05_feo.png", 1);
  svd_svc_image("../res/Image_06.png", "../res/Image_06_feo.png", 1);
  return 0;
}

void svd_svc_image(char* input_path, char* output_path, int channels) {
  printf("[LOG]: Doing process for \"%s\"... ", input_path);
  gsl_matrix **matrices = matrices_from_image(input_path, channels);
  printf("DONE\n");

  gsl_vector *work = gsl_vector_alloc((*matrices)->size2);
  gsl_matrix *V = gsl_matrix_alloc((*matrices)->size2,(*matrices)->size2);
  gsl_vector *S = gsl_vector_alloc((*matrices)->size2);

  printf("[LOG]: Doing decomposition... ");
  gsl_linalg_SV_decomp(matrices[0], V, S, work);
  printf("DONE\n");

  printf("[LOG]: removing sv's less than 5%%... ");
  double sv_total = 0;
  for(int i=0;i<S->size;i++) sv_total += gsl_vector_get(S,i);
  double sv_sum = 0;
  int index;
  for(int i=0;i<S->size;i++) {
	  if (sv_sum > sv_total * 0.95f) {
		  gsl_vector_set(S,i,0);
	  }
	  if (gsl_vector_get(S,i) != 0) {
		  index = i + 1;
		  sv_sum += gsl_vector_get(S,i);
	  }
  }
  printf("DONE, removed from %d to %zu\n", index, S->size);

  printf("[LOG]: Doing composition of the result... ");
  gsl_matrix *A = gsl_matrix_alloc((*matrices)->size1,(*matrices)->size2);
  matrix_svc(matrices[0], S, V, A); 
  printf("DONE\n");

  gsl_matrix *aux = matrices[0]; 
  matrices[0] = A;

  printf("[LOG]: Saving the result into an image... ");
  matrices_to_image(matrices,  output_path, channels);
  printf("DONE\n");

  printf("[LOG]: freeing the memory... ");
  gsl_vector_free(work);
  gsl_matrix_free(aux);
  for(int i = 0; i < channels; i++)
	  gsl_matrix_free(matrices[i]);
  gsl_matrix_free(V);
  gsl_vector_free(S);
  printf("DONE\n");
}
