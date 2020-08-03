/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlSearchUsers.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlSearchUsers (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlProfileType, gmtUmlUserDataType **);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - name or part of the name (I);
 * char * - email or part of email (I);
 * gmtUmlProfileType - profile (I);
 * gmtUmlUserDataType ** - the user data threaded list (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * This function can be used by anyone to search another user's information.
 */

gmtUmlErrorType 
GmtUmlSearchUsers (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlUserProfileType, gmtUmlUserDataType **);

 /* $RCSfile: gmtUmlSearchUsers.h,v $ */