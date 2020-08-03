/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlAcceptInvite.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlAcceptInvite (gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - the temp password (I);
 * gmtUmlUserDataType * - the user data struct (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Accept invitation.
 */

gmtUmlErrorType 
GmtUmlAcceptInvite (gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *); 

 /* $RCSfile: gmtUmlAcceptInvite.h,v $ */