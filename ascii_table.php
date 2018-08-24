<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<meta name="Author" content="Joseph Acosta">
<META NAME="ROBOTS" CONTENT="NOARCHIVE">
<title>My ASCII Table</title>
<style type="" type="text/css">
<!--
table { border:1px solid black; width}
table.key { border:none;}
table.key td, table.key th { border-bottom: solid black 1px; }
table.key td { border-left: solid black 1px;border-right: solid black 1px; }
th { vertical-align:top; text-align:center; }
td { vertical-align:top; text-align:left; white-space: nowrap; }
th, td { padding-left:4px; padding-right:4px;
		padding-top:2px; padding-bottom:2px;  }

tr.even_odd_0 { background-color:#ffefff} 
tr.even_odd_1 { background-color:#ccceff;} 

.decimal { border: 1px solid #ffaaff; }
.hex { border: 1px solid green }
.octal { border: 1px solid magenta}
.binary { border: 1px solid orange; }
.char { border: 1px solid red;  }

-->
</style>
</head>
<body>

ASCII Table<P>
<table class="key"><th>key</th>
<tr><td>
dec = decimal
</td></tr><tr><td>
chr = character (printable or non printable)
</td></tr><tr><td>
hex = hexidecimal
</td></tr><tr><td>
oct = octal
</td></tr><tr><td>
bin = binary
</td></tr>
</table>

<br>

<?php
// This sets up the array that we use
// non printable charachters
$nonprintchardata = array("NUL (null)", "SOH (start of heading)", "STX (start of text)", 
					"ETX (end of text)", "EOT (end of transmission)", 
					"ENQ (enquiry)", "ACK (acknowledge)", "BEL (bel)", 
					"BS (backspace)", "TAB (horizontal tab)", 
					"LF (NL line feed, new line)", "VT (verticle tab)", 
					"FF (NP form feed, new page)", "CR (carriage return)", "SO (shift out)", 
					"SI (shift in)", "DLE (data link exchange)", "DC1 (device control 1)", 
					"DC2 (device control 2)", "DC3 (device control 3)", "DC4 (device control 4)", 
					"NAK (negitive acknowledge)", "SYN (synchronous idle)", 
					"ETB (end of trans. block)", "CAN (cancel)", "EM (end of medium)", 
					"SUB (substitute)", "ESC (escape)", "FS (file separator)", "GS (group separator)", 
					"RS (record separator)", "US (unit separator)", "SPACE" );

// printable characters
for ($i=33; $i<127; $i++) {
    $nonprintchardata[$i] = chr($i); 
}

// the last non printable character in the first 127
$nonprintchardata[127] = "DEL";

// this is the table header
$tableheader = "<tr><th class=\"decimal\">dec</th>";
$tableheader .= "<th class=\"char\">chr</th>";
$tableheader .= "<th class=\"hex\">hex</th>";
$tableheader .= "<th class=\"octal\">oct</th>";
$tableheader .= "<th class=\"binary\">bin</th></tr>";
?>

<table><tr><td>
<table width="350px">

<?php
print $tableheader; 
$break = 127 / 3;
for ($i=0; $i<128; $i++) {

     $cssindex = $i % 2;
	
     $line = "<tr class=\"even_odd_$cssindex\"><td class=\"decimal\">$i</td>";
		$line .= "<td class=\"char\">" . $nonprintchardata[$i] . "</td>";
		$line .= "<td class=\"hex\">" . dechex($i) . "</td>";
		$line .= "<td class=\"octal\">" . decoct($i) . "</td>";
		$line .= "<td class=\"binary\">" . decbin($i) . "</td></tr>";
    print $line;
    if (  $i % 43 == 42 ) {
        print "</table></td><td><table>$tableheader\n";
    }
	
}
?>
</table>
</td></tr></table>

<P>Extended ASCII Table<P>

<table><tr><td>

<table>
<?php
// added as there is no chr yet for these
// this is the table header
$tableheader = "<tr><th class=\"decimal\">dec</th>";
$tableheader .= "<th class=\"hex\">hex</th>";
$tableheader .= "<th class=\"octal\">oct</th>";
$tableheader .= "<th class=\"binary\">bin</th></tr>";

print $tableheader; 

for ($i=128; $i<=255; $i++) {

	$cssindex = $i % 2;
	
	$line = "<tr class=\"even_odd_$cssindex\"><td class=\"decimal\">$i</td>";
	$line .= "<td class=\"hex\">" . dechex($i) . "</td>";
	$line .= "<td class=\"octal\">" . decoct($i) . "</td>";
	$line .= "<td class=\"binary\">" . decbin($i) . "</td></tr>";
    print $line;
	if (($i%32 == 31) && ($i != 255)) {
	    print "</table></td><td><table>$tableheader\n";
	}
}

?>
</table>
</td></tr></table>
</body>
</html>


