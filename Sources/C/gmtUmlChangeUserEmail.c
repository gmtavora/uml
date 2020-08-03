/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlChangeUserEmail.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlConfig.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlAcceptInvite.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlChangeUserEmail.h"

/*
 * gmtUmlErrorType
 * GmtUmlChangeUserEmail (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlUserProfileType);
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
GmtUmlChangeUserProfile (gmtUmlConfigurationOptionsType *gmtUmlConfiguration, char *gmtUmlAdminNickname, char *gmtUmlUserNickname, gmtUmlUserProfileType gmtUmlNewProfile)
{
  gmtUmlUserDataType *gmtUmlUsersList, *gmtUmlUser;
  gmtUmlErrorType gmtUmlValidation;
  boolean found = False;

  if ((gmtUmlAdminNickname == NULL) || (gmtUmlUserNickname == NULL))
    return gmtUmlErrorNullPointer;

  if (gmtUmlConfiguration == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, gmtUmlConfiguration);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, gmtUmlConfiguration)))
    return gmtUmlValidation;

  gmtUmlUser = gmtUmlUsersList;

  while (gmtUmlUser != NULL)
  {
    if (!strcmp (gmtUmlUserNickname, gmtUmlUser->nickname))
    {
      found = True;
      break;
    }
  }

  if (!found)
    return gmtUmlErrorUserNotFound;

  gmtUmlUsers->profile = gmtUmlNewProfile;

  GmtUmlWriteUsersFile (gmtUmlUsersList, gmtUmlConfiguration);

  return gmtUmlOk;
}

 /* $RCSfile: gmtUmlChangeUserEmail.c,v $ */