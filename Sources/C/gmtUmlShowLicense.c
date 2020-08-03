/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlShowLicense.c,v $
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
printf ("	      			<a class=\"dropdown-item\" href=\"gmtUmlShowLicense.cgi?gmtUmlLanguage=english&gmtUmlConfigurationFileName=%s\"><img src=\"/~gabriel.tavora/images/en-us.png\"> English</a>", gmtUmlConfigurationFileName);
printf ("      				<a class=\"dropdown-item\" href=\"gmtUmlShowLicense.cgi?gmtUmlLanguage=portuguese&gmtUmlConfigurationFileName=%s\"><img src=\"/~gabriel.tavora/images/pt-br.png\"> Portuguese</a>", gmtUmlConfigurationFileName);
printf ("      				<a class=\"dropdown-item disabled\" href=\"#\"><img src=\"/~gabriel.tavora/images/de.png\"> German</a>");
printf ("      			</div>");
printf ("	    </div>");
printf ("	  </div>");
printf ("	</nav>");

/* Content */
printf ("	<div class=\"container\">");
printf ("		<div class=\"card content\">");

switch (gmtUmlLanguage)
{
  default:
  case gmtUmlEnglish:
    printf ("			<h4>Creative Commons License - CC BY 4.0</h4>");
    printf ("			<p>You are free to share, copy and redistribute the material in any medium or format, adapt, remix, transform, and build upon the material");
    printf ("for any purpose, even commercially. You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.</p>");
    printf ("			<p>*This work is licensed under some Bootstrap, jQuery and FlatIcon (for some images) conditions. Take a look in their license before copy or reuse the code in your works.</p>");
    printf ("			<a href=\"https://creativecommons.org/licenses/by/4.0/\" class=\"forgot-password\">Attribution 4.0 International (CC BY 4.0)</a>");
    printf ("			<a href=\"javascript:history.back()\" class=\"forgot-password\">Back</a>");
  break;
  
  case gmtUmlPortuguese:
    printf ("			<h4>Licenca Creative Commons - CC BY 4.0</h4>");
    printf ("			<p>Voce esta livre para compartilhar, copiar e redistribuir o material sob qualquer meio ou formato, adaptar, transformar e construir a partir  dele");
    printf ("para quaisquer propositos, ate comerciais. Voce precisa dar os creditos apropriados, prover um link para a licenca, e indicar se mudancas tiverem sido feitas. Voce pode faze-lo de qualquer modo, mas nao de forma a sugerir que o licenciante endosse seu uso.</p>");
    printf ("			<p>*Este trabalho esta licenciado sob algumas condicoes de Bootstrap, jQuery e FlatIcon (em relacao a alguns icones). Leia suas licencas antes de copiar ou reutilizar este codigo nos seus trabalhos.</p>");
    printf ("			<a href=\"https://creativecommons.org/licenses/by/4.0/\" class=\"forgot-password\">Attribution 4.0 International (CC BY 4.0)</a>");
    printf ("			<a href=\"javascript:history.back()\" class=\"forgot-password\">Retornar</a>");
  break;
}

printf ("		</div>");
printf ("	</div>");
printf ("	<div class=\"footer\">");
printf ("		<a href=\"mailto:gabriel.tavora@poli.ufrj.br\">� 2017 Gabriel Montenegro Tavora.</a>");
printf ("	</div>");
printf ("	<script src=\"jquery-3.2.1.js\"></script>");
printf ("	<script src=\"bootstrap/js/bootstrap.bundle.min.js\"></script>");
printf ("</body>");

  mlCgiFreeResources ();
  return ML_CGI_OK;
}

/* $RCSfile: gmtUmlShowLicense.c,v $ */
