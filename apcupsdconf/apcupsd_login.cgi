# this is the login file for the apcupsd configuration tool
# this file gets its user / admin settable variables from the configloc.pl file

use CGI qw/:standard/;

require "configloc.pl";

$apc = new CGI;

print $apc->header;

print $apc->start_html(-title=>'apcupsd configuration login', -BGCOLOR=>$bgcolor),"\n";

print p,"<center><img src=\"$imageloc\"></center>\n";

print p,"<B><font size=\"+1\"> Welcome to the apcupsd configuration tool. </font></b>\n" ;

print p,"<B>This tool is designed to aid in the creation of apcupsd.conf files. ";

print "Please read the documentation that came with your version of apcupsd before making changes. \n";

print "It can be found <a href=\"$helpfile\">here.</a>\n";

print "<center>",p,"Enter login and password:\n", $apc->start_form(-name=>'apc', -action=>'apcupsd_conf.cgi');

print p,"*USERNAME: ", $apc->textfield(-name=>'username', -maxlength=>8),"\n";

print p,"*PASSWORD: ", $apc->password_field(-name=>'password', -maxlength=>8),"\n";

print p, $apc->submit(-value=>'login',-name=>'submit'), "\n";

print p,"Please send bug report to <a href=\"$mailbugs\">$mailbugs</a>.\n";

print $apc->end_form,"\n</b>", $apc->end_html,"\n"; 
