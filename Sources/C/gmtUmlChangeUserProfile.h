/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlChangeUserProfile.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlChangeUserProfile (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlUserProfileType);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - the admin nickname (I);
 * char * - the user nickname (I);
 * gmtUmlUserProfileType - the new profile (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * This function can be used by an administrator to change another user's profile. However, the user number 0 cannot have
 * his profile changed, also an administrator with at least 1 request.
 */

gmtUmlErrorType 
GmtUmlChangeUserProfile (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlUserProfileType);

 /* $RCSfile: gmtUmlChangeUserProfile.h,v $ */