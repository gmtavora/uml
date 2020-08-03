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

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "gmtUmlConst.h"
#include "gmtUmlTypes.h"
#include "./Libraries/mlcgi.h"
#include "gmtUmlErrors.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlWebUserInterface.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlCreateCookieFile.h"
#include "gmtUmlCompareCookie.h"

int
main (int argc, char **argv)
{
  gmtUmlConfigurationOptionsType *configurationOptions;
  gmtUmlUserDataType *gmtUmlUserData, *gmtUmlUsersList, *currentUser;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  gmtUmlErrorType gmtUmlValidation;
  char gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH+1],
       gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1],
       receivedValue [64+1];
  char *token;
  boolean foundUser = False;

  if (!(configurationOptions = malloc (sizeof (gmtUmlConfigurationOptionsType))))
    return gmtUmlOk;

  if (!(gmtUmlUserData = malloc (sizeof (gmtUmlUserDataType))))
    return gmtUmlOk;

  if (mlCgiInitialize(&gmtUmlEnvironment))
  {
    free (configurationOptions);
    free (gmtUmlUserData);
    return gmtUmlOk;
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
    return gmtUmlOk;
  }

  memset (receivedValue, 0x00, 65);

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlConfigurationFileName", gmtUmlConfigurationFileName, GMT_UML_MAX_FILE_NAME_LENGTH+1)))
  {
    strcpy (gmtUmlConfigurationFileName, GMT_UML_DEFAULT_CONFIG_FILE);
  }

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlLanguage", gmtUmlLanguageName, GMT_UML_MAX_FILE_NAME_LENGTH + 1)))
  {
    strcpy (gmtUmlLanguageName, "english");
  }

  mlCgiBeginHttpHeader ("text/html");

  gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

  if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfigurationFileName, configurationOptions)))
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
    if (mlCgiGetSpecificCookie ("GMT_UML", 8, receivedValue, 64+1) == ML_CGI_COOKIE_NOT_FOUND)
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
      GmtUmlDestroyUserDataList (gmtUmlUsersList);
      mlCgiFreeResources ();
      return gmtUmlOk;
    }

    if (currentUser->profile > 3)
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
    GmtUmlDestroyUserDataList (gmtUmlUsersList);
    mlCgiFreeResources ();
    return gmtUmlOk;
  }

  mlCgiEndHttpHeader ();

  token = strtok (currentUser->name, " ");

  printf ("<!DOCTYPE html>");
  printf ("<html>");
  printf ("<head>");
  printf ("<meta charset=\"utf-8\">");
  printf ("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">");
  printf ("<link rel=\"icon\" href=\"favicon.ico\">");
  printf ("<link rel=\"stylesheet\" type=\"text/css\" href=\"bootstrap/css/bootstrap.min.css\">");
  printf ("<link rel=\"stylesheet\" href=\"style.css\">");
  printf ("<title>%s</title>", GmtUmlGetWebUserInterface (gmtUmlPageTitle, gmtUmlLanguage));
  printf ("</head>");
  printf ("<body>");
  printf ("<nav class=\"navbar navbar-expand-lg navbar-light bg-light\">");
  printf ("<a class=\"navbar-brand\" href=\"/~gabriel.tavora/index.html\">%s</a>", GmtUmlGetWebUserInterface (gmtUmlProjectName, gmtUmlLanguage));
  printf ("<button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarNavAltMarkup\" aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">");
  printf ("<span class=\"navbar-toggler-icon\"></span>");
  printf ("</button>");
  printf ("<div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\">");
  printf ("<div class=\"navbar-nav\">");
  printf ("<a class=\"nav-item nav-link\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlHome, gmtUmlLanguage));
  printf ("<a class=\"nav-item nav-link\" href=\"gmtUmlShowRequestRegistrationForm.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlRegister, gmtUmlLanguage));
  printf ("<a class=\"nav-item nav-link\" href=\"gmtUmlShowRequestPasswordResetForm.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlResetPassword, gmtUmlLanguage));
  printf ("<a class=\"nav-item nav-link\" href=\"gmtUmlShowWebHelp.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlHelp, gmtUmlLanguage));
  printf ("<a class=\"nav-item nav-link\" href=\"gmtUmlShowLicense.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlLicense, gmtUmlLanguage));
  printf ("<div class=\"nav-item dropdown\">");
  printf ("<a class=\"nav-link dropdown-toggle\" href=\"#\" id=\"navbarDropdown\" role=\"button\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">");
  printf ("%s", GmtUmlGetWebUserInterface (gmtUmlLanguageSelect, gmtUmlLanguage));
  printf ("</a>");
  printf ("<div class=\"dropdown-menu\" aria-labelledby=\"navbarDropdown\">");
  printf ("<a class=\"dropdown-item\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=english&gmtUmlConfigurationFileName=%s\"><img src=\"../images/en-us.png\"> English</a>", gmtUmlConfigurationFileName);
  printf ("<a class=\"dropdown-item\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=portuguese&gmtUmlConfigurationFileName=%s\"><img src=\"../images/pt-br.png\"> Portuguese</a>", gmtUmlConfigurationFileName);
  printf ("<a class=\"dropdown-item disabled\" href=\"#\"><img src=\"../images/de.png\"> German</a>");
  printf ("</div>");
  printf ("</div>");
  printf ("</div>");
  printf ("</nav>");

  printf ("<div class=\"container\">");
  printf ("<div class=\"card card-container\">");
  printf ("<h1>%s %s</h1>", GmtUmlGetWebUserInterface (gmtUmlHello, gmtUmlLanguage), token);
  printf ("<h6>%s</h6>", GmtUmlGetWebUserInterface (gmtUmlSelectOption, gmtUmlLanguage));

  printf ("<div class=\"btn-group-vertical\" role=\"group\" aria-label=\"Button group with nested dropdown\">");
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlAddUserForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebAddUser, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlInviteUserForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebInviteUser, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlRegistrationRequests.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebRegistrationRequests, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlLockUserForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebLockUser, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlUnlockUser.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebUnlockUser, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlResetUserPasswordForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebResetUserPassword, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlChangeUserPasswordForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebChangeUserPassword, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlChangeUserNameForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebChangeUserName, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlChangeUserEmailForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebChangeUserEmail, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlChangeUserProfileForm.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebChangeUserProfile, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlGetUsers.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebGetUsers, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlUserPanel.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebUsersPanel, gmtUmlLanguage));
  printf ("<button type=\"button\" class=\"btn btn-lg btn-primary btn-block btn-menu\" onclick=\"window.location.href='gmtUmlLogout.cgi?gmtUmlLanguage=%i&gmtUmlConfigurationFileName=%s';\">%s</button>", gmtUmlLanguage, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlWebLogout, gmtUmlLanguage));
  printf ("</div>");
  printf ("</div>");
  printf ("</div>");

  printf ("<div class=\"footer\">");
  printf ("<a href=\"mailto:gabriel.tavora@poli.ufrj.br\">© 2017 Gabriel Montenegro Tavora.</a>");
  printf ("</div>");

  printf ("<script src=\"jquery-3.2.1.js\"></script>");
  printf ("<script src=\"bootstrap/js/bootstrap.bundle.min.js\"></script>");
  printf ("</body>");
  printf ("</html>");

  free (configurationOptions);
  free (gmtUmlUserData);
  GmtUmlDestroyUserDataList (gmtUmlUsersList);
  mlCgiFreeResources ();
  return gmtUmlOk;
}
