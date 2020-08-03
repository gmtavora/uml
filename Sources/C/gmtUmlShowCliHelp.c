/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlShowCliHelp.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#include<stdio.h>

#include "gmtUmlTypes.h"

 /*
 * gmtUmlErrorType
 * GmtUmlShowCliHelp (gmtUmlConfigurationOptionsType *, gmtUmlLanguageType);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the structure containing the configuration values (I);
 * gmtUmlLanguage - the current language (I);
 *
 * Returned code:
 * void
 *
 * Description:
 * Displays the CLI help messages.
 */


void
GmtUmlShowCliHelp (gmtUmlConfigurationOptionsType * configurationOptions, gmtUmlLanguageType language)
{ 
  switch (language)
  {
    default:
    case gmtUmlEnglish:
      printf ("\nTo display this information in other language, type language=value.\n\n");
      printf ("Option\t\t\tAction\n\n");
      printf ("-h | --help\t\tDisplays the help.\n");
      printf ("-N | --Ncurses\t\tRun Ncurses interface.\n");
      printf ("-C | --configure\tCreate user\'s files.\n");
      printf ("-a | --add\t\tAdd user.\n");
      printf ("-i | --invite\t\tInvite user.\n");
      printf ("-t | --accept\t\tAccept invitation.\n");
      printf ("-j | --reject\t\tReject invitation.\n");
      printf ("-n | --new\t\tRequest registration.\n");
      printf ("-q | --request\t\tGet pending registration requests per user.\n");
      printf ("-Q | --Request\t\tGet pending registration requests.\n");
      printf ("-v | --approve\t\tApprove registration request.\n");
      printf ("-d | --disapprove\tDisapprove registration request.\n");
      printf ("-U | --Unlocking\tGet unlocking requests.\n");
      printf ("-l | --lock\t\tLock user account.\n");
      printf ("-u | --unlock\t\tUnlock user account.\n");
      printf ("-p | --password\t\tChange user password.\n");
      printf ("-r | --reset\t\tReset user password.\n");
      printf ("-m | --modify\t\tChange user name.\n");
      printf ("-e | --edit\t\tChange user email.\n");
      printf ("-c | --confirm\t\tConfirm email change.\n");
      printf ("-g | --group\t\tChange user profile.\n");
      printf ("-s | --show\t\tGet user informations.\n");
      printf ("-S | --Search\t\tSearch user.\n\n");
    break;
    
    case gmtUmlPortuguese:
      printf ("\nOpcao\t\t\tAcao\n\n");
      printf ("-h | --help\t\tExibir ajuda.\n");
      printf ("-N | --Ncurses\t\tExecutar interface Ncurses.\n");
      printf ("-C | --configure\tCria os arquivos de usuarios.\n");
      printf ("-a | --add\t\tAdicionar usuario.\n");
      printf ("-i | --invite\t\tConvidar usuario.\n");
      printf ("-t | --accept\t\tAceitar convite.\n");
      printf ("-j | --reject\t\tRejeitar convite.\n");
      printf ("-n | --new\t\tSolicitar cadastro.\n");
      printf ("-q | --request\t\tVerificar solicitacoes de cadastro para determinado usuario.\n");
      printf ("-Q | --Request\t\tVerificar todas as solicitacoes de cadastro.\n");
      printf ("-v | --approve\t\tAprovar solicitacao de cadastro.\n");
      printf ("-d | --disapprove\tRejeitar solicitacao de cadastro.\n");
      printf ("-U | --Unlocking\tVerificar pedidos de desbloqueio de usuario.\n");
      printf ("-l | --lock\t\tBloquear usuario.\n");
      printf ("-u | --unlock\t\tDesbloquear usuario.\n");
      printf ("-p | --password\t\tTrocar senha de usuario.\n");
      printf ("-r | --reset\t\tResetar senha de usuario.\n");
      printf ("-m | --modify\t\tModificar nome de usuario\n");
      printf ("-e | --edit\t\tModificar email de usuario.\n");
      printf ("-c | --confirm\t\tConfirmar mudanca de email.\n");
      printf ("-g | --group\t\tModificar perfil de usuario.\n");
      printf ("-s | --show\t\tObter informacoes de usuario.\n");
      printf ("-S | --Search\t\tBuscar usuario.\n\n");
    break;
  }
}