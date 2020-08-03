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
#include<ctype.h>

#include "gmtUmlConst.h"
#include "gmtUmlTypes.h"
#include "./Libraries/mlcgi.h"
#include "gmtUmlErrors.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlWebUserInterface.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlCreateCookieFile.h"
#include "gmtUmlCompareCookie.h"
#include "gmtUmlSearchUsers.h"

int
main (int argc, char **argv)
{
  gmtUmlConfigurationOptionsType *configurationOptions;
  gmtUmlUserDataType *gmtUmlUserData, *gmtUmlUsersList, *currentUser;
  gmtUmlUserProfileType gmtUmlProfile = 0;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  gmtUmlErrorType gmtUmlValidation;
  char gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH+1],
       gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1],
       gmtUmlNameFilter [GMT_UML_MAX_NAME_LENGTH+1],
       gmtUmlProfileFilter [GMT_UML_MAX_PROFILE_LENGTH+1],
       gmtUmlEmailFilter [GMT_UML_MAX_EMAIL_LENGTH+1],
       receivedValue [64+1];
  boolean foundUser = False, filtering = False;
  unsigned count = 0, index = 0;

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

  memset (gmtUmlNameFilter, 0x00, GMT_UML_MAX_NAME_LENGTH+1);
  memset (gmtUmlEmailFilter, 0x00, GMT_UML_MAX_EMAIL_LENGTH+1);
  memset (gmtUmlProfileFilter, 0x00, GMT_UML_MAX_PROFILE_LENGTH+1);
  memset (receivedValue, 0x00, 65);

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlConfigurationFileName", gmtUmlConfigurationFileName, GMT_UML_MAX_FILE_NAME_LENGTH+1)))
  {
    strcpy (gmtUmlConfigurationFileName, GMT_UML_DEFAULT_CONFIG_FILE);
  }

  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlLanguage", gmtUmlLanguageName, GMT_UML_MAX_FILE_NAME_LENGTH + 1)))
  {
    strcpy (gmtUmlLanguageName, "english");
  }

  if (mlCgiGetFormStringNoNewLines ("inputName", gmtUmlNameFilter, GMT_UML_MAX_NAME_LENGTH + 1) == ML_CGI_OK)
    filtering = True;

  if (mlCgiGetFormStringNoNewLines ("inputEmail", gmtUmlEmailFilter, GMT_UML_MAX_NAME_LENGTH + 1) == ML_CGI_OK)
    filtering = True;

  if (mlCgiGetFormStringNoNewLines ("inputProfile", gmtUmlProfileFilter, GMT_UML_MAX_NAME_LENGTH + 1) == ML_CGI_OK)
    if (strlen (gmtUmlProfileFilter))
    {
      filtering = True;

      for (index = 0; index < strlen (gmtUmlProfileFilter); index++)
        gmtUmlProfileFilter [index] = toupper (gmtUmlProfileFilter [index]);

      if ((strcmp (gmtUmlProfileFilter, "MAIN ADMIN") == 0) || (strcmp (gmtUmlProfileFilter, "ADMIN PRINCIPAL") == 0))
        gmtUmlProfile = 1;
      else if ((strcmp (gmtUmlProfileFilter, "ADMIN") == 0) || (strcmp (gmtUmlProfileFilter, "ADMIN") == 0))
        gmtUmlProfile = 2;
      else if ((strcmp (gmtUmlProfileFilter, "USER") == 0) || (strcmp (gmtUmlProfileFilter, "USUARIO") == 0))
        gmtUmlProfile = 4;
      else
      {
        mlCgiBeginHttpHeader ("text/html");
        mlCgiEndHttpHeader ();
        printf ("<html>");
        printf ("<head>");
        printf ("<meta http-equiv=\"refresh\" content=\"0,gmtUmlGetUsers.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">", gmtUmlLanguageName, gmtUmlConfigurationFileName);
        printf ("</head>");
        printf ("<body>");
        printf ("<script>alert (\"%s\");</script>", GmtUmlGetWebErrorMessage (gmtUmlErrorInvalidProfile, gmtUmlLanguage));
        printf ("</body>");
        printf ("</html>");
        free (configurationOptions);
        free (gmtUmlUserData);
        mlCgiFreeResources ();
        return gmtUmlOk;
      }
    }

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
    mlCgiBeginHttpHeader ("text/html");
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

  mlCgiBeginHttpHeader ("text/html");

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
  printf ("<a class=\"dropdown-item\" href=\"gmtUmlGetUsers.cgi?gmtUmlLanguage=english&gmtUmlConfigurationFileName=%s\"><img src=\"../images/en-us.png\"> English</a>", gmtUmlConfigurationFileName);
  printf ("<a class=\"dropdown-item\" href=\"gmtUmlGetUsers.cgi?gmtUmlLanguage=portuguese&gmtUmlConfigurationFileName=%s\"><img src=\"../images/pt-br.png\"> Portuguese</a>", gmtUmlConfigurationFileName);
  printf ("<a class=\"dropdown-item disabled\" href=\"#\"><img src=\"../images/de.png\"> German</a>");
  printf ("</div>");
  printf ("</div>");
  printf ("</div>");
  printf ("</nav>");

  printf ("<div class=\"container\">");
  printf ("<div class=\"card\">");
  printf ("<h2>%s</h2>", GmtUmlGetWebUserInterface (gmtUmlWebGetUsers, gmtUmlLanguage));
  printf ("<p>%s</p>", GmtUmlGetWebUserInterface (gmtUmlWebTextGetUsers, gmtUmlLanguage));

  printf ("<form class=\"form-inline form-filter\" method=\"POST\" action=\"gmtUmlGetUsers.cgi\">");
  printf ("<div class=\"form-group form-filter\">");
  printf ("<label for=\"inputName\" class=\"sr-only\">%s</label>", GmtUmlGetWebUserInterface (gmtUmlInputName, gmtUmlLanguage));
  printf ("<input type=\"text\" name=\"inputName\" class=\"form-control\" id=\"inputName\" placeholder=\"%s\">", GmtUmlGetWebUserInterface (gmtUmlInputName, gmtUmlLanguage));
  printf ("</div>");
  printf ("<div class=\"form-group form-filter\">");
  printf ("<input type=\"text\" name=\"inputEmail\" class=\"form-control\" id=\"inputEmail\" placeholder=\"%s\">", GmtUmlGetWebUserInterface (gmtUmlInputEmail, gmtUmlLanguage));
  printf ("<label for=\"inputEmail\" class=\"sr-only\">%s</label>", GmtUmlGetWebUserInterface (gmtUmlInputEmail, gmtUmlLanguage));
  printf ("</div>");
  printf ("<div class=\"form-group form-filter\">");
  printf ("<label for=\"inputProfile\" m class=\"sr-only\">%s</label>", GmtUmlGetWebUserInterface (gmtUmlInputProfile, gmtUmlLanguage));
  printf ("<input type=\"text\" name=\"inputProfile\" class=\"form-control\" id=\"inputProfile\" placeholder=\"%s\">", GmtUmlGetWebUserInterface (gmtUmlInputProfile, gmtUmlLanguage));
  printf ("</div>");
  printf ("<input type=\"hidden\" name=\"gmtUmlConfigurationFileName\" value=\"%s\">", gmtUmlConfigurationFileName);
  printf ("<input type=\"hidden\" name=\"gmtUmlLanguage\" value=\"%u\">", gmtUmlLanguage);
  printf ("<button type=\"submit\" class=\"btn btn-primary\">%s</button>", GmtUmlGetWebUserInterface (gmtUmlFilterButton, gmtUmlLanguage));
  printf ("</form>");

  printf ("<table class=\"table table-sm table-hover\">");
  printf ("<thead>");
  printf ("<tr>");
  printf ("<th scope=\"col\">#</th>");
  printf ("<th scope=\"col\">%s</th>", GmtUmlGetWebUserInterface (gmtUmlNameHeader, gmtUmlLanguage));
  printf ("<th scope=\"col\">%s</th>", GmtUmlGetWebUserInterface (gmtUmlEmailHeader, gmtUmlLanguage));
  printf ("<th scope=\"col\">%s</th>", GmtUmlGetWebUserInterface (gmtUmlProfileHeader, gmtUmlLanguage));
  printf ("</tr>");
  printf ("</thead>");
  printf ("<tbody>");

  if (filtering)
  {
    if ((gmtUmlValidation = GmtUmlSearchUsers (configurationOptions, gmtUmlNameFilter, gmtUmlEmailFilter, gmtUmlProfile, &gmtUmlUsersList)))
    {
      printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
      printf ("</tbody>");
      printf ("</table>");

      printf ("<br><a href=\"javascript:history.back()\" class=\"forgot-password\">%s</a>", GmtUmlGetWebUserInterface (gmtUmlBack, gmtUmlLanguage));
      printf ("</div>");
      printf ("</div>");

      printf ("<div class=\"footer\">");
      printf ("<a href=\"mailto:gabriel.tavora@poli.ufrj.br\">© 2017 Gabriel Montenegro Tavora.</a>");
      printf ("</div>");

      printf ("<script src=\"jquery-3.2.1.js\"></script>");
      printf ("<script src=\"bootstrap/js/bootstrap.bundle.min.js\"></script>");
      printf ("</body>");
      printf ("</html>");
      return gmtUmlOk;
    }
  }

  currentUser = gmtUmlUsersList;

  while (currentUser != NULL)
  {
    count++;
    printf ("<tr>");
    printf ("<th scope=\"row\">%i</th>", count);
    printf ("<td>%s</td>", currentUser->name);
    printf ("<td>%s</td>", currentUser->email);

    switch (currentUser->profile)
    {
      case 1:
      switch (gmtUmlLanguage)
      {
        default:
        case gmtUmlEnglish:
        printf ("<td>Main admin</td>");
        break;

        case gmtUmlPortuguese:
        printf ("<td>Admin principal</td>");
        break;
      }
      break;

      case 2:
      switch (gmtUmlLanguage)
      {
        default:
        case gmtUmlEnglish:
        printf ("<td>Admin</td>");
        break;

        case gmtUmlPortuguese:
        printf ("<td>Admin</td>");
        break;
      }
      break;

      case 4:
      switch (gmtUmlLanguage)
      {
        default:
        case gmtUmlEnglish:
        printf ("<td>User</td>");
        break;

        case gmtUmlPortuguese:
        printf ("<td>Usuario</td>");
        break;
      }
      break;
    }

    printf ("</tr>");
    currentUser = currentUser->next;
  }

  printf ("</tbody>");
  printf ("</table>");

  printf ("<br><a href=\"javascript:history.back()\" class=\"forgot-password\">%s</a>", GmtUmlGetWebUserInterface (gmtUmlBack, gmtUmlLanguage));
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
