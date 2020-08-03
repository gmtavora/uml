/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlGetPendingRegistrationRequests.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlGetPendingRegistrationRequests (gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - user's nickname (I);
 * gmtUmlUserDataType * - pointer to the first elementof the list containing the pending requests (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Prints all the valid registration requests.
 */

gmtUmlErrorType 
GmtUmlGetPendingRegistrationRequests (gmtUmlConfigurationOptionsType *, gmtUmlUserDataType **);

/* $RCSfile: gmtUmlGetPendingRegistrationRequests.h,v $ */