/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlCliUserInterface.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 */

#ifndef _GMTUMLCLIUSERINTERFACE_H
#define _GMTUMLCLIUSERINTERFACE_H "@(#)gmtUmlCliUserInterface.h $Revision: 1.1 $"

#include "gmtUmlTypes.h"

typedef enum
{
  gmtUmlInformYourPassword,
  gmtUmlConfirmYourPassword,
  gmtUmlAccountCreatedSuccessfully,
  gmtUmlPermissionDenied,
  gmtUmlYourNicknameIs,
  gmtUmlNewUserNicknameIs,
  gmtUmlInformNewUsersPassword,
  gmtUmlConfirmNewUsersPassword,
  gmtUmlInformYourNickname,
  gmtUmlUserInvitedSuccessfully,
  gmtUmlCliSearchResults,
  gmtUmlInvitationRejected,
  gmtUmlCliAllUsers,
  gmtUmlInformNewPassword,
  gmtUmlConfirmNewPassword,
  gmtUmlUserPasswordChanged,
  gmtUmlWelcome,
  gmtUmlRequestRegistered,
  gmtUmlUserPendingRegistrationRequests,
  gmtUmlResults,
  gmtUmlTotal,
  gmtUmlRegistrationRequestApproved,
  gmtUmlRegistrationRequestDisapproved,
  gmtUmlCliMessageAmount
} gmtUmlCliMessageType;

char *
GmtUmlGetCliUserInterface (gmtUmlCliMessageType, gmtUmlLanguageType);

#endif