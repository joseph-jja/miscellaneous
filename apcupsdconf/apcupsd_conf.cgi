# this is the main configuration program for the apcupsd program

use CGI qw/:standard/;

require "configloc.pl";

require "apcupsd_common.pl";

$apc = new CGI;

# here we declair the an array for the fields we are going to use 
@allflds = ("UPSCABLE", "UPSTYPE","DEVICE","LOCKFILE","BATTERYLEVEL",
                   "MINUTES", "TIMEOUT","ANNOY", "ANNOYDELAY", "NOLOGON", 
                   "NETSERVER", "SERVERPORT", "EVENTSFILE","STATTIME","STATFILE",
                   "LOGSTATS","DATATIME", "SENSITIVITY","FACILITY","NETPORT", 
                   "UPSNAME","WAKEUP","SLEEP","LOTRANSFER", "HITRANSFER",
                   "RETURNCHARGE","BEEPSTATE","LOWBATT","OUTPUTVOLTS",
                   "UPSCLASS", "UPSMODE", "NETACCESS", "SELFTEST", "NETTIME",
                   "MASTER", "SLAVE", "USERMAGIC");

# here we declair arrays for things that we want to appear as selection boxes
@UPSCABLE = ("940-0020B", "940-0023A", "940-0024B", "940-0024C", 
              "940-1524C", "940-0024G", "940-0095A", "940-0095B", "940-0095C", "ether",
                          "smart", "simple");

@UPSTYPE = ("backups", "sharebasic", "backupspro", "netups", "smartvsups", "newbackupspro",
                          "backupspropnp", "smartups", "matrixups", "sharesmart");

@NOLOGON = ("always", "disable", "timeout", "percent", "minutes");

@NETSERVER = ("on", "off"); 

@LOGSTATS = ("on", "off");

@UPSCLASS = ("standalone", "shareslave", "sharemaster", "netslave", "netmaster",  "sharenetmaster");

@UPSMODE = ("disable", "share", "net", "sharenet"); 

@NETACCESS = ("true", "false"); 

# here we use 2 arrays rather than a hash.. maybe later
@cfgname = ("Custom Configuration", "Default Configuration",  "Server Configuration", "Slave Configuration");

@cfgfile = ($infile, $defaultcfg, $servercfg, $slavecfg);

$cfgvar = 0;

# define the error message to be displayed wheh a uid/pwd combo fails
$accessviolation = "<b>You are not authorized to access this system or you have not supplied the correct user id or password</b>\n";

# create the header and the title
print $apc->header;
print $apc->start_html(-title=>'apcupsd configuration', -BGCOLOR=>$bgcolor),"\n";

print p,"<center><img src=\"$imageloc\"></center>\n";

# this is set to 0 on error, 1 on no error 
$noerror = checkPass(param('password'), param('username'), $apcpwdfile);

# check password and uid were entered by user
if (!$noerror) {
   push (@errorarray, $accessviolation);
   $errorcode = 1;
} else {
    # setup default hidden fields 
    $hiddenflds = "<input type=hidden name=username  value=" . param('username') . ">\n"; 
    $hiddenflds .= "<input type=hidden name=password value=" . param('password') . ">\n";
}

# check to see that we had a uid/pwd match else display an error message
if ($noerror != 1) {
   push (@errorarray, $accessviolation);
   $errorcode = 1;
}

# these lines prints the top of the file
print p,"These are the current settings in the <B>$infile</b> file.\n";

print p,"Please read the documentation that came your the version of apcupsd before making changes. \n";

print "The documentation can be found <a href=\"$helpfile\">here.</a>\n";

# check for errors and if we have errors print them all and stop the program
if ($errorcode != 0) {
    print p,"<b>The following error(s) has(have) occured: </b>\n";
    
    print "<blockquote><ul>";

    foreach $error (@errorarray) {      
        print "<li>", $error, "</li>";
    }

    print "</ul></blockquote>";
    
    # this is the form button to take us back to the logon screen 
    # if we are here then we have not logged in correctly
    print "<form method=post action=apcupsd_login.cgi>\n";
    print "<input type=submit value=\"Back To Login\">\n";
    print "</form>";

    exit -1;
} 

# this is a change password button
print "<center><table><tr><td><form name=selectcfg method=post action=apcupsd_pwd.cgi>\n";

print "$hiddenflds";
 
print "<input type=\"submit\" name=\"pwdsubmit\"  value=\"change your password\">\n";

print "</form>\n</td>";

# this is the apcupsd user configuration manager
if (param('username') eq "admin") { 
    print "<td><form name=selectcfg method=post action=admin_cfg.cgi>\n$hiddenflds";
    print "<input type=\"submit\" name=\"adminpwd\"  value=\"apcupsd admin user configuration tool\">\n";
    print "</form></td></tr>\n";
}
print "</table></center>";

# this is where we begin the main forms
# this form is for adding slaves or selecting the different configuration file
print "<form name=selectcfg method=post action=apcupsd_conf.cgi>\n";

# we need to save the UID and PWD and store them here
print "$hiddenflds";
 
print "<br><center>Type of configuration file: </td><td><select width=30 name=cfgtype>\n";

# this determines which cfg file we are loading
foreach $item (@cfgname) {
    if ((param('cfgtype') ne "" )  && (param('cfgtype') eq $cfgfile[$cfgvar] ) ) {
        print "<option value=\"$cfgfile[$cfgvar]\" selected>$item</option>\n";
        $infile = $cfgfile[$cfgvar];
    } else {
        print "<option value=\"$cfgfile[$cfgvar]\">$item</option>\n";
    }
    $cfgvar++;
}

print "</select>\n";

print "<input type=submit value=\"Load Config\"></center>\n";
print "<br><center>Number of SLAVES: </td><td><input type=textfield size=10 name=addslaves>\n";
print " <input type=submit value=\"Add Fields\"></center>\n";
print "</form>\n";

# print the second form
print "\n<center>", $apc->start_form(-name=>'apcreadconf', -action=>'apcconf.cgi');

print $apc->start_table();

my $i =1 ;
my $k = 0;
my $mod = $i%2;
my $slavesno = 0;
 
# this is to print out the table in multi column format and also does some witchcraft 
# with the slaves directive
foreach $item (@allflds) {
    my $retnval = getfld($item, $infile, $slavesno); 

    my $hrefs="<a href=$helpfile#$item>";

    if ($mod == 1) {
        print "<tr>";
    }

    # if an array has been defined for this then we create a selection list for it
    # else we create a text feild for it
    if (@$item) {
        # initialize counter then start creating selection box
        my $itemval = 0;
        print "<td bgcolor=",$color[$k%2],">$hrefs$item</a> </td><td bgcolor=",$color[$k%2],">\n";
        print "<select width=30 name=$item>";

        foreach $newitem (@$item) {
            if (($retnval ne "" )  && ($retnval eq $newitem ) ) {
                print "<option value=\"$newitem\" selected>$newitem</option>\n";
            } else {
                print "<option value=\"$newitem\">$newitem</option>\n";
            }
            $itemval++;
        }
        print "</select></td>\n";

    } else {
       if (($item eq "SLAVE") ||  (($item eq "SLAVE") && (param('addslaves') ne ""))) {
           # we need to do something if we have more slaves
           print "\n<td bgcolor=",$color[$k%2],">$hrefs$item</a> </td><td bgcolor=",$color[$k%2],">", $apc->textfield(-name=>$item, -value=>$retnval, -size=>$tsize), "</td>\n";
           if ($mod == 0) {
               print "</tr>";
              $k++;
           }
           $i++;
           $mod = $i%2;
           my $totnum = getslvcnt($infile);
           for (my $slv=1; $slv <param('addslaves') + $totnum;$slv++) { 
               $slavesno++;
               $retnval = getfld($item, $infile, $slavesno);
               if ($mod == 1) {
                   print "<tr>";
               }
               print "\n<td bgcolor=",$color[$k%2],">$hrefs$item</a> </td><td bgcolor=",$color[$k%2],">", $apc->textfield(-name=>$item, -value=>$retnval, -size=>$tsize), "</td>\n";
               if ($mod == 0) {
                  print "</tr>";
                  $k++;
               }
               $i++;
               $mod = $i%2;
           }
        } else {
           # becuase of bugs we are making user magic always in its own row for now
           if ($item eq "USERMAGIC") {
                   print "<tr>";
           }
           print "\n<td bgcolor=",$color[$k%2],">$hrefs$item</a> </td><td bgcolor=",$color[$k%2],">", $apc->textfield(-name=>$item, -value=>$retnval, -size=>$tsize), "</td>\n";
        }
    }

    if ($mod == 0) {
        print "</tr>";
        $k++;
    }
    
    $i++;
    $mod = $i%2;
}

print $apc->end_table();

# again we are saving UID/PWD else we get errors
print "$hiddenflds";

print $apc->submit(-value=>'Modify', -name=>'Submit');
 
print $apc->end_form, "</center>\n";

print $apc->end_html,"\n";

sub getfld {
    my ($fldname, $filename, $myslve) = @_;
    $myslvtmp =0;
    open(FILENAME, "<$filename");    
    while(!eof(FILENAME)) {
        my $nextline = readline(*FILENAME);
        my $fld = substr($nextline, 0, length($fldname));       
        if ($fld eq $fldname) {
            chop($nextline);
            if ($fldname ne "SLAVE") {            
                my $val = substr($nextline, length($fldname)+1, length($nextline));
                close(FILENAME); 
                return $val; 
            } else {
                if ($myslve == $myslvtmp) {      
                    my $val = substr($nextline, length($fldname)+1, length($nextline));
                    close(FILENAME); 
                    return $val; 
                }
                $myslvtmp++;
            }
        }
    }
    close(FILENAME); 
    return;
}

sub getslvcnt {
    my ($filename) = @_;
    $myslvtmp = 0;
    open(FILENAME, "<$filename");    
    while(!eof(FILENAME)) {
        my $nextline = readline(*FILENAME);
        my $fld = substr($nextline, 0, length("SLAVE"));       
        if ($fld eq "SLAVE") {
            $myslvtmp++;
        }
    }
    close(FILENAME); 
    return $myslvtmp;
}

