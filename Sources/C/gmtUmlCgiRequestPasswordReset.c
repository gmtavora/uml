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
#include "./Libraries/sendmail.h"
#include "gmtUmlErrors.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlWebUserInterface.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlCompareCookie.h"
#include "gmtUmlCreateCookieFile.h"
#include "gmtUmlResetPassword.h"

int
main (int argc, char **argv)
{
  gmtUmlConfigurationOptionsType *configurationOptions;
  gmtUmlUserDataType *gmtUmlUserData, *gmtUmlNewUserData, *gmtUmlUsersList, *currentUser;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlUserProfileType gmtUmlUserProfile;
  boolean foundUser = False;
  char gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH+1],
       gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1],
       gmtUmlCookieName [16+1] = "GMT_UML",
       gmtUmlCookieNickname [16+1] = "GMT_UML_NICKNAME",
       gmtUmlRawProfile [GMT_UML_MAX_PROFILE_LENGTH+1],
       receivedValue [32+1],
       *validation;

  if (!(configurationOptions = malloc (sizeof (gmtUmlConfigurationOptionsType))))
    exit (gmtUmlErrorAllocatingMemory);

  if (!(gmtUmlUserData = malloc (sizeof (gmtUmlUserDataType))))
    exit (gmtUmlErrorAllocatingMemory);

  if (!(gmtUmlNewUserData = malloc (sizeof (gmtUmlUserDataType))))
    exit (gmtUmlErrorAllocatingMemory);

  if (mlCgiInitialize(&gmtUmlEnvironment))
  {
    free (configurationOptions);
    free (gmtUmlUserData);
    free (gmtUmlNewUserData);
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
    free (gmtUmlNewUserData);
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

  if (mlCgiGetSpecificCookie (gmtUmlCookieNickname, 17, gmtUmlNickname, 64+1) == ML_CGI_COOKIE_NOT_FOUND)
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
    printf ("</head>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    free (gmtUmlNewUserData);
    GmtUmlDestroyUserDataList (gmtUmlUsersList);
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

  if (mlCgiGetFormStringNoNewLines ("inputProfile", gmtUmlRawProfile, GMT_UML_MAX_NAME_LENGTH + 1))
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlErrorInvalidPassword);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidPassword, GmtUmlGetWebErrorMessage (gmtUmlErrorInvalidPassword, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  gmtUmlUserProfile = strtoull (gmtUmlRawProfile, &validation, 10);

  if (*validation != '\0')
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<title>Error #%i</title>", gmtUmlErrorInvalidProfile);
    printf ("</head>");
    printf ("<body>");
    printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidProfile, GmtUmlGetWebErrorMessage (gmtUmlErrorInvalidProfile, gmtUmlLanguage));
    printf ("</body>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  switch (gmtUmlUserProfile) {
    case 0:
    gmtUmlNewUserData->profile = 4;
    break;

    case 1:
    gmtUmlNewUserData->profile = 2;
    break;
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

  if (foundUser)
  {
    if (mlCgiGetSpecificCookie (gmtUmlCookieName, 8, receivedValue, 64+1) == ML_CGI_COOKIE_NOT_FOUND)
    {
      mlCgiEndHttpHeader ();
      printf ("<html>");
      printf ("<head>");
      printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
      printf ("</head>");
      printf ("</html>");
      free (configurationOptions);
      free (gmtUmlUserData);
      free (gmtUmlNewUserData);
      GmtUmlDestroyUserDataList (gmtUmlUsersList);
      mlCgiFreeResources ();
      return gmtUmlOk;
    }

    if ((gmtUmlValidation = GmtUmlCompareCookie (configurationOptions->gmtUmlCookiesDirectory, currentUser->id, receivedValue)))
    {
      mlCgiEndHttpHeader ();
      printf ("<html>");
      printf ("<head>");
      printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
      printf ("</head>");
      printf ("</html>");
      free (configurationOptions);
      free (gmtUmlUserData);
      free (gmtUmlNewUserData);
      GmtUmlDestroyUserDataList (gmtUmlUsersList);
      mlCgiFreeResources ();
      return gmtUmlOk;
    }
  }
  else
  {
    mlCgiEndHttpHeader ();
    printf ("<html>");
    printf ("<head>");
    printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
    printf ("</head>");
    printf ("</html>");
    free (configurationOptions);
    free (gmtUmlUserData);
    free (gmtUmlNewUserData);
    GmtUmlDestroyUserDataList (gmtUmlUsersList);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

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
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if (mlCgiGetFormStringNoNewLines ("inputEmail", gmtUmlNewUserData->email, GMT_UML_MAX_EMAIL_LENGTH + 1))
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
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if (mlCgiGetFormStringNoNewLines ("inputNickname", gmtUmlNewUserData->nickname, GMT_UML_MAX_NICKNAME_LENGTH + 1))
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
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if ((gmtUmlValidation = GmtUmlCheckStringField (gmtUmlNewUserData->nickname, GMT_UML_NICKNAME_VALID_CHARS, 3, GMT_UML_MAX_NICKNAME_LENGTH)))
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
    free (gmtUmlNewUserData);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  if((gmtUmlValidation = GmtUmlValidateUserInformation (gmtUmlNewUserData)))
  {
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    return gmtUmlOk;
  }

  if ((gmtUmlValidation = GmtUmlSelectNickname (gmtUmlNewUserData->name, gmtUmlNewUserData->nickname, configurationOptions)))
  {
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    return gmtUmlOk;
  }

  memset (gmtUmlNewUserData->password, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);
  memset (gmtUmlNewUserData->passwordConfirmation, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);

  if ((gmtUmlValidation = GmtUmlAddUser (configurationOptions, gmtUmlNewUserData)))
  {
    printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
    return gmtUmlOk;
  }

  free (configurationOptions);
  free (gmtUmlUserData);
  free (gmtUmlNewUserData);

  mlCgiEndHttpHeader ();

  printf ("<html>");
  printf ("<head>");

  printf ("<html>");
  printf ("<head>");
  printf ("<title>%s</title>", GmtUmlGetWebUserInterface (gmtUmlProjectName, gmtUmlLanguage));
  printf ("</head>");
  printf ("<body>An email was sent with instructions.</body>");
  printf ("</html>");

  printf ("</head>");
  printf ("</html>");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile: gmtUmlCgiLogin.c,v $ */
