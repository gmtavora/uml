/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlWebUserInterface.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 */

#include "gmtUmlConst.h"
#include "gmtUmlTypes.h"
#include "gmtUmlWebUserInterface.h"

char * gmtUmlWebUIMessages [gmtUmlLanguageAmount][gmtUmlUIMessageAmount] =
{
	{
		"Projeto",
		"Projeto",
		"Reset Password",
		"Help",
		"License",
		"Username",
		"Password",
		"Remember me",
		"Forgot password",
		"Register",
		"Home",
		"Login",
    "Language",
    "Email",
    "Back",
    "Full Name",
    "Confirm password",
    "Your Email",
    "Confirm your email",
    "Your friend's email",
    "I accept the terms of use.",
		"Hello,",
		"Pick one of the following options:",
		"Add User",
		"Invite User",
		"Registration Requests",
		"Lock User",
		"Unlock User",
		"Reset User\'s Password",
		"Change User\'s Password",
		"Change User\'s Name",
		"Change User\'s Email",
		"Change User\'s Profile",
		"Users List",
		"Logout",
		"This form adds a new user directly to the system.",
		"Confirm Email",
		"Confirm Name",
		"Confirm Password",
		"Profile",
		"User",
		"Admin",
		"Reset",
		"This form invites a new user to the system.",
		"You can check above the registration requests. You can also filter the requests by user.",
		"Nickname",
		"Filter",
		"Name",
		"Email",
		"Friend\'s nickname",
		"You may use this form to reset an user's password. A random new one will be generated, and the user will receive an email with instructions.",
		"You may use this form to change an user's email. A key will be generated and sent to the old email, so that the user can validate the new email.",
		"New Email",
		"New Name",
		"You may use this form to change an user's name. The new name may not generate a new nickname, but if it does, the new one cannot exist already.",
		"You may use this form to change an user's profile.",
		"New Password",
		"You may use this form to change an user's password. An alert email will be sent.",
		"Name",
		"Email",
		"Profile",
		"You can check above the users list. You can also filter the results.",
		"Profile",
		"User\'s Panel",
		"Admin\'s Panel"
	},
	{
		"Projeto",
		"Projeto",
		"Resetar Senha",
		"Ajuda",
		"Licenca",
		"Usuario",
		"Senha",
		"Lembrar-me",
		"Esqueci a senha",
		"Cadastrar",
		"Pagina Inicial",
		"Entrar",
    "Idioma",
    "Email",
    "Voltar",
    "Nome Completo",
    "Confirme sua senha",
    "Seu email",
    "Confirme seu email",
    "Email do seu amigo",
    "Aceito os termos de uso.",
		"Ola,",
		"Selecione uma das opcoes abaixo:",
		"Adicionar Usuario",
		"Convidar Usuario",
		"Solicitacoes de Registro",
		"Bloquear Usuario",
		"Desbloquear Usuario",
		"Resetar Senha de Usuario",
		"Mudar Senha de Usuario",
		"Mudar Nome de Usuario",
		"Mudar Email de Usuario",
		"Mudar Perfil de Usuario",
		"Lista de Usuarios",
		"Sair",
		"Este formulario adiciona um novo usuario diretamente ao sistema.",
		"Confirme o Email",
		"Confirme o Nome",
		"Confirme a Senha",
		"Perfil",
		"Usuario",
		"Admin",
		"Limpar",
		"Este formulario convida um novo usuario ao sistema.",
		"Voce pode ver abaixo os pedidos de registro. Voce tambem pode filtrar os registros por usuario.",
		"Apelido",
		"Filtrar",
		"Nome",
		"Email",
		"Apelido do amigo",
		"Voce pode usar este formulario para resetar a senha de um usuario. Uma nova senha aleatoria sera gerada, e o usuario recebera um email com instrucoes.",
		"Voce pode usar este formulario para alterar o email de um usuario. Uma chave sera gerada e enviada ao email antigo, para que o usuario possa validar o novo email.",
		"Novo Email",
		"Nov Nome",
		"Voce pode usar este formulario para alterar o nome de um usuario. O novo nome nao podera gerar um novo apelido, mas se o fizer, o apelido nao podera existir.",
		"Voce pode usar este formulario para alterar o perfil de um usuario.",
		"Nova Senha",
		"Voce pode usar este formulario para alterar a senha de um usuario. Um email sera enviado alertando-o.",
		"Nome",
		"Email",
		"Perfil",
		"Voce pode ver abaixo a lista de usuarios. Voce tambem pode filtrar os resultados.",
		"Perfil",
		"Painel de Usuario",
		"Painel de Admin"
	}
};

char *
GmtUmlGetWebUserInterface (gmtUmlMessageType gmtUmlMessage, gmtUmlLanguageType gmtUmlLanguage)
{
  return gmtUmlWebUIMessages [gmtUmlLanguage] [gmtUmlMessage];
}

/* $RCSfile: gmtUmlWebUserInterface.c,v $ */
