#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

#define NUMERO_ARGUMENTOS		3
#define COMPRIMENTO_MAX_LINHA		1024

#define OK				0
#define ERRO_ARGUMENTO_INVALIDO		1
#define ERRO_MANIPULANDO_ARQUIVO	2
#define ERRO_STRING_OVERFLOW		3

int
main (int argc, char **argv)
{
  FILE *leitura, *gravacao;
  char buffer;
  char string [2*(COMPRIMENTO_MAX_LINHA)+1];
  unsigned short indice = 0;
  
  if (argc != NUMERO_ARGUMENTOS)
  {
    printf ("USO: %s <entrada> <saida>.\n", argv[0]);
    exit (ERRO_ARGUMENTO_INVALIDO);
  }
  
  leitura = fopen (argv[1], "r");
  
  if (!leitura)
  {
    printf ("ERRO: nao foi possivel abrir o arquivo %s.\n", argv[1]);
    printf ("ERROR (%i): %s.\n", errno, strerror (errno));
    exit (ERRO_MANIPULANDO_ARQUIVO);
  }
  
  gravacao = fopen (argv[2], "w");
  
  if (!gravacao)
  {
    printf ("ERRO: nao foi possivel criar o arquivo %s.\n", argv[2]);
    printf ("ERROR (%i): %s.\n", errno, strerror (errno));
    fclose (leitura);
    exit (ERRO_MANIPULANDO_ARQUIVO);
  }
  
  memset (string, 0x00, COMPRIMENTO_MAX_LINHA+1);
  
  while ((buffer = fgetc (leitura)) != EOF)
  {
    if (buffer == '\r')
    {
      indice++;
      continue;
    }
    if (buffer == '\"' || buffer == '\'')
    {
      string[indice] = '\\';
      indice++;
    }
    if (buffer == '\n')
    {
      if (indice == 0)
        continue;

      fprintf (gravacao, "printf (\"%s\");\n", string);
      memset (string, 0x00, COMPRIMENTO_MAX_LINHA+1);
      indice = 0;
    } else {
      if (indice == COMPRIMENTO_MAX_LINHA)
      {
        printf ("ERRO: linha excede comprimento maximo.\n");
        fclose (leitura);
        fclose (gravacao);
        exit (ERRO_STRING_OVERFLOW);
      }
      string [indice] = buffer;
      indice++;
    }
  }

  printf ("Sucesso.\n");
  
  fclose (leitura);
  fclose (gravacao);
  
  return OK;
}
