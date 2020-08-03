/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlCgiLogin.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "gmtUmlConst.h"
#include "gmtUmlTypes.h"
#include "./Libraries/mlcgi.h"
#include "gmtUmlErrors.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlWebUserInterface.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlCreateCookieFile.h"

int
main (int argc, char **argv)
{
  gmtUmlConfigurationOptionsType *configurationOptions;
  gmtUmlUserDataType *gmtUmlUserData;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  gmtUmlErrorType gmtUmlValidation;
  char gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH+1],
       gmtUmlPassword [GMT_UML_MAX_PASSWORD_LENGTH+1],
       gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1],
       gmtUmlCookieName [16+1] = "GMT_UML",
       gmtUmlCookieNickname [16+1] = "GMT_UML_NICKNAME",
       gmtUmlCookieValue [32+1];

  if (!(configurationOptions = malloc (sizeof (gmtUmlConfigurationOptionsType))))
    exit (gmtUmlErrorAllocatingMemory);

  if (!(gmtUmlUserData = malloc (sizeof (gmtUmlUserDataType))))
    exit (gmtUmlErrorAllocatingMemory);

  if (mlCgiInitialize(&gmtUmlEnvironment))
  {
    free (configurationOptions);
    free (gmtUmlUserData);
    exit (ML_CGI_OK);
  }

  if (gmtUmlEnvironment == commandLine)
  {
    switch (gmtUmlLanguage)
    {
      default:
      case gmtUmlEnglish:
      printf ("ERROR: Invalid environment.\n");
      break;

      case gmtUmlPortuguese:
      printf ("ERRO: Ambiente invalido.\n");
      break;
    }

    free (configurationOptions);
    free (gmtUmlUserData);
    exit (gmtUmlErrorInvalidEnvironment);
  }

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlConfigurationFileName", gmtUmlConfigurationFileName, GMT_UML_MAX_FILE_NAME_LENGTH+1)))
  {
    strcpy (gmtUmlConfigurationFileName, GMT_UML_DEFAULT_CONFIG_FILE);
  }

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlLanguage", gmtUmlLanguageName, GMT_UML_MAX_LANGUAGE_LENGTH + 1)))
  {
    strcpy (gmtUmlLanguageName, "english");
  }

  /* HTML HEADER */

  mlCgiBeginHttpHeader ("text/html");

  gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

  if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfigurationFileName, configurationOptions)))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlValidation);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if (mlCgiGetFormStringNoNewLines ("nickname", gmtUmlNickname, GMT_UML_MAX_FILE_NAME_LENGTH + 1))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlErrorInvalidNickname);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if (mlCgiGetFormStringNoNewLines ("password", gmtUmlPassword, GMT_UML_MAX_FILE_NAME_LENGTH + 1))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlErrorInvalidPassword);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidPassword, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if ((gmtUmlValidation = GmtUmlCheckStringField (gmtUmlNickname, GMT_UML_NICKNAME_VALID_CHARS, 3, GMT_UML_MAX_NICKNAME_LENGTH)))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlValidation);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if ((gmtUmlValidation = GmtUmlCheckStringField (gmtUmlPassword, GMT_UML_PASSWORD_VALID_CHARS, GMT_UML_MIN_PASSWORD_LENGTH, GMT_UML_MAX_PASSWORD_LENGTH)))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlValidation);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if ((gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, configurationOptions, gmtUmlUserData)))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlValidation);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  GmtUmlCreateCookieFile (configurationOptions->gmtUmlCookiesDirectory, gmtUmlUserData->id, (time (NULL) + 3600), gmtUmlCookieValue);
  mlCgiSetCookie (gmtUmlCookieName, gmtUmlCookieValue, 3600, NULL, NULL, NULL);
  mlCgiSetCookie (gmtUmlCookieNickname, gmtUmlUserData->nickname, 3600, NULL, NULL, NULL);
  free (configurationOptions);
  free (gmtUmlUserData);

  mlCgiEndHttpHeader ();

  printf ("<html>");
  printf ("<head>");

  if (gmtUmlUserData->profile < 4)
    printf ("<meta http-equiv=\"refresh\" content=\"0,./gmtUmlAdminPanel.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguage, gmtUmlConfigurationFileName);
  else
    printf ("<meta http-equiv=\"refresh\" content=\"0,./gmtUmlUserPanel.cgi?gmtUmlLanguage=%ii&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguage, gmtUmlConfigurationFileName);

  printf ("</head>");
  printf ("</html>");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile: gmtUmlCgiLogin.c,v $ */
