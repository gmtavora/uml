/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author$
 * $Date$
 * $Log$
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#include "gmtUmlErrors.h"
#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlCreateCookieFile.h"

/*
 * gmtUmlErrorType
 * GmtUmlCreateCookieFile (char *cookiesDirectory, gmtUmlUserIdentifierType userId, unsigned long long expiration);
 *
 * Arguments:
 * char * - the directory to store the cookie (I)
 * gmtUmlUserIdentifierType - user id (I)
 * unsigned long long - expiration in seconds (I)
 * char * - the value generated (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Saves a cookie file in the specified directory. The file name will be the user id.
 */

gmtUmlErrorType
GmtUmlCreateCookieFile (char *cookiesDirectory, gmtUmlUserIdentifierType userId, unsigned long long expiration, char *generatedValue)
{
  FILE *file;
  char path [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       value [GMT_UML_MAX_COOKIE_LENGTH+1];
  unsigned index;

  srand ((unsigned) time (NULL));

  if ((cookiesDirectory == NULL) || (value == NULL))
    return gmtUmlErrorNullPointer;

  snprintf (path, GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+64, "%s%020llu", cookiesDirectory, userId);

  for (index = 0; index < GMT_UML_MAX_COOKIE_LENGTH; index++)
    value [index] = GMT_UML_COOKIE_VALID_CHARS [rand () % strlen (GMT_UML_COOKIE_VALID_CHARS)];

  value [index] = 0;

  file = fopen (path, "w");

  if (!file)
    return gmtUmlErrorOpeningFile;

  fprintf (file, "%llu:%s", expiration, value);

  strcpy (generatedValue, value);

  fclose (file);

  return gmtUmlOk;
}

/* $RCSfile$ */