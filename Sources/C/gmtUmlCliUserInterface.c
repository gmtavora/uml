/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlCliUserInterface.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 */

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlCliUserInterface.h"

char * gmtUmlCliMessages [gmtUmlLanguageAmount][gmtUmlCliMessageAmount] =
{
  {
    "Inform your password: ",
    "Confirm your password: ",
    "Account created successfully!",
    "Permission denied.",
    "Your nickname is:",
    "The new user\'s nickname is:",
    "Inform the new user\'s password:",
    "Confirm the new user\'s password:",
    "Inform your nickname: ",
    "User invited successfully!",
    "Search results:",
    "Invitation rejected successfully",
    "Users list:",
    "Inform the new password: ",
    "Confirm the new password: ",
    "User\'s password changed successfully.",
    "Invitation accepted!",
    "Request registered successfully!",
    "Pending registration requests for",
    "Result(s)",
    "Total",
    "Registration request successfully approved!",
    "Registration request successfully disapproved."
  },
  {
    "Digite sua senha: ",
    "Confirme sua senha: ",
    "Conta criada com sucesso!",
    "Permissao negada.",
    "Seu apelido e:",
    "O apelido do novo usuario e:",
    "Informe a senha do novo usuario:",
    "Confirme a senha do novo usuario:",
    "Informe seu apelido: ",
    "Usuario convidado com sucesso!",
    "Resultados da pesquisa:",
    "Convite rejeitado com exito",
    "Lista de usuarios:",
    "Informe a nova senha: ",
    "Confirme a nova senha: ",
    "Senha alterada com exito.",
    "Convite aceito!",
    "Solicitacao de registro enviada com sucesso!",
    "Solicitacoes de registro para",
    "Resultado(s)",
    "Total",
    "Pedido de registro aprovado com exito!",
    "Pedido de registro nao aprovado."
  }
};

char *
GmtUmlGetCliUserInterface (gmtUmlCliMessageType gmtUmlMessage, gmtUmlLanguageType gmtUmlLanguage)
{
  return gmtUmlCliMessages [gmtUmlLanguage] [gmtUmlMessage];
}