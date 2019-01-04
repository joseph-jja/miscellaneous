
# this code is a mess unless you really want to make changes I wouldn't mess with it
# I am working on this though

use CGI qw/:standard/;

require "configloc.pl";

require "apcupsd_common.pl";

$apc = new CGI;

print $apc->header;

print $apc->start_html(-title=>'apcupsd configuration login', -BGCOLOR=>$bgcolor),"\n";

print p,"<center><img src=\"$imageloc\"></center>\n";

print p,"<B><font size=\"+1\"> This is the password maintenance screen to apcupsd_conf. </b>\n" ;

print p,"Please read the documentation that came with the version \n";

print "of apcupsd before making changes. It can be found \n";

print "<a href=\"$helpfile\">here.</a>\n";

# verify old password not just name
my $pass = checkPass(param('password'), param('username'), $apcpwdfile);
if (!$pass) {
    my $pass = checkPass(param('pwd'), param('uname'), $apcpwdfile);
}

my $noerror = !$pass;

if (param('pwdsubmit')  || (param('uname') || param('pwd'))) { 

    if ((param('uname') && !param('pwd')) 
	    || (!param('uname') && param('pwd'))
		|| (!param('pwdsubmit') && (!param('newpwd')  || !param('confirmpwd')))) {
        print "<P><b>Make sure you have entered Username, Password, ";
        print "New Password, and Confirm Password!</b>";
    }

    if (param('newpwd') && param('confirmpwd')) {

        $noerror = updatePass (param('pwd'), param('uname'), param('newpwd'), param('confirmpwd'), $apcpwdfile);

        if ($noerror == 1) {
                print p, "<center><h2>Password was changed!</h2></center>";
        } else {
             print p, "<center><h2>Passwords did not match!</h2></center>";
        }        
    }

    if (!$noerror) {

        print "<center>",p,"Enter login and password:\n<table><tr><td>";
 
        print $apc->start_form(-name=>'change_pass', -action=>'apcupsd_pwd.cgi');
 
        print p,"<B>*USERNAME: ", $apc->textfield(-name=>'uname', -maxlength=>8, -value=>param('username')),"\n";

        print p,"*NEW PASSWORD: ", $apc->password_field(-name=>'newpwd', -maxlength=>8),"</B></td><td>\n";

        print p,"<B>*PASSWORD: ", $apc->password_field(-name=>'pwd', -maxlength=>8),"\n";

        print p,"*CHANGE PASSWORD: ", $apc->password_field(-name=>'confirmpwd', -maxlength=>8),"\n</B></td></tr></table>";

        print p, $apc->submit(-value=>'Change Password',-name=>'submit'), "\n";

    } else {

        print "<center><b>Now test your new password.</b>";

        print $apc->start_form(-name=>'relogin', -action=>'apcupsd_login.cgi');

        print p, $apc->submit(-value=>'Return to Logon Screen',-name=>'submit'), "\n";

    }
    print $apc->end_form,"\n</center>";

} else {

    print p, "<B>You have incorrectly accessed this page!</b>";
 
    print "<center>", $apc->start_form(-name=>'relogin', -action=>'apcupsd_login.cgi');

    print p, $apc->submit(-value=>'Return to Logon Screen',-name=>'submit'), "\n";
 
    print $apc->end_form,"\n</center>";
}

print $apc->end_html;
