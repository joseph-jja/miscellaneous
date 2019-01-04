
# this code is for the admin password tool
# this can be modified to be a frontend to any password files fairly easily IMHO

use CGI qw/:standard/;

require "configloc.pl";

require "apcupsd_common.pl";

$apc = new CGI;

print $apc->header, $apc->start_html(-title=>'apcupsd configuration login', -BGCOLOR=>$bgcolor),"\n";

print p,"<center><img src=\"$imageloc\"></center>\n";

print p,"<B><font size=\"+1\"> This is the user maintenance screen to apcupsd_conf. </b>\n" ;

print p,"Please read the documentation that came with the version \n";

print "of apcupsd before making changes. It can be found \n";

print "<a href=\"$helpfile\">here.</a>\n";

my $noerror = 0;

# check to see that we have admin user and a password
if (param('password') && (param('username') eq "admin")) { 

    # check the password
	# bug here why do we need to pass the substr??
    $noerror = checkPass(param('password'), substr(param('username'), 0,5), $apcpwdfile); 

    if ($noerror == 1) {

        # here we do the processing for ad change or delete of users if any cunfiotn is seleted 
        if (param('userfunct')) {
            if ((param('userfunct') eq " Delete User ") || (param('userfunct') eq " Reset Password ")) {
                 open(PWDFILE, "< $apcpwdfile");
                 my @addarray = "";
                 while (!eof(PWDFILE)) {
                         $password = readline(*PWDFILE);
                         my ($un,$pn) = split(/\s/,$password);
                         if ($un ne param('userlist')) {
                             push (@addarray, $password);
                         }
                }
               close(PWDFILE); 
               open(PWDFILE, "> $apcpwdfile");
               foreach $item (@addarray) {
                    print PWDFILE $item;
               }                     
               close(PWDFILE); 
           } 
            if ((param('userfunct') eq " Add User ") || (param('userfunct') eq " Reset Password ")) {
                 open(PWDFILE, "< $apcpwdfile");
                 my $eno = 0;
                 my @addarray = "";
                 while (!eof(PWDFILE)) {
                         $password = readline(*PWDFILE);
                         push (@addarray, $password);
                         my ($un,$pn) = split(/\s/,$password);
                         if ($un eq param('uname')) {
                             print p,"<b>User Exists And Cannot Be Added!</b>";
                             $eno =1;
                         }
                }
               close(PWDFILE); 
                if ($eno != 1) {
                    open(PWDFILE, "> $apcpwdfile");
                    foreach $item (@addarray) {
                        print PWDFILE $item;
                   }
                    if (param('pwd') && param('confirmpwd') && (param('pwd') eq param('confirmpwd'))) {
                        my $newpwd = crypt(param('pwd'), param('uname')); 
                        my $name = param('uname');
                        print PWDFILE "$name $newpwd\n";  
                    }                         
                    close(PWDFILE); 
                }             
            } 
        }

        print "<center>",p;
 
        # the actual for that you see on your screen
        print $apc->start_form(-name=>'change_pass', -action=>'admin_cfg.cgi');

        my $pass = param('password');

        my $uname = param('username');

        print "<input type=hidden name=\"password\" value=\"$pass\">";

        print "<input type=hidden name=\"username\" value=\"$uname\">";

        print p,"<table border=2 cellpadding=5 cellspacing=5><tr><td>Users: <br><center><select name=userlist size=5>";

        # read in the user names and passwords
        open (FILENAME, "< $apcpwdfile");
        while(!eof(FILENAME)) {
            my $namespwd = readline(*FILENAME);
            my ($names, $pwd) = split(/\s/,$namespwd);
            if ($names ne "admin") {
                print "<option value=\"$names\">$names</option>";
           }
        }
        close(FILENAME);
        print "<option value=\"\">----------</option>";

        print "</select></center></td><td>\n";

        print $apc->radio_group(-name=>'userfunct', -linebreak=>'true', -values=>[' Add User ',' Delete User ', ' Reset Password ']), "</td><td>\n";

        # initialize flds
        $apc->delete('uname');
        $apc->delete('pwd');
        $apc->delete('confirmpwd');

        print "<table><tr><td>New User Name: </td><td>",$apc->textfield(-name=>'uname', -maxlength=>8, -value=>'');

        print "\n</td></tr><tr><td>Password: </td><td>", $apc->password_field(-name=>'pwd', -maxlength=>8, -value=>''),"\n</B>\n";

        print "</td></tr><tr><td>Confirm Password: </td><td>", $apc->password_field(-name=>'confirmpwd', -maxlength=>8, -value=>''),"\n</td></tr></table></td></tr></table>";

        print p, $apc->submit(-value=>'Submit',-name=>'submit'), "\n";

        print $apc->reset(-value=>'Reset',-name=>'reset'), "\n";

        print $apc->hidden(-value=>param('username'), -name=>'username');

        print $apc->end_form,"\n";

        print $apc->start_form(-name=>'relogin', -action=>'apcupsd_login.cgi');

        print p, $apc->submit(-value=>'Return to Logon Screen',-name=>'submit'), "\n";

        print $apc->end_form,"\n</center>";

    } else {
        print p, "<B>You have incorrectly accessed this page!</b>";
	}

} else {

    print p, "<B>You have incorrectly accessed this page!</b>";
}
print $apc->end_html;
