/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlWebUserInterface.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 */

#ifndef _GMTUMLWEBUSERINTERFACE_H
#define _GMTUMLWEBUSERINTERFACE_H "@(#)gmtUmlWebUserInterface.h $Revision: 1.1 $"

#include "gmtUmlTypes.h"

typedef enum
{
	gmtUmlPageTitle,
	gmtUmlProjectName,
	gmtUmlResetPassword,
	gmtUmlHelp,
	gmtUmlLicense,
	gmtUmlUsername,
	gmtUmlPassword,
	gmtUmlRememberMe,
	gmtUmlForgotPassword,
	gmtUmlRegister,
	gmtUmlHome,
	gmtUmlLogin,
  gmtUmlLanguageSelect,
  gmtUmlEmail,
  gmtUmlBack,
  gmtUmlFullName,
  gmtUmlConfirmPassword,
  gmtUmlYourEmail,
  gmtUmlConfirmYourEmail,
  gmtUmlFriendEmail,
  gmtUmlAcceptTermsOfUse,
	gmtUmlHello,
	gmtUmlSelectOption,
	gmtUmlWebAddUser,
	gmtUmlWebInviteUser,
	gmtUmlWebRegistrationRequests,
	gmtUmlWebLockUser,
	gmtUmlWebUnlockUser,
	gmtUmlWebResetUserPassword,
	gmtUmlWebChangeUserPassword,
	gmtUmlWebChangeUserName,
	gmtUmlWebChangeUserEmail,
	gmtUmlWebChangeUserProfile,
	gmtUmlWebGetUsers,
	gmtUmlWebLogout,
	gmtUmlWebTextAddUser,
	gmtUmlEmailConfirmation,
	gmtUmlNameConfirmation,
	gmtUmlPasswordConfirmation,
	gmtUmlProfile,
	gmtUmlUserProfile,
	gmtUmlAdminProfile,
	gmtUmlReset,
	gmtUmlWebTextInviteUser,
	gmtUmlWebTextRegistrationRequests,
	gmtUmlInputNickname,
	gmtUmlFilterButton,
	gmtUmlNameHeader,
	gmtUmlEmailHeader,
	gmtUmlFriendNicknameHeader,
	gmtUmlWebTextResetUserPassword,
	gmtUmlWebTextChangeUserEmail,
	gmtUmlInputNewEmail,
	gmtUmlInputNewName,
	gmtUmlWebTextChangeName,
	gmtUmlWebTextChangeUserProfile,
	gmtUmlInputNewPassword,
	gmtUmlWebTextChangeUserPassword,
	gmtUmlInputName,
	gmtUmlInputEmail,
	gmtUmlInputProfile,
	gmtUmlWebTextGetUsers,
	gmtUmlProfileHeader,
	gmtUmlWebUsersPanel,
	gmtUmlWebAdminsPanel,
	gmtUmlUIMessageAmount
} gmtUmlMessageType;

char *
GmtUmlGetWebUserInterface (gmtUmlMessageType, gmtUmlLanguageType);

#endif

/* $RCSfile: gmtUmlWebUserInterface.h,v $ */
