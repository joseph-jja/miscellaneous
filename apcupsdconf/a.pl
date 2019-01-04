

use apcupsd;

@data = apcupsd::read_cfg_file('cfgfiles/apcupsd.conf');

foreach $item (@data) { 
   %h = $item;
   #print $h{'type'} . "\n";
    while ( ( $key, $val ) = each(%h) ) { 
	print $key ."\n";
    }
}

