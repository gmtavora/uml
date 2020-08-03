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
#include<string.h>
#include<time.h>

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"
#include "./Libraries/mlcgi.h"
#include "gmtUmlCreateCookieFile.h"
#include "gmtUmlCompareCookie.h"

/*
 * gmtUmlErrorType
 * GmtUmlVerifyLogin (gmtUmlConfigurationOptionsType *, gmtUmlLanguageType, gmtUmlUserIdentifierType, char *)
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the configuration options (I)
 * gmtUmlLanguageType - the language (I)
 * gmtUmlUserIdentifierType - the user id (I)
 * char * - the address to go to, in case of success (I)
 *
 * Returned code:
 *
 * Description:
 * Verify if the user is logged in.
 */

gmtUmlErrorType
GmtUmlVerifyLogin (gmtUmlConfigurationOptionsType *configurationOptions, gmtUmlLanguageType gmtUmlLanguage, gmtUmlUserIdentifierType gmtUmlUserId)
{
  char name [13] = "GMT_UML";
  char receivedValue [64+1];

  if (configurationOptions == NULL)
    return gmtUmlErrorNullPointer;

  /*GmtUmlCreateCookieFile (directory, 0, time (NULL) + expiration, value);
  mlCgiSetCookie (name, value, expiration, NULL, "www02.del.ufrj.br", NULL);*/

  if (mlCgiGetSpecificCookie (name, 6, receivedValue, 64+1) == ML_CGI_COOKIE_NOT_FOUND)
    return gmtUmlErrorNotLoggedIn;

  if (!GmtUmlCompareCookie (configurationOptions->gmtUmlCookiesDirectory, gmtUmlUserId, receivedValue))
    return gmtUmlErrorInvalidCookie;

  return gmtUmlOk;
}
