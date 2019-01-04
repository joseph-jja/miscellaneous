# makefile for apcconfig

PERL = /usr/bin/perl

where = /public/lx-bin/apcupsdrun/

CGIFILE = apcconf.cgi apcupsd_conf.cgi apcupsd_login.cgi configloc.pl admin_cfg.cgi apcupsd_pwd.cgi apcupsd_common.pl

IMGFILE = apcupsd.gif

PASSWDFILE = .apcpwdfile

all:

install:
	chmod +x $(CGIFILE)
	for i in $(CGIFILE); do \
	    echo "#!$(PERL)" > tmp ; \
	    cat $$i >> tmp ; \
            install -D tmp $(where)/$$i  ; \
        done 
	rm -f tmp
	chmod +x $(IMGFILE)
	install $(IMGFILE) $(where)
	cp -rp cfgfiles $(where)

install_pwdfile:
	chmod 777 $(PASSWDFILE)
	cp -p $(PASSWDFILE) $(where)
