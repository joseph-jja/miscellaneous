# this is a package for apcupsd configuration file parsing
# it stores all the data of the config file so that changing values 
# is easier to do
package apcupsd;

# we use a hash to store a line 
# it will contain the line type and data
# and possilby the line value and name
# line type will be comment, inactive field, or active field
# cfg_file will contain the entire file as an array of the hashes
my @cfg_file = [];

our $VERSION=0.1;

# all the fields that can be read in
# here we declair the an array for the fields we are going to use
my @allflds = ("UPSCABLE", "UPSTYPE","DEVICE","LOCKFILE","BATTERYLEVEL",
            "MINUTES", "TIMEOUT","ANNOY", "ANNOYDELAY", "NOLOGON",
            "NETSERVER", "SERVERPORT", "EVENTSFILE","STATTIME","STATFILE",
            "LOGSTATS","DATATIME", "SENSITIVITY","FACILITY","NETPORT",
            "UPSNAME","WAKEUP","SLEEP","LOTRANSFER", "HITRANSFER",
            "RETURNCHARGE","BEEPSTATE","LOWBATT","OUTPUTVOLTS",
            "UPSCLASS", "UPSMODE", "NETACCESS", "SELFTEST", "NETTIME",
            "MASTER", "SLAVE", "USERMAGIC");

# method to search a line for array values
sub search_array {
  my $val = shift;
  # given a line we loop through our array and figure out 
  # which field it is
  my %line_data = {};
  foreach $item (@allflds) { 
    if ( length($val) >= length(item) 
      && ( substr($val, 0, length($item) ) eq $item  
      || substr($val, 0, length($item) + 1 )  eq "#" . "$item" ) ) 
    { 
      # line is commented out
      if ( $val =~ m/^#/ ) { 
        $line_data{'type'} = 'inactive';
        my $rval = $val;
        $rval =~ s/#//g;
        my @parts = split(/\ /, $rval);
        if ( length(@parts) == 1 ) { 
          $line_data{'field_name'} = $rval;
        } else {
          $line_data{'field_name'} = $parts[0];
          $line_data{'field_value'} = $parts[1];
        }
      } else {
        # name value pair parse and split
        $line_data{'type'} = 'active';
        my @parts = split(/\ /, $val);
        $line_data{'field_name'} = $parts[0];
        $line_data{'field_value'} = $parts[1];
      }
    }
  } 
  if ( ! exists($line_data['type']) && $val =~ m/^#/ ) { 
    # line is a comment just save
    $line_data{'type'} = 'comment';
    $line_data{'field_value'} = $val;
  }
  return %line_data;
}

# read in the configuration file
# return an array
sub read_cfg_file {
  my $file = shift;
  
  open(CFGFILE, "< $file") or die "Could not find file $file\n";
  
  while ( !eof(CFGFILE) ) { 
    my $line = readline(*CFGFILE);
    my %line_data = search_array($line);
    push(@cfg_file, %line_data);
  }

  close(CFGFILE);

  return @cfg_file;
}

sub write_cfg_file {

}

return 1;
