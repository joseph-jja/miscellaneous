
##############################################
# checkPass
#
# description: 
#  this checks the password
#
# inputs:
#  $passwd - password
#  $uname - user name
#  $pwdfile - location of the password file
#
# returns:
#  1 if pasword found
#  0 if password not found
##############################################
sub checkPass {
    ($passwd, $uname, $pwdfile) = @_;
    if (($passwd eq "") || ($uname eq "")) {
       return 0; 
    } else {
        my $encdata = crypt($passwd, $uname);
        my $udata = $uname;
        my $userdata = "$udata $encdata\n";
        @array = "";
        open(PWDFILE, "< $pwdfile");
        while (!eof(PWDFILE)) {
            $password = readline(*PWDFILE);
            if ($password eq $userdata) {
                return 1;
            }   
        }
        close(PWDFILE); 
    }
	return 0;
}

##############################################
# updatePass
#
# description: 
#  this updates the password
#
# inputs:
#  $passwd - password
#  $uname - user name
#  $newpass - the new password
#  $confirm - the confirmed password 
#  $pwdfile - location of the password file
#
# returns:
#  1 if updated
#  0 if not updated
##############################################
sub updatePass {
    ($passwd, $uname, $newpass, $confirm, $pwdfile) = @_;
	$true = 0;
    if (($passwd) && ($newpass) && ($newpass eq $confirm)) {
        my $encdata = crypt($passwd, $uname);
        my $udata = $uname;
        my $userdata =  "$udata $encdata\n";
        my @array = "";
             
		# search for the password uname
        open(PWDFILE, "< $pwdfile");
		while (!eof(PWDFILE)) {
            $password = readline(*PWDFILE);
            if ($password eq $userdata) {
                my $newpwd = crypt($newpass, $uname);   
                my $datapwd = "$udata $newpwd\n";           
                push(@array,$datapwd);
				# we found it true = 1
				$true = 1;
            } else {
                push (@array, $password);
            }
        }
        close(PWDFILE);
		    
	    # only write it if we have a new password
        if ($true) {
            open(PWDFILE, "> $pwdfile");
        	foreach $item (@array) {
               print PWDFILE $item;
            }
			close(PWDFILE);
	    }          
    }
	return $true;
}

return 1;
