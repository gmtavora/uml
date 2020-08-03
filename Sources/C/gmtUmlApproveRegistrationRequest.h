/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlApproveRegistrationRequest.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlApproveRegistrationRequests (gmtUmlConfigurationOptionsType *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - friend's nickname (I);
 * char * - user's nickname (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Approves a registration request.
 */

gmtUmlErrorType 
GmtUmlApproveRegistrationRequest (gmtUmlConfigurationOptionsType *configurationOptions, char *friendNickname, char *userNickname);

/* $RCSfile: gmtUmlApproveRegistrationRequest.h,v $ */