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
  gmtUmlUserDataType *gmtUmlUserData, *gmtUmlUsersList, *currentUser;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  char gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH+1],
       gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1],
       path [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];
  gmtUmlErrorType gmtUmlValidation;
  boolean foundUser = False;

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

  if (mlCgiGetSpecificCookie ("GMT_UML_NICKNAME", 17, gmtUmlNickname, 64+1) == ML_CGI_COOKIE_NOT_FOUND)
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
    printf ("</head>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    GmtUmlDestroyUserDataList (gmtUmlUsersList);
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

  if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, configurationOptions)))
  {
    mlCgiBeginHttpHeader ("text/html");
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetWebErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  currentUser = gmtUmlUsersList;

  while (currentUser != NULL)
  {
    if (!strcmp (currentUser->nickname, gmtUmlNickname))
    {
      foundUser = True;
      break;
    }

    currentUser = currentUser->next;
  }

  if (!foundUser)
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error</title>");
    printf ("</head>");
    printf ("<body>");
    printf ("You are not logged in.");
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  snprintf (path, GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH, "%s%020llu", configurationOptions->gmtUmlCookiesDirectory, gmtUmlUserData->id);
  remove (path);
  free (configurationOptions);
  free (gmtUmlUserData);

  mlCgiEndHttpHeader ();

  printf ("<html>");
  printf ("<head>");
  printf ("<meta http-equiv=\"refresh\" content=\"0,./gmtUmlMain.cgi?gmtUmlLanguage=%ii&gmtUmlConfigurationFileName=%s&gmtUmlNickname=%s\">", gmtUmlLanguage, gmtUmlConfigurationFileName, gmtUmlNickname);
  printf ("</head>");
  printf ("</html>");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile: gmtUmlCgiLogin.c,v $ */
