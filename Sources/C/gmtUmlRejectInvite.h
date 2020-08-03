/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlRejectInvite.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlRejectInvite (gmtUmlConfigurationOptionsType *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * gmtUmlUserDataType * - the user's informations (I);
 * char * - the temp password (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Reject invitation.
 */

gmtUmlErrorType 
GmtUmlRejectInvite (gmtUmlConfigurationOptionsType *, gmtUmlUserDataType *, char *); 

 /* $RCSfile: gmtUmlRejectInvite.h,v $ */