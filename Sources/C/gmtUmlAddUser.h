/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlAddUser.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#ifndef _GMTUMLADDUSER_H
#define _GMTUMLADDUSER_H "@(#)gmtUmlAddUser.h $Revision: 1.1 $"

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"

 /*
 * gmtUmlErrorType
 * GmtUmlAddUser (gmtUmlConfigurationOptionsType *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the structure containing the configuration values (I);
 * gmtUmlUserDataType * - the structure containing the new user data (I);
 *
 * Returned code:
 * gmtUmlOk - success;
 * gmtUmlErrorInvalidUserData - the user data is a null pointer;
 * gmtUmlErrorUsersFileExists - cannot create another user with profile 0;
 * gmtUmlErrorInvalidProfile - to create a new file, the new user profile must be 0;
 * gmtUmlErrorCreatingTempFile - could not create temp file;
 * gmtUmlErrorCorruptedUserFile - the user file is corrupted;
 * gmtUmlErrorSendingEmail - could not send email;
 *
 * Description:
 * Adds a new user to the system.
 */

gmtUmlErrorType
GmtUmlAddUser (gmtUmlConfigurationOptionsType *gmtUmlConfiguration, gmtUmlUserDataType *gmtUmlUserData);

#endif

/* $RCSfile: gmtUmlAddUser.h,v $ */