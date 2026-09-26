# ---------------------------------------------------------
# Variables por defecto (si no se pasan por línea de comandos)
# ---------------------------------------------------------
if (!exists("infile"))  infile = 'datos.dat'
if (!exists("outfile")) outfile = 'grafica.png'
if (!exists("pct"))     pct = 0.90

# ---------------------------------------------------------
# Configuración de salida PNG
# ---------------------------------------------------------
set terminal pngcairo size 1200,800 font "Sans,12"
set output outfile

# ---------------------------------------------------------
# Analizar el archivo y calcular el rango
# ---------------------------------------------------------
stats infile skip 1 using 1 nooutput
N = STATS_records

inicio = int(N * (1.0 - pct))

# Configuración visual
set title sprintf("Archivo: %s | %.0f%% final (%d a %d)", infile, pct*100, inicio, N)
set xlabel "Índice"
set ylabel "Valor"
set grid

# ---------------------------------------------------------
# Graficar
# ---------------------------------------------------------
plot infile skip 1 every ::inicio::N using 1 with lines title "Datos"

unset output

