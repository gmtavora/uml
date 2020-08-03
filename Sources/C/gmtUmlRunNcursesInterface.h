/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlRunNcursesInterface.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 */
 
#include<ncurses.h> 

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"
 
 /*
  * gmtUmlErrorType
  * GmtUmlRunNcursesInterface (gmtUmlConfigurationOptionsType *, char *, gmtUmlLanguageType)
  *
  * Arguments:
  * gmtUmlConfigurationOptionsType * - the current configuration options (I);
  * char * - the user nickname (I);
  * gmtUmlLanguageType - the current language;
  *
  * Returned code:
  * gmtUmlOk - success;
  * 
  */

gmtUmlErrorType
GmtUmlRunNcursesInterface (gmtUmlConfigurationOptionsType *, char *, gmtUmlLanguageType);

WINDOW
*gmtUmlNcursesCreateNewWindow (int, int, int, int);

void
gmtUmlNcursesDestroyWindow (WINDOW *);

/* $RCSfile: gmtUmlRunNcursesInterface.h,v $ */