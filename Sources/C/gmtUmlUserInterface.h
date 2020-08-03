/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/11/15 02:35:47 $
 * $Log: gmtUmlUserInterface.h,v $
 * Revision 1.1  2017/11/15 02:35:47  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#ifndef _GMTUMLUSERINTERFACE_H
#define _GMTUMLUSERINTERFACE_H "@(#)gmtUmlUserInterface.h $Revision: 1.1 $"

typedef enum {gmtUmlUserInterfaceMessageAmount} gmtUmlUserInterfaceMessageNumberType;

char * 
GmtUmlGetCliUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtUmlLanguageType); 

char * 
GmtUmlGetNcursesUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtumlLanguageType); 

char * 
GmtUmlGetWebUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtUmlLanguageType); 

#endif  
