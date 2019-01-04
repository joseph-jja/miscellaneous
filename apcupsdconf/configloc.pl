
# here are the locations of the config files, they are in an array
# the infile is the default file or the current system config file
# the default config file that comes standard with apcupsd
# the default server config file, the default slave config file

$infile = "cfgfiles/apcupsd.conf";
$defaultcfg = "cfgfiles/apcupsd.default.conf";
$servercfg = "cfgfiles/apcupsd.master.conf";
$slavecfg = "cfgfiles/apcupsd.slave.conf";

# this is the location of the output file
$datafile = $infile;

# location of the password file
$apcpwdfile = "./.apcpwdfile";

# location of the help file
$helpfile = "cfgfiles/configure.html";

# size of text fields
$tsize = 30;

# this is the location of the image file
$imageloc = "apcupsd.gif";

# I hope that eventually that this will be the adress for bugs apcupsd-devel\@ro.com 
$mailbugs = "joeja\@mindspring.com";

# colors of the rows
@color = ("pink", "yellow");

# background color of the windows
$bgcolor = "#efefff";
