/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlRequestRegistration.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlRequestRegistration(gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - email of the user responsible for the verification (I);
 * gmtUmlUserDataType * - pointer to the struct containing the new user's information (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Requests a new registration.
 */

gmtUmlErrorType 
GmtUmlRequestRegistration(gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);

/* $RCSfile: gmtUmlRequestRegistration.h,v $ */