/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlChangeUserPassword.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlChangeUserPassword (gmtUmlConfigurationOptionsType *, char *, char*, char *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - administrator's nickname (I);
 * char * - user's nickname (I);
 * char * - current password (I);
 * char * - new password (I);
 * char * - new password confirmation (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Changes user's password. An administrator can change any user's password. When used by admin, his nickname needs to be
 * informed, otherwise the argument can be NULL.
 */

gmtUmlErrorType 
GmtUmlChangeUserPassword (gmtUmlConfigurationOptionsType *, char *, char*, char *, char *, char *); 

 /* $RCSfile: gmtUmlChangeUserPassword.h,v $ */