
use CGI;
require "configloc.pl";

require "apcupsd_common.pl";

require "flush.pl";

# initial number of slaves
$slaveno = 0;

#initialize error code
$errorcode = 0;

# this is a simple perl program for writing the apcupsd.conf file
print "Content-type: text/html\n\n";

print "<html>\n";

print "<title>$datafile editor data</title><body bgcolor=\"$bgcolor\">\n";

print "<P><center><img src=\"$imageloc\"></center>\n";

read(STDIN, $data, $ENV{"CONTENT_LENGTH"});
@fields = split(/&/, $data);

# initialize the counter
$i = 0;
# this is where we do data checking and see if the data that the 
# user want to use is actually valid data
foreach $item (@fields) {
     @inputdata = split(/=/, $item);
     $inputdata[1] =~ s/\+/ /g;
     $pos = 0;
     while (($pos = index($inputdata[1], "%" , $pos)) != -1) {
          $ascii = hex(substr($inputdata[1], $pos + 1, 2)) ;
          substr($inputdata[1], $pos , 3) = pack("c", $ascii);
     }
     # we build a hash that is indexed for error checking
     $myhash{$inputdata[0]} = $inputdata[1];
}

$accessviolation = "<b>You are not authorized to access this system or you have not supplied the correct user id or password</b>\n";

#return 0 on error, or 1 on no error
$noerror = checkPass($myhash{password}, $myhash{username}, $apcpwdfile);

if ($noerror != 1) {
   push (@errorarray, $accessviolation);
   $errorcode = 1;
}

# rules we should obey
if (($myhash{UPSCLASS} eq netslave) && ($myhash{UPSCABLE} ne ether)) {
     push (@errorarray, "For UPSCLASS set to netslave the UPSCABLE must be set to ether.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSCABLE} eq ether) && ($myhash{UPSCLASS} ne netslave)) {
     push (@errorarray, "for UPSCABLE set to ether the UPSCLASS must be set to netslave.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} eq netslave) && ($myhash{NETSERVER} eq on)) {
     push (@errorarray, "For UPSCLASS set to netslave the NETSERVER must be off as on is not supported.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} ne netslave) && ($myhash{USERMAGIC} ne "")) {
     push (@errorarray, "For UPSCLASS set to netslave, USERMAGIC should be blank.\n"); 
     if (length($myhash{USERMAGIC}) > 20) {
         push (@errorarray, "USERMAGIC must be less than 20 characters.\n"); 
     }
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} ne netmaster) && ($myhash{NETTIME} ne "")) {
     push (@errorarray, "NETTIME is only used when UPSCLASS is set to netmaster.\n"); 
     if ($myhash{NETTIME} == 0) {
         push (@errorarray, "NETTIME must not be 0 and it should be a low number.\n"); 
     }
     $errorcode = 1; 
}
if (($myhash{BATTERYLEVEL} ne "") && (($myhash{BATTERYLEVEL} < 0) || 
                                      ($myhash{BATTERYLEVEL} >100))) {
     push (@errorarray, "BATTERYLEVEL needs to be between 0 and 100.\n"); 
     $errorcode = 1;
}
if (($myhash{BATTDATE} ne "") && (length($myhash{BATTDATE}) > 8)) {
     push (@errorarray, "BATTDATE must be less than 8 characters.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSNAME} ne "") && (length($myhash{UPSNAME}) > 8)) {
     push (@errorarray, "UPSNAME must be less than 8 characters.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} ne netmaster) && ($myhash{SLAVE} ne "")) {
     push (@errorarray, "SLAVE directive cna only be used when UPSCLASS is netmaster\n."); 
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} ne netslave) && ($myhash{MASTER} ne "")) {
     push (@errorarray, "MASTER directive can only be used when UPSCLASS is netslave.\n"); 
     $errorcode = 1; 
}
if ((($myhash{UPSCLASS} eq netmaster) || ($myhash{UPSCLASS} eq netslave)) 
     && ($myhash{UPSMODE} ne net)) {
     push (@errorarray, "UPSMODE must be net when UPSCLASS is netmaster or netslave.\n"); 
     $errorcode = 1; 
}
if (($myhash{UPSCLASS} eq netslave) && ($myhash{DEVICE} ne "")) {
     push (@errorarray, "DEVICE directive is not used when the UPSCLASS is netslave.\n"); 
     $errorcode = 1; 
}
if ((!opendir(DIR, $myhash{LOCKFILE}) ) && ($noerror == 1)) {
     push (@errorarray, "LOCKFILE directory $myhash{LOCKFILE} does not exist.\n"); 
     $errorcode = 1; 
} else {
    close DIR;
}

print "<form method=post action=apcupsd_login.cgi>\n";
foreach $item (@fields) {
     @inputdata = split(/=/, $item);
     $inputdata[1] =~ s/\+/ /g;
     $pos = 0;
     while (($pos = index($inputdata[1], "%" , $pos)) != -1) {
          $ascii = hex(substr($inputdata[1], $pos + 1, 2)) ;
          substr($inputdata[1], $pos , 3) = pack("c", $ascii);
     }
     print "<input type=hidden name=\"$inputdata[0]\" value=\"$inputdata[1]\">\n";
}

# check for errors and if we have print them all and stop the program
if ($errorcode != 0) {
    print "<p><b>The following error(s) has(have) occured: </b>";
    
    print "<blockquote><ul>\n";

    foreach $error (@errorarray) {
        
        print "<li>", $error, "</li>\n";

    }

    print "</ul></blockquote>\n";

    print "<input type=submit value=\"Back To Login\">\n";

    print "</form>";

    exit -1;
} else {
    print "<P><B><font size=+1>The following data was written to your config file, \n" ;

    print "please verify that the data is correct before restarting  apcupsd.</font></b><p>\n";

    print "This config file is in your cgi-bin named: <b>$datafile</b><P>\n";

    print "<b><strong>Fields in blue should be checked thru '/sbin/apcaccess status' \n";

    print "before restarting server as they could damage your machine.</strong></b><p>\n";

}

# start the table
print "<table border=0 cellpadding=0 cellspacing=0>\n";

# this actually write the data to the screen
foreach $items (@fields) {
     if ($i%2 == 0) {
         $mycolor = $color[0];
     } else {
         $mycolor = $color[1];
     }
     @wanteddata = split(/=/, $items);
     $wanteddata[1] =~ s/\+/ /g;
     $pos = 0;
     while (($pos = index($wanteddata[1], "%" , $pos)) != -1) {
          $ascii = hex(substr($wanteddata[1], $pos + 1, 2)) ;
          substr($wanteddata[1], $pos , 3) = pack("c", $ascii);
     }

     push ( @mydata, $wanteddata[1] );
     
     if (($wanteddata[0] eq WAKEUP) || ($wanteddata[0] eq SLEEP)
          || ($wanteddata[0] eq LOTTRANSFER) || ($wanteddata[0] eq HITTRANSFER)
          || ($wanteddata[0] eq RETURNCHARGE) || ($wanteddata[0] eq BEEPSTATE)
          || ($wanteddata[0] eq OUTPUTVOLTS) || ($wanteddata[0] eq SELFTEST)
          || ($wanteddata[0] eq SENSITIVITY)) {
               if ($wanteddata[1] ne "") {
                    $mycolor = skyblue;
               }
     }
    
    # this is all for the GUI displaying of the data
    # if we have a field then we display it as is if we do not we put a # and then display it 
    my $displaydata;
    if ($mydata[$i] eq "") { 
        $displaydata = "#$wanteddata[0]";
    } else {
        $displaydata = "$wanteddata[0]";
    }
    # here we build the actual GUI
    if ((lc($wanteddata[0]) ne "submit") && (lc($wanteddata[0]) ne "username") && (lc($wanteddata[0]) ne "password")) {    
         print "<tr><td  bgcolor=",$mycolor,">", $displaydata, "</td><td bgcolor=",$mycolor,">",  $mydata[$i], "</td></tr>\n";
    }
    
    # here is the actual writing of the file
    # slave directive is special as there can be many
    if ("$wanteddata[0]" eq "SLAVE") {
        if ($mydata[$i] ne "") {
            $slaveno++;
            slaveprocess($wanteddata[0], $mydata[$i], $datafile, $slaveno);
        } else {
             if ($slaveno == 0) {
                 slaveprocess($wanteddata[0], $mydata[$i], $datafile, $slaveno);
                 $slaveno = 0;
             }
         }
     } else {
        # this is for writing all other data
         $slaveno = 0;
         updatefld($wanteddata[0], $mydata[$i], $datafile, $slaveno);
     } 
      
     $i++;
}

print "</table><br>\n";

print "<input type=submit value=\"Back To Login\">\n";

print "</form>\n";

print "</body></html>\n";

sub updatefld {
    my ($fld, $val, $namefile, $slvval) = @_;
    open(APCFILE, "< $namefile");
    my $linedata;
    my @array;
    my $slavecount = 1;
    while (!eof(APCFILE)) {
         $linedata = readline(*APCFILE);
         my ($data, $value) = split(/\s/, $linedata);
         my $datatmp = "#$fld";
         if (($data eq $fld) || ($data eq $datatmp)) {
            my $newdata = "$fld $val\n"; 
            if ($val ne "") {
                push(@array,$newdata);
            } else {
                push(@array,"#$newdata")
            }
         } else {
             push (@array, $linedata);
         }
    }
    close(APCFILE);
    my $item; 
    open(APCFILE, "> $namefile");
    foreach $item (@array) {
          print APCFILE $item;
    }
           close(APCFILE);}

sub slaveprocess {
    my ($fld, $val, $namefile, $slvval) = @_;
    my $linedata;
    my @array;
    my $slavecount = 1;
    my $switch = 0;
    open(APCFILE, "< $namefile");
    while (!eof(APCFILE)) {
         if (($switch ==0) || ($slavecount < $slvval)) {
              $linedata = readline(*APCFILE);
         }
         my ($data, $value) = split(/\s/, $linedata);
         my $datatmp = "#$fld";
         if (($data eq $fld) || ($data eq $datatmp) || ($switch == 1)) {
              $switch = 1;
              if(($slvval == 0) && ("$val" eq "") && ($slavecount == 1)) {
                  push(@array, "$datatmp\n");
              } else {
                  if(($slvval == $slavecount) && ("$val" ne "")) {
                      push(@array, "$fld $val\n");
                  } else {
                      if ($slavecount < $slvval) {
                          push(@array, $linedata);
                      } else {
                          $switch = 0;
                      }
                  }
              }
              $slavecount++;
          } else {
              push(@array, $linedata);
         }
    }
    close(APCFILE);
    my $item; 
    open(APCFILE, "> $namefile");
    foreach $item (@array) {
          print APCFILE $item;
    }
    close(APCFILE);
}
