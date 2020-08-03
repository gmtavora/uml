/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author$
 * $Date$
 * $Log$
 *
 */

#ifndef _GMTUMLVERIFYLOGIN_H
#define _GMTUMLVERIFYLOGIN_H "@(#)gmtUmlVerifyLogin.h $Revision$"

#include "gmtUmlErrors.h"
#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlVerifyLogin (gmtUmlConfigurationOptionsType *, gmtUmlLanguageType, gmtUmlUserIdentifierType, char *)
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the configuration options (I)
 * gmtUmlLanguageType - the language (I)
 * gmtUmlUserIdentifierType - the user id (I)
 * char * - the address to go to, in case of success (I)
 *
 * Returned code:
 *
 * Description:
 * Verify if the user is logged in.
 */

gmtUmlErrorType
GmtUmlVerifyLogin (gmtUmlConfigurationOptionsType *, gmtUmlLanguageType, gmtUmlUserIdentifierType);

#endif

/* $RCSfile$ */
