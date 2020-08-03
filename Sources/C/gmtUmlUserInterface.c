/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/11/15 02:35:47 $
 * $Log: gmtUmlUserInterface.c,v $
 * Revision 1.1  2017/11/15 02:35:47  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#include "gmtUmlUserInterface.h"

char *gmtUmlCliUserInterfaceMessages [gmtUmlLanguageAmount] [gmtUmlUserInterfaceMessageAmount] =
{
  {
    "Ok"
  },
  {
    "Sucesso"
  }
};

char *gmtUmlNcursesUserInterfaceMessages [gmtUmlLanguageAmount] [gmtUmlUserInterfaceMessageAmount] =
{
  {
    "Ok"
  },
  {
    "Sucesso"
  }
};

char *gmtUmlWebUserInterfaceMessages [gmtUmlLanguageAmount] [gmtUmlUserInterfaceMessageAmount] =
{
  {
    "Ok"
  },
  {
    "Sucesso"
  }
};

char * 
GmtUmlGetCliUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtUmlLanguageType)
{
  return gmtUmlCliUserInterfaceMessages [gmtUmlLanguageType] [gmtUmlUserInterfaceMessageNumberType];
}

char * 
GmtUmlGetNcursesUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtumlLanguageType)
{	
  return gmtUmlCliUserInterfaceMessages [gmtUmlLanguageType] [gmtUmlUserInterfaceMessageNumberType];
}

char * 
GmtUmlGetWebUserInterfaceMessage (gmtUmlUserInterfaceMessageNumberType, gmtUmlLanguageType)
{
  return gmtUmlCliUserInterfaceMessages [gmtUmlLanguageType] [gmtUmlUserInterfaceMessageNumberType];
}

/* $RCSfile: gmtUmlUserInterface.c,v $ */
