/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlCgiMain.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
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

int
main (int argc, char **argv)
{
  char gmtUmlConfigurationFileName [GMT_UML_MAX_FILE_NAME_LENGTH+1];
  char gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH+1];
  unsigned gmtUmlValidation;
  environmentType gmtUmlEnvironment;
  gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
  
  memset (gmtUmlConfigurationFileName, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH+1);
  memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH+1);
  
  if (mlCgiInitialize(&gmtUmlEnvironment))
    exit (ML_CGI_OK);
  
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
    
    exit (gmtUmlErrorInvalidEnvironment);
  }
  
  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlConfigurationFileName", gmtUmlConfigurationFileName, GMT_UML_MAX_FILE_NAME_LENGTH+1)))
  {
    strcpy (gmtUmlConfigurationFileName, GMT_UML_DEFAULT_CONFIG_FILE);
  }
  
  if ((gmtUmlValidation = mlCgiGetFormStringNoNewLines ("gmtUmlLanguage", gmtUmlLanguageName, GMT_UML_MAX_FILE_NAME_LENGTH + 1)))
  {
    strcpy (gmtUmlLanguageName, "english");
  }
  
  gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);
  
  /* HTML HEADER */
  
  mlCgiBeginHttpHeader ("text/html");
  mlCgiEndHttpHeader ();
  
  /* HTML BODY */
  
  printf ("<!DOCTYPE html>");
printf ("<html>");
printf ("<head>");
printf ("	<meta charset=\"utf-8\">");
printf ("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">");
printf ("	<link rel=\"icon\" href=\"favicon.ico\">");
printf ("	<link rel=\"stylesheet\" type=\"text/css\" href=\"bootstrap/css/bootstrap.min.css\">");
printf ("	<link rel=\"stylesheet\" href=\"style.css\">");
printf ("	<title>%s</title>", GmtUmlGetWebUserInterface (gmtUmlPageTitle, gmtUmlLanguage));
printf ("</head>");
printf ("<body>");
printf ("	<nav class=\"navbar navbar-expand-lg navbar-light bg-light\">");
printf ("	  <a class=\"navbar-brand\" href=\"/~gabriel.tavora/index.html\">%s</a>", GmtUmlGetWebUserInterface (gmtUmlProjectName, gmtUmlLanguage));
printf ("	  <button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#navbarNavAltMarkup\" aria-controls=\"navbarNavAltMarkup\" aria-expanded=\"false\" aria-label=\"Toggle navigation\">");
printf ("	  	<span class=\"navbar-toggler-icon\"></span>");
printf ("	  </button>");
printf ("	  <div class=\"collapse navbar-collapse\" id=\"navbarNavAltMarkup\">");
printf ("	    <div class=\"navbar-nav\">");
printf ("	    	<a class=\"nav-item nav-link\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlHome, gmtUmlLanguage));
printf ("	    	<a class=\"nav-item nav-link\" href=\"gmtUmlShowRequestRegistrationForm.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlRegister, gmtUmlLanguage));
printf ("	    	<a class=\"nav-item nav-link\" href=\"gmtUmlShowRequestPasswordResetForm.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlResetPassword, gmtUmlLanguage));
printf ("	    	<a class=\"nav-item nav-link\" href=\"gmtUmlShowWebHelp.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlHelp, gmtUmlLanguage));
printf ("	    	<a class=\"nav-item nav-link\" href=\"gmtUmlShowLicense.cgi?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlLicense, gmtUmlLanguage));
printf ("    		<div class=\"nav-item dropdown\">");
printf ("	    		<a class=\"nav-link dropdown-toggle\" href=\"#\" id=\"navbarDropdown\" role=\"button\" data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">");
printf ("     				%s", GmtUmlGetWebUserInterface (gmtUmlLanguageSelect, gmtUmlLanguage));
printf ("    			</a>");
printf ("    			<div class=\"dropdown-menu\" aria-labelledby=\"navbarDropdown\">");
printf ("	      			<a class=\"dropdown-item\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=english&gmtUmlConfigurationFileName=%s\"><img src=\"/~gabriel.tavora/images/en-us.png\"> English</a>", gmtUmlConfigurationFileName);
printf ("      				<a class=\"dropdown-item\" href=\"gmtUmlMain.cgi?gmtUmlLanguage=portuguese&gmtUmlConfigurationFileName=%s\"><img src=\"/~gabriel.tavora/images/pt-br.png\"> Portuguese</a>", gmtUmlConfigurationFileName);
printf ("      				<a class=\"dropdown-item disabled\" href=\"#\"><img src=\"/~gabriel.tavora/images/de.png\"> German</a>");
printf ("      			</div>");
printf ("	    </div>");
printf ("	  </div>");
printf ("	</nav>");

/* Content */

printf ("	<div class=\"container\">");
printf ("		<div class=\"card card-container\">");
printf ("			<img id=\"profile-img\" class=\"profile-img-card\" src=\"http://ssl.gstatic.com/accounts/ui/avatar_2x.png\" />");
printf ("	        <p id=\"profile-name\" class=\"profile-name-card\"></p>");
printf ("			<form class=\"form-signin\" method=\"POST\" action=\"gmtUmlLogin.cgi\">");
printf ("				<h2 class=\"form-signin-heading\">%s</h2>", GmtUmlGetWebUserInterface (gmtUmlLogin, gmtUmlLanguage));
printf ("				<label for=\"inputNickname\" class=\"sr-only\">%s</label>", GmtUmlGetWebUserInterface (gmtUmlUsername, gmtUmlLanguage));
printf ("				<input type=\"text\" name=\"nickname\" id=\"inputNickname\" class=\"form-control\" placeholder=\"%s\" required autofocus>", GmtUmlGetWebUserInterface (gmtUmlUsername, gmtUmlLanguage));
printf ("				<label for=\"inputPassword\" class=\"sr-only\">%s</label>", GmtUmlGetWebUserInterface (gmtUmlPassword, gmtUmlLanguage));
printf ("				<input type=\"password\" name=\"password\" id=\"inputPassword\" class=\"form-control\" placeholder=\"%s\" required>", GmtUmlGetWebUserInterface (gmtUmlPassword, gmtUmlLanguage));
printf ("				<div class=\"checkbox\">");
printf ("					<label>");
printf ("						<input type=\"checkbox\" value=\"remember-me\"> %s", GmtUmlGetWebUserInterface (gmtUmlRememberMe, gmtUmlLanguage));
printf ("					</label>");
printf ("				</div>");
printf ("				<input type=\"hidden\" name=\"gmtUmlConfigurationFileName\" value=\"%s\">", gmtUmlConfigurationFileName);
printf ("				<input type=\"hidden\" name=\"gmtUmlLanguage\" value=\"%ul\">", gmtUmlLanguage);
printf ("				<button class=\"btn btn-lg btn-primary btn-block btn-signin\" type=\"submit\">%s</button>", GmtUmlGetWebUserInterface (gmtUmlLogin, gmtUmlLanguage));
printf ("			</form>");
printf ("			<a href=\"forgot-password.html?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\" class=\"forgot-password\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlForgotPassword, gmtUmlLanguage));
printf ("			<a href=\"registration.html?gmtUmlLanguage=%s&gmtUmlConfigurationFileName=%s\" class=\"forgot-password\">%s</a>", gmtUmlLanguageName, gmtUmlConfigurationFileName, GmtUmlGetWebUserInterface (gmtUmlRegister, gmtUmlLanguage));
printf ("		</div>");
printf ("	</div>");
printf ("	<div class=\"footer\">");
printf ("		<a href=\"mailto:gabriel.tavora@poli.ufrj.br\">© 2017 Gabriel Montenegro Tavora.</a>");
printf ("	</div>");
printf ("	<script src=\"jquery-3.2.1.js\"></script>");
printf ("	<script src=\"bootstrap/js/bootstrap.bundle.min.js\"></script>");
printf ("</body>");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile: gmtUmlCgiMain.c,v $ */
