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
#include "gmtUmlCompareCookie.h"

#define COOKIE_CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!."

/*
 * boolean
 * GmtUmlCompareCookieValues (char *cookiesDirectory, gmtUmlUserIdentifierType userId, char *receivedValue);
 *
 * Arguments:
 * char * - the cookie's directory (I)
 * gmtUmlUserIdentifierType - user id (I)
 * char * - the received value (I)
 *
 * Returned code:
 * true - the cookie is valid;
 * false - the cookie is invalid;
 *
 * Description:
 * Compares the informed cookie with the stored value, and returns true or false.
 */

gmtUmlErrorType
GmtUmlCompareCookie (char *cookiesDirectory, gmtUmlUserIdentifierType userId, char *receivedValue)
{
  FILE *file;
  char path [GMT_UML_MAX_FILE_NAME_LENGTH+GMT_UML_MAX_PATH_LENGTH+1],
       buffer [64+1];
  char *token, *validation;
  unsigned long long expiration;

  if ((cookiesDirectory == NULL) || (receivedValue == NULL))
    return gmtUmlErrorNullPointer;

  snprintf (path, GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+64, "%s%020llu", cookiesDirectory, userId);

  if ((access (path, F_OK) == -1))
    return gmtUmlErrorCookieDoesntExist;

  file = fopen (path, "r");

  if (!file)
    return gmtUmlErrorOpeningCookie;

  fgets (buffer, 64+1, file);

  token = strtok (buffer, ":");

  if (token == NULL)
  {
    fclose (file);
    remove (path);
    return gmtUmlErrorCorruptedCookie;
  }

  expiration = strtoull (token, &validation, 10);

  if (*validation != '\0')
  {
    fclose (file);
    remove (path);
    return gmtUmlErrorCorruptedCookie;
  }

  if ((time (NULL) > expiration))
  {
    fclose (file);
    remove (path);
    return gmtUmlErrorExpiredCookie;
  }

  token = strtok (NULL, ":");

  if (token == NULL)
  {
    fclose (file);
    remove (path);
    return gmtUmlErrorCorruptedCookie;
  }

  if (token [strlen (token)-1] == '\n')
    token [strlen (token)-1] = 0;

  if (!strcmp (receivedValue, token))
  {
    fclose (file);
    return gmtUmlOk;
  }

  fclose (file);
  remove (path);
  return gmtUmlErrorIncorrectCookie;
}

/* $RCSfile$ */
