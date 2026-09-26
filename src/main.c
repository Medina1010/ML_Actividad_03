#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define BLD_IMPLEMENTATION

#include "gsl_wrapper.h"
#include "image_wrapper.h"
#include "bld.h"

void svd_svc_image(char *input_path, char *output_path, int channels);
void svd_and_save(char *input_path, int channels);
void svd_compose(char *input_path, int channels);
void analysis_vector(gsl_vector* vector);
void analysis_and_graph(const char* file_wno_extension, float percent);

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  //svd_svc_image("../res/Image_01.png", "../res/Image_01_feo.png", 1);
  //svd_svc_image("../res/Image_02.png", "../res/Image_02_feo.png", 1);
  //svd_svc_image("../res/Image_03.png", "../res/Image_03_feo.png", 1);
  //svd_svc_image("../res/Image_04.png", "../res/Image_04_feo.png", 1);
  //svd_svc_image("../res/Image_05.png", "../res/Image_05_feo.png", 1);
  //svd_svc_image("../res/Image_06.png", "../res/Image_06_feo.png", 1);
  int channels = 3;
  //svd_and_save("../res/Image_01", channels);
  //svd_and_save("../res/Image_02", channels);
  //svd_and_save("../res/Image_03", channels);
  //svd_and_save("../res/Image_04", channels);
  //svd_and_save("../res/Image_05", channels);
  //svd_and_save("../res/Image_06", channels);
  
  //svd_compose("../res/Image_01", channels);
  //svd_compose("../res/Image_02", channels);
  //svd_compose("../res/Image_03", channels);
  //svd_compose("../res/Image_04", channels);
  //svd_compose("../res/Image_05", channels);
  //svd_compose("../res/Image_06", channels);
  

  analysis_and_graph("../res/Image_01_S_c0_3", 0.9);

  return 0;
}

void analysis_and_graph(const char* file_wno_extension, float percent) {
  char input[128];
  char output[128];
  sprintf(input, "%s.dat", file_wno_extension);
  sprintf(output, "%s_curve.png", file_wno_extension);

  gsl_vector* S = load_vector_from_file(input);
  gsl_vector_view v_truncated = gsl_vector_subvector(S, S->size * (1 - percent), S->size * percent);
  analysis_vector(&v_truncated.vector);
  gsl_vector_free(S);

  char command[512];
  sprintf(command, "gnuplot -e \"infile='%s'; outfile='%s'; pct=%f\" plot.gp", input, output, percent);
  cmd(command);
}

#include <gsl/gsl_fit.h>

// Función para calcular la Suma Total de Cuadrados (TSS) de un array
double compute_tss(const double *y, size_t n) {
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        sum += y[i];
    }
    double mean = sum / n;

    double tss = 0.0;
    for (size_t i = 0; i < n; i++) {
        double diff = y[i] - mean;
        tss += diff * diff;
    }
    return tss;
}

// Estructura para almacenar resultados del ajuste
typedef struct {
    double c0;       // Intercepto (o log de A)
    double c1;       // Pendiente B
    double sum_sq;   // Suma de los residuos al cuadrado
    double R2;       // Coeficiente de determinación R^2
} FitResult;

// Ajuste Lineal: y = c0 + c1 * x
FitResult fit_linear(const double *x, const double *y, size_t n) {
    FitResult res;
    double cov00, cov01, cov11;
    
    gsl_fit_linear(x, 1, y, 1, n, &res.c0, &res.c1, &cov00, &cov01, &cov11, &res.sum_sq);
    
    double tss = compute_tss(y, n);
    res.R2 = 1.0 - (res.sum_sq / tss);
    return res;
}

// Ajuste Exponencial: y = A * exp(B * x)  =>  ln(y) = ln(A) + B * x
FitResult fit_exponential(const double *x, const double *y, size_t n) {
    double y_log[n];
    for (size_t i = 0; i < n; i++) {
        y_log[i] = log(y[i]);
    }
    
    FitResult res;
    double cov00, cov01, cov11;
    
    gsl_fit_linear(x, 1, y_log, 1, n, &res.c0, &res.c1, &cov00, &cov01, &cov11, &res.sum_sq);
    
    double tss = compute_tss(y_log, n);
    res.R2 = 1.0 - (res.sum_sq / tss);
    return res; // A = exp(res.c0), B = res.c1
}

// Ajuste Algebraico (Potencia): y = A * x^B  =>  ln(y) = ln(A) + B * ln(x)
FitResult fit_algebraic(const double *x, const double *y, size_t n) {
    double x_log[n], y_log[n];
    for (size_t i = 0; i < n; i++) {
        x_log[i] = log(x[i]);
        y_log[i] = log(y[i]);
    }
    
    FitResult res;
    double cov00, cov01, cov11;
    
    gsl_fit_linear(x_log, 1, y_log, 1, n, &res.c0, &res.c1, &cov00, &cov01, &cov11, &res.sum_sq);
    
    double tss = compute_tss(y_log, n);
    res.R2 = 1.0 - (res.sum_sq / tss);
    return res; // A = exp(res.c0), B = res.c1
}

void analysis_vector(gsl_vector* vector) {
    // Ejemplo de datos en vectores gsl_vector
    size_t n = vector->size;
    gsl_vector *v_x = gsl_vector_alloc(n);


    for (size_t i = 0; i < n; i++) {
        gsl_vector_set(v_x, i, i+1);
    }

    // Punteros a los arrays continuos subyacentes de gsl_vector
    double *x = gsl_vector_ptr(v_x, 0);
    double *y = gsl_vector_ptr(vector, 0);

    // Cálculo de los coeficientes
    FitResult res_lin = fit_linear(x, y, n);
    FitResult res_exp = fit_exponential(x, y, n);
    FitResult res_alg = fit_algebraic(x, y, n);

    // Impresión de resultados
    printf("--- Coeficientes R^2 ---\n");
    printf("Modelo Lineal:      R^2 = %.6f\n", res_lin.R2);
    printf("Modelo Exponencial: R^2 = %.6f  (y = %.4f * e^(%.4f * x))\n", 
           res_exp.R2, exp(res_exp.c0), res_exp.c1);
    printf("Modelo Algebraico:  R^2 = %.6f  (y = %.4f * x^(%.4f))\n", 
           res_alg.R2, exp(res_alg.c0), res_alg.c1);

    // Limpieza de memoria
    gsl_vector_free(v_x);

}

void svd_and_save(char *input_path, int channels) {
  printf("[LOG]: Doing process for \"%s\"... ", input_path);
  char str[256];
  sprintf(str, "%s.png", input_path);
  gsl_matrix **matrices = matrices_from_image(str, channels);
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
    sprintf(str, "%s_U_c%d_%d.dat", input_path, i, channels);
    save_matrix_to_file(str, matrices[i]);
    sprintf(str, "%s_S_c%d_%d.dat", input_path, i, channels);
    save_vector_to_file(str, S[i]);
    sprintf(str, "%s_V_c%d_%d.dat", input_path, i, channels);
    save_matrix_to_file(str, V[i]);
    printf("DONE\n");
  }
  printf("[LOG]: freeing the memory... ");
  gsl_vector_free(work);
  for (int i = 0; i < channels; i++) {
    gsl_matrix_free(matrices[i]);
    gsl_matrix_free(V[i]);
    gsl_vector_free(S[i]);
  }
  printf("DONE\n");
}

void svd_compose(char *input_path, int channels) {
  printf("[LOG]: Doing process for \"%s\"... ", input_path);
  char str[256];
  printf("DONE\n");

  gsl_matrix *matrices[channels];
  gsl_matrix *V[channels];
  gsl_vector *S[channels];
  for (int i = 0; i < channels; i++) {
    sprintf(str, "%s_U_c%d_%d.dat", input_path, i, channels);
    matrices[i] = load_matrix_from_file(str);
    sprintf(str, "%s_S_c%d_%d.dat", input_path, i, channels);
    S[i] = load_vector_from_file(str);
    sprintf(str, "%s_V_c%d_%d.dat", input_path, i, channels);
    V[i] = load_matrix_from_file(str);
  }
  gsl_vector *work = gsl_vector_alloc((*matrices)->size2);

  for (int i = 0; i < channels; i++) {
    printf("[LOG]: removing sv's less than 5%% for channel %d/%d... ", i + 1,
           channels);
    double sv_total = 0;
    for (int j = 0; j < (*S)->size; j++)
      sv_total += gsl_vector_get(S[i], j);
    double sv_sum = 0;
    int index;
    for (int j = 0; j < (*S)->size; j++) {
      if (sv_sum > sv_total * 0.2f) {
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
  sprintf(str, "%s_c%d.png", input_path, channels);
  printf("[LOG]: Saving the result into \"%s\"... ", str);
  sprintf(str, "%s_c%d.png", input_path, channels);
  matrices_to_image(matrices, str, channels);
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
