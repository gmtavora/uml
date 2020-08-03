/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlShowCliHelp.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#include "gmtUmlTypes.h"

 /*
 * gmtUmlErrorType
 * GmtUmlShowCliHelp (gmtUmlConfigurationOptionsType *, gmtUmlLanguageType);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the structure containing the configuration values (I);
 * gmtUmlLanguage - the current language (I);
 *
 * Returned code:
 * void
 *
 * Description:
 * Displays the CLI help messages.
 */

void
GmtUmlShowCliHelp (gmtUmlConfigurationOptionsType * configurationOptions, gmtUmlLanguageType language);