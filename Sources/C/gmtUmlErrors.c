/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlErrors.c,v $
 * Revision 1.3  2017/12/21 22:04:50  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.2  2017/11/22 21:57:10  gabriel.tavora
 * Aula 1.1 finalizada.
 *
 * Revision 1.1  2017/11/15 02:19:45  gabriel.tavora
 * Initial revision
 *
 *
 */

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"

char * gmtUmlCliErrorMessages [gmtUmlLanguageAmount] [gmtUmlErrorAmount] =
{
  {
    "Ok",
    "The function is trying to use a null pointer",
    "Invalid file path",
    "Invalid file name",
    "The function is trying to use an invalid length",
    "The string length is not valid",
    "The string contains an invalid character",
    "Invalid username",
    "Invalid email",
    "Invalid name",
    "Invalid encryption algorithm",
    "Invalid password",
    "Invalid salt",
    "Unsupported algorithm",
    "Passwords don\'t match",
    "Invalid configuration option",
    "Invalid user id",
    "Null argument",
    "Invalid language",
    "Invalid argument",
    "Invalid configuration file",
    "Invalid user",
    "User names don\'t match.",
    "Emails don\'t match.",
    "Too few arguments",
    "Invalid profile",
    "Invalid friend email",
    "Invalid nickname",
    "Incorrect environment",
    "Could not open file",
    "Invalid user data",
    "Users file already exists",
    "Could not create temporary file",
    "Could not allocate memory",
    "The user file is corrupted.",
    "Invalid project name",
    "Could not send email",
    "Option not supported",
    "Invalid key",
    "Argument set twice",
    "Cannot create nickname",
    "User not found",
    "Incorrect password",
    "Could not create configuration file",
    "Permission denied",
    "There are no invitations",
    "The invited users file is corrupted",
    "Invitation not found",
    "The invitation expired",
    "Nickname already exists",
    "Email already exists",
    "The system has been configured already",
    "The system is not configured",
    "User still awaiting for approval",
    "There is no registration request pending",
    "Request not found",
    "Friend not found",
    "Administrator not found",
    "You are not logged in",
    "Invalid cookie",
    "Cookie doesn\'t exist",
    "Cannot open cookie file",
    "Corrupted cookie file",
    "Expired cookie",
    "Incorrect cookie"
  },
  {
    "Sucesso",
    "A funcao esta tentando usar um ponteiro nulo",
    "Diretorio invalido",
    "Nome de arquivo invalido",
    "O comprimento informado e invalido",
    "A string possui comprimento nao permitido",
    "A string possui caractere invalido",
    "Nome de usuario invalido",
    "Email invalido",
    "Nome invalido",
    "Algoritmo de codificacao invalido",
    "Senha Invalida",
    "Salt invalido",
    "Algoritmo de codificacao nao suportado",
    "As senhas nao conferem",
    "Opcao de configuracao invalida",
    "Id de usuario invalida",
    "Argumento nulo",
    "Idioma invalido",
    "Argumento invalido",
    "Arquivo de configuracao invalido",
    "Usuario invalido",
    "Nomes de usuario nao correspondem",
    "Emails nao correspondem",
    "Numero insuficiente de argumentos",
    "Perfil invalido",
    "Email de amigo invalido",
    "Nickname invalido",
    "Ambiente incorreto",
    "Nao foi possivel abrir arquiv",
    "Dados de usuario invalidos",
    "Arquivo de usuarios ja existe",
    "Nao foi possivel criar arquivo temporario",
    "Nao foi possivel alocar memoria",
    "O arquivo de dados de usuario esta corrompido",
    "Nome de projeto invalido",
    "Nao foi possivel enviar email",
    "Opcao nao suportada",
    "Chave invalida",
    "Argumento definido duas vezes",
    "Nao foi possivel criar apelido",
    "Usuario nao encontrado",
    "Senha incorreta",
    "Nao foi possivel criar arquivo de configuracao",
    "Permissao negada",
    "Nao ha nenhum convite",
    "O arquivo de usuarios convidados esta corrompido",
    "Convite nao encontrado",
    "O convite expirou",
    "Este apelido ja existe",
    "Este email ja esta cadastrado",
    "O sistema ja foi configurado",
    "Sistema nao configurado",
    "Usuario aguardando aprovacao",
    "Nao ha nenhuma solicitacao de registro",
    "Solicitacao nao encontrada",
    "Amigo nao encontrado",
    "Administrador nao encontrado",
    "Voce nao esta logado",
    "Cookie invalido",
    "Cookie nao existe",
    "Nao foi possivel abrir arquivo de cookie",
    "Arquivo de cookie corrompido",
    "Cookie expirou",
    "Cookie incorreto"
  }
};

char * gmtUmlNcursesErrorMessages [gmtUmlLanguageAmount] [gmtUmlErrorAmount] =
{
  {
    "Ok",
    "The function is trying to use a null pointer",
    "Invalid file path",
    "Invalid file name",
    "The function is trying to use an invalid length",
    "The string length is not valid",
    "The string contains an invalid character",
    "Invalid username",
    "Invalid email",
    "Invalid name",
    "Invalid encryption algorithm",
    "Invalid password",
    "Invalid salt",
    "Unsupported algorithm",
    "Passwords don\'t match",
    "Invalid configuration option",
    "Invalid user id",
    "Null argument",
    "Invalid language",
    "Invalid argument",
    "Invalid configuration file",
    "Invalid user",
    "User names don\'t match.",
    "Emails don\'t match.",
    "Too few arguments",
    "Invalid profile",
    "Invalid friend email",
    "Invalid nickname",
    "Incorrect environment",
    "Could not open file",
    "Invalid user data",
    "Users file already exists",
    "Could not create temporary file",
    "Could not allocate memory",
    "The user file is corrupted.",
    "Invalid project name",
    "Could not send email",
    "Option not supported",
    "Invalid key",
    "Argument set twice",
    "Cannot create nickname",
    "User not found",
    "Incorrect password",
    "Could not create configuration file",
    "Permission denied",
    "There are no invitations",
    "The invited users file is corrupted",
    "Invitation not found",
    "The invitation expired",
    "Nickname already exists",
    "Email already exists",
    "The system has been configured already",
    "The system is not configured",
    "User still awaiting for approval",
    "There is no registration request pending",
    "Request not found",
    "Friend not found",
    "Administrator not found"
  },
  {
    "Sucesso",
    "A funcao esta tentando usar um ponteiro nulo",
    "Diretorio invalido",
    "Nome de arquivo invalido",
    "O comprimento informado e invalido",
    "A string possui comprimento nao permitido",
    "A string possui caractere invalido",
    "Nome de usuario invalido",
    "Email invalido",
    "Nome invalido",
    "Algoritmo de codificacao invalido",
    "Senha Invalida",
    "Salt invalido",
    "Algoritmo de codificacao nao suportado",
    "As senhas nao conferem",
    "Opcao de configuracao invalida",
    "Id de usuario invalida",
    "Argumento nulo",
    "Idioma invalido",
    "Argumento invalido",
    "Arquivo de configuracao invalido",
    "Usuario invalido",
    "Nomes de usuario nao correspondem",
    "Emails nao correspondem",
    "Numero insuficiente de argumentos",
    "Perfil invalido",
    "Email de amigo invalido",
    "Nickname invalido",
    "Ambiente incorreto",
    "Nao foi possivel abrir arquiv",
    "Dados de usuario invalidos",
    "Arquivo de usuarios ja existe",
    "Nao foi possivel criar arquivo temporario",
    "Nao foi possivel alocar memoria",
    "O arquivo de dados de usuario esta corrompido",
    "Nome de projeto invalido",
    "Nao foi possivel enviar email",
    "Opcao nao suportada",
    "Chave invalida",
    "Argumento definido duas vezes",
    "Nao foi possivel criar apelido",
    "Usuario nao encontrado",
    "Senha incorreta",
    "Nao foi possivel criar arquivo de configuracao",
    "Permissao negada",
    "Nao ha nenhum convite",
    "O arquivo de usuarios convidados esta corrompido",
    "Convite nao encontrado",
    "O convite expirou",
    "Este apelido ja existe",
    "Este email ja esta cadastrado",
    "O sistema ja foi configurado",
    "Sistema nao configurado",
    "Usuario aguardando aprovacao",
    "Nao ha nenhuma solicitacao de registro",
    "Solicitacao nao encontrada",
    "Amigo nao encontrado",
    "Administrador nao encontrado"
  }
};

char * gmtUmlWebErrorMessages [gmtUmlLanguageAmount] [gmtUmlErrorAmount] =
{
  {
    "Ok",
    "The function is trying to use a null pointer",
    "Invalid file path",
    "Invalid file name",
    "The function is trying to use an invalid length",
    "The string length is not valid",
    "The string contains an invalid character",
    "Invalid username",
    "Invalid email",
    "Invalid name",
    "Invalid encryption algorithm",
    "Invalid password",
    "Invalid salt",
    "Unsupported algorithm",
    "Passwords don\'t match",
    "Invalid configuration option",
    "Invalid user id",
    "Null argument",
    "Invalid language",
    "Invalid argument",
    "Invalid configuration file",
    "Invalid user",
    "User names don\'t match.",
    "Emails don\'t match.",
    "Too few arguments",
    "Invalid profile",
    "Invalid friend email",
    "Invalid nickname",
    "Incorrect environment",
    "Could not open file",
    "Invalid user data",
    "Users file already exists",
    "Could not create temporary file",
    "Could not allocate memory",
    "The user file is corrupted.",
    "Invalid project name",
    "Could not send email",
    "Option not supported",
    "Invalid key",
    "Argument set twice",
    "Cannot create nickname",
    "User not found",
    "Incorrect password",
    "Could not create configuration file",
    "Permission denied",
    "There are no invitations",
    "The invited users file is corrupted",
    "Invitation not found",
    "The invitation expired",
    "Nickname already exists",
    "Email already exists",
    "The system has been configured already",
    "The system is not configured",
    "User still awaiting for approval",
    "There is no registration request pending",
    "Request not found",
    "Friend not found",
    "Administrator not found"
  },
  {
    "Sucesso",
    "A funcao esta tentando usar um ponteiro nulo",
    "Diretorio invalido",
    "Nome de arquivo invalido",
    "O comprimento informado e invalido",
    "A string possui comprimento nao permitido",
    "A string possui caractere invalido",
    "Nome de usuario invalido",
    "Email invalido",
    "Nome invalido",
    "Algoritmo de codificacao invalido",
    "Senha Invalida",
    "Salt invalido",
    "Algoritmo de codificacao nao suportado",
    "As senhas nao conferem",
    "Opcao de configuracao invalida",
    "Id de usuario invalida",
    "Argumento nulo",
    "Idioma invalido",
    "Argumento invalido",
    "Arquivo de configuracao invalido",
    "Usuario invalido",
    "Nomes de usuario nao correspondem",
    "Emails nao correspondem",
    "Numero insuficiente de argumentos",
    "Perfil invalido",
    "Email de amigo invalido",
    "Nickname invalido",
    "Ambiente incorreto",
    "Nao foi possivel abrir arquiv",
    "Dados de usuario invalidos",
    "Arquivo de usuarios ja existe",
    "Nao foi possivel criar arquivo temporario",
    "Nao foi possivel alocar memoria",
    "O arquivo de dados de usuario esta corrompido",
    "Nome de projeto invalido",
    "Nao foi possivel enviar email",
    "Opcao nao suportada",
    "Chave invalida",
    "Argumento definido duas vezes",
    "Nao foi possivel criar apelido",
    "Usuario nao encontrado",
    "Senha incorreta",
    "Nao foi possivel criar arquivo de configuracao",
    "Permissao negada",
    "Nao ha nenhum convite",
    "O arquivo de usuarios convidados esta corrompido",
    "Convite nao encontrado",
    "O convite expirou",
    "Este apelido ja existe",
    "Este email ja esta cadastrado",
    "O sistema ja foi configurado",
    "Sistema nao configurado",
    "Usuario aguardando aprovacao",
    "Nao ha nenhuma solicitacao de registro",
    "Solicitacao nao encontrada",
    "Amigo nao encontrado",
    "Administrador nao encontrado"
  }
};

char *
GmtUmlGetCliErrorMessage (gmtUmlErrorType gmtUmlError, gmtUmlLanguageType gmtUmlLanguage)
{
  return gmtUmlCliErrorMessages [gmtUmlLanguage] [gmtUmlError];
}

char *
GmtUmlGetNcursesErrorMessage (gmtUmlErrorType gmtUmlError, gmtUmlLanguageType gmtUmlLanguage)
{
  return gmtUmlNcursesErrorMessages [gmtUmlLanguage] [gmtUmlError];
}

char *
GmtUmlGetWebErrorMessage (gmtUmlErrorType gmtUmlError, gmtUmlLanguageType gmtUmlLanguage)
{
  return gmtUmlWebErrorMessages [gmtUmlLanguage] [gmtUmlError];
}
