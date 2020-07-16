#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <omp.h>
#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
#define MAXIMA_LONGITUD_CADENA 5000
#define MOD(i, n) (i % n + n) % n

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
void cifrar(char *mensaje, char *destino, int rotaciones);
void descifrar(char *mensaje, char *destino, int rotaciones);
int ord(char c);

int main(void) {
  // El original, el cifrado y luego el descifrado
  char mensaje[MAXIMA_LONGITUD_CADENA], mensajeCifrado[MAXIMA_LONGITUD_CADENA],
      mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
  printf("Escribe un mensaje para que lo cifre:\n",
         MAXIMA_LONGITUD_CADENA - 1);
  // Esto es para obtener el mensaje y evitar desbordamientos; se puede ignorar
  fgets(mensaje, MAXIMA_LONGITUD_CADENA, stdin);
  /*Quitar el salto de línea*/ mensaje[strcspn(mensaje, "\r\n")] = 0;
  // ¿Cuántas rotaciones?
  int rotaciones;
  printf("Escribe el numero de rotaciones:\n");
  scanf("%d", &rotaciones);
  // Ahora sí ciframos y descriframos
  printf("El mensaje original es: %s\n", mensaje);
  cifrar(mensaje, mensajeCifrado, rotaciones);
  printf("El mensaje cifrado es: %s\n", mensajeCifrado);
  descifrar(mensajeCifrado, mensajeDescifrado, rotaciones);
  printf("El mensaje descifrado es: %s\n", mensajeDescifrado);
  return 0;
}

void cifrar(char *mensaje, char *destino, int rotaciones) {
  /*Recorrer cadena*/
  int i = 0;
  #pragma omp parallel shared(mensaje, i)
  while (mensaje[i]) {
    char caracterActual = mensaje[i];
    int posicionOriginal = ord(caracterActual);
    if (!isalpha(caracterActual)) {
      destino[i] = caracterActual;
      i++;
      continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
    }
    if (isupper(caracterActual)) {
      destino[i] =
          alfabetoMayusculas[(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS +
                              rotaciones) %
                             LONGITUD_ALFABETO];
    } else {

      destino[i] =
          alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS +
                              rotaciones) %
                             LONGITUD_ALFABETO];
    }
    i++;
  }
}

void descifrar(char *mensaje, char *destino, int rotaciones) {
  /*Recorrer cadena*/
  int i = 0;
  while (mensaje[i]) {
    char caracterActual = mensaje[i];
    int posicionOriginal = ord(caracterActual);
    if (!isalpha(caracterActual)) {
      destino[i] = caracterActual;
      i++;
      continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
    }
    if (isupper(caracterActual)) {
      destino[i] = alfabetoMayusculas[MOD(
          posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - rotaciones,
          LONGITUD_ALFABETO)];
    } else {
      destino[i] = alfabetoMinusculas[MOD(
          posicionOriginal - INICIO_ALFABETO_MINUSCULAS - rotaciones,
          LONGITUD_ALFABETO)];
    }
    i++;
  }
}
int ord(char c) { return (int)c; }
