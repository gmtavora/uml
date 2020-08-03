# Universidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
# Prof. Marcelo Luiz Drumond Lanza
# EEL 270 - Computacao II - Turma 2017/2
# 
# $Author: gabriel.tavora $
# $Date: 2017/12/21 22:04:50 $
# $Log: Makefile,v $
# Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
# Initial revision
#
#

# Compilacao e Link-edicao
CC = gcc
LD = gcc

# mkdir
MKDIR = mkdir -p

# Flags de compilacao e link-edicao
CFLAGS = -Wall -ansi -std=c99
LFLAGS = -Wall -ansi -std=c99

# Diretorios
GMTUMLWEBDIR = ~gabriel.tavora/public/html/
GMTUMLBINDIR = ~gabriel.tavora/private/EEL270/2017-2/GMT_UML/Binaries/
GMTUMLDATADIR = ~gabriel.tavora/private/EEL270/2017-2/GMT_UML/Data/
GMTUMLHTMLDIR = ~gabriel.tavora/private/EEL270/2017-2/GMT_UML/Sources/HTML/
GMTUMLCOOKIESDIR = ~gabriel.tavora/private/EEL270/2017-2/GMT_UML/Data/Cookies/
CGIDIR = CGIs/

# OBJS
GMTUMLOBJS = gmtUmlFunctions.o gmtUmlShowCliHelp.o gmtUmlRunNcursesInterface.o \
	     gmtUmlShowConfigurationValues.o gmtUmlErrors.o gmtUmlAddUser.o \
	     gmtUmlCliUserInterface.o gmtUmlGetUsers.o gmtUmlSearchUsers.o gmtUmlRejectInvite.o \
	     gmtUmlAcceptInvite.o gmtUmlChangeUserPassword.o gmtUmlRequestRegistration.o \
	     gmtUmlGetPendingRegistrationRequestsPerUser.o gmtUmlGetPendingRegistrationRequests.o \
	     gmtUmlApproveRegistrationRequest.o  gmtUmlDisapproveRegistrationRequest.o gmtUml.o
GMTUMLCGIMAINOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlCgiMain.o
GMTUMLSHOWLICENSEOBJS = gmtUmlFunctions.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlWebUserInterface.o gmtUmlShowLicense.o
GMTUMLSHOWPASSWORDRESETOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
			      gmtUmlCgiShowRequestPasswordResetForm.o
GMTUMLSHOWREGISTRATIONFORMOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
				 gmtUmlCgiShowRequestRegistrationForm.o
GMTUMLPASSWORDRESETOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
			      gmtUmlCgiRequestPasswordReset.o
GMTUMLREQUESTREGISTRATIONOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
				 gmtUmlCgiRequestRegistration.o
GMTUMLSHOWWEBHELPOBJS = gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
			gmtUmlCgiShowWebHelp.o
GMTUMLCGILOGINOBJS = gmtUmlCgiLogin.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
		     gmtUmlErrors.o gmtUmlCreateCookieFile.o
GMTUMLCGILOGOUTOBJS = gmtUmlCgiLogout.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
		     gmtUmlErrors.o gmtUmlCreateCookieFile.o
GMTUMLUSERPANELOBJS = gmtUmlCgiUserPanel.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o \
		     gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLADMINPANELOBJS = gmtUmlCgiAdminPanel.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIADDUSERFORMOBJS = gmtUmlCgiAddUserForm.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIADDUSEROBJS = gmtUmlCgiAddUser.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o gmtUmlAddUser.o
GMTUMLCGIINVITEUSERFORMOBJS = gmtUmlCgiInviteUserForm.o  gmtUmlFunctions.o \
			  gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
			  gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIINVITEUSEROBJS = gmtUmlCgiInviteUser.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o gmtUmlAddUser.o
GMTUMLCGIREGISTRATIONREQUESTSOBJS = gmtUmlCgiRegistrationRequests.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIRESETUSERPASSWORDFORMOBJS = gmtUmlCgiResetUserPasswordForm.o gmtUmlFunctions.o \
				 gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				 gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIRESETUSERPASSWORDOBJS = gmtUmlCgiResetUserPassword.o gmtUmlFunctions.o \
				 gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				 gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o 
GMTUMLCGICHANGEUSEREMAILFORMOBJS = gmtUmlCgiChangeUserEmailForm.o gmtUmlFunctions.o \
			       gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
			       gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSEREMAILOBJS = gmtUmlCgiChangeUserEmail.o gmtUmlFunctions.o \
			       gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
			       gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSERNAMEFORMOBJS = gmtUmlCgiChangeUserNameForm.o gmtUmlFunctions.o \
			      gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
			      gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSERNAMEOBJS = gmtUmlCgiChangeUserName.o gmtUmlFunctions.o \
			      gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
			      gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSERPROFILEFORMOBJS = gmtUmlCgiChangeUserProfileForm.o gmtUmlFunctions.o \
				 gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				 gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSERPROFILEOBJS = gmtUmlCgiChangeUserProfile.o gmtUmlFunctions.o \
				 gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				 gmtUmlCompareCookie.o gmtUmlCreateCookieFile.oG
GMTUMLCGICHANGEUSERPASSWORDFORMOBJS = gmtUmlCgiChangeUserPasswordForm.o gmtUmlFunctions.o \
				  gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				  gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGICHANGEUSERPASSWORDOBJS = gmtUmlCgiChangeUserPassword.o gmtUmlFunctions.o \
				  gmtUmlWebUserInterface.o gmtUmlGetUsers.o gmtUmlCliUserInterface.o gmtUmlErrors.o \
				  gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o
GMTUMLCGIGETUSERSOBJS = gmtUmlCgiGetUsers.o gmtUmlFunctions.o gmtUmlWebUserInterface.o gmtUmlGetUsers.o \
		       gmtUmlCliUserInterface.o gmtUmlErrors.o gmtUmlCompareCookie.o gmtUmlCreateCookieFile.o gmtUmlSearchUsers.o

# Executaveis
EXECS = gmtUml \
	gmtUmlMain.cgi \
	gmtUmlLogin.cgi \
	gmtUmlShowLicense.cgi \
	gmtUmlShowRequestPasswordResetForm.cgi \
	gmtUmlShowRequestRegistrationForm.cgi \
	gmtUmlShowWebHelp.cgi \
	gmtUmlAdminPanel.cgi \
	gmtUmlUserPanel.cgi \
	gmtUmlLogout.cgi \
	gmtUmlAddUserForm.cgi \
	gmtUmlAddUser.cgi \
	gmtUmlInviteUserForm.cgi \
	gmtUmlInviteUser.cgi \
	gmtUmlRegistrationRequests.cgi \
	gmtUmlResetUserPasswordForm.cgi \
	gmtUmlChangeUserEmailForm.cgi \
	gmtUmlChangeUserNameForm.cgi \
	gmtUmlChangeUserProfileForm.cgi \
	gmtUmlChangeUserPasswordForm.cgi \
	gmtUmlGetUsers.cgi

# HTML
HTML = html-indexes \
       html-images \
       html-other

# Regra Implicita
.c.o:
	$(CC) $(CFLAGS) -c $<

# Rotulos
libgmtuml.a:
	ar -r $@ $(LIBGMTUMLOBJS)

install: $(directories) $(HTML) $(EXECS)

directories:
	$(MKDIR) $(GMTUMLWEBDIR)
	$(MKDIR) $(GMTUMLBINDIR)
	$(MKDIR) $(GMTUMLDATADIR)
	$(MKDIR) $(GMTUMLWEBDIR)$(CGIDIR)
	$(MKDIR) $(GMTUMLCOOKIESDIR)

html-indexes:
	cp $(GMTUMLHTMLDIR)index_en-us.html $(GMTUMLWEBDIR)index_en-us.html
	cp $(GMTUMLHTMLDIR)index_pt-br.html $(GMTUMLWEBDIR)index_pt-br.html

html-images:
	cp -R $(GMTUMLHTMLDIR)images $(GMTUMLWEBDIR)images

html-other:
	cp -R $(GMTUMLHTMLDIR)CGIs/bootstrap $(GMTUMLWEBDIR)CGIs/bootstrap
	cp $(GMTUMLHTMLDIR)CGIs/jquery-3.2.1.js $(GMTUMLWEBDIR)CGIs/jquery-3.2.1.js
	cp $(GMTUMLHTMLDIR)CGIs/style.css $(GMTUMLWEBDIR)CGIs/style.css
	cp ~gabriel.tavora/private/EEL270/2017-2/GMT_UML/Sources/C/gmt-uml.cfg $(GMTUMLWEBDIR)CGIs/gmt-uml.cfg

gmtUml: $(GMTUMLOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLBINDIR)$@ $(GMTUMLOBJS) -lcrypt -lncurses -L Libraries -lsendmail -D_DEBUG_

gmtUmlMain.cgi: $(GMTUMLCGIMAINOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIMAINOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlLogin.cgi: $(GMTUMLCGILOGINOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGILOGINOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlShowLicense.cgi: $(GMTUMLSHOWLICENSEOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLSHOWLICENSEOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlShowRequestPasswordResetForm.cgi: $(GMTUMLSHOWPASSWORDRESETOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLSHOWPASSWORDRESETOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlRequestPasswordReset.cgi: $(GMTUMLPASSWORDRESETOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLPASSWORDRESETOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlShowRequestRegistrationForm.cgi: $(GMTUMLSHOWREGISTRATIONFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLSHOWREGISTRATIONFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlRequestRegistration.cgi: $(GMTUMLREQUESTREGISTRATIONOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLREQUESTREGISTRATIONOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlShowWebHelp.cgi: $(GMTUMLSHOWWEBHELPOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLSHOWWEBHELPOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlUserPanel.cgi: $(GMTUMLUSERPANELOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLUSERPANELOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlAdminPanel.cgi: $(GMTUMLADMINPANELOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLADMINPANELOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlLogout.cgi: $(GMTUMLCGILOGOUTOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGILOGOUTOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlAddUserForm.cgi: $(GMTUMLCGIADDUSERFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIADDUSERFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlAddUser.cgi: $(GMTUMLCGIADDUSEROBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIADDUSEROBJS) -L Libraries -lmlcgi -lsendmail -lcrypt

gmtUmlInviteUserForm.cgi: $(GMTUMLCGIINVITEUSERFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIINVITEUSERFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlInviteUser.cgi: $(GMTUMLCGIINVITEUSEROBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIINVITEUSEROBJS) -L Libraries -lmlcgi -lsendmail -lcrypt

gmtUmlRegistrationRequests.cgi: $(GMTUMLCGIREGISTRATIONREQUESTSOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIREGISTRATIONREQUESTSOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlResetUserPasswordForm.cgi: $(GMTUMLCGIRESETUSERPASSWORDFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIRESETUSERPASSWORDFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlResetUserPassword.cgi: $(GMTUMLCGIRESETUSERPASSWORDOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIRESETUSERPASSWORDOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserEmailForm.cgi: $(GMTUMLCGICHANGEUSEREMAILFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSEREMAILFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserEmail.cgi: $(GMTUMLCGICHANGEUSEREMAILOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSEREMAILOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserNameForm.cgi: $(GMTUMLCGICHANGEUSERNAMEFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERNAMEFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserName.cgi: $(GMTUMLCGICHANGEUSERNAMEOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERNAMEOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserProfileForm.cgi: $(GMTUMLCGICHANGEUSERPROFILEFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERPROFILEFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserProfile.cgi: $(GMTUMLCGICHANGEUSERPROFILEOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERPROFILEOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserPasswordForm.cgi: $(GMTUMLCGICHANGEUSERPASSWORDFORMOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERPASSWORDFORMOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlChangeUserPassword.cgi: $(GMTUMLCGICHANGEUSERPASSWORDOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGICHANGEUSERPASSWORDOBJS) -L Libraries -lmlcgi -lcrypt

gmtUmlGetUsers.cgi: $(GMTUMLCGIGETUSERSOBJS)
	$(LD) $(LFLAGS) -o $(GMTUMLWEBDIR)$(CGIDIR)$@ $(GMTUMLCGIGETUSERSOBJS) -L Libraries -lmlcgi -lcrypt

clean:
	rm -f *.o $(ALL)

