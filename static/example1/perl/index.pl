use CGI;

my $cgi = CGI->new;
my $message;
if ($ENV{'REDIRECT_STATUS'} eq '200'){
	$message = 'This is a Perl generated message for GET';
} else {
	$message = 'This is a Perl generated message for redirect';
}

my $test = `date`;

print $cgi->header;
print <<HTML;
<html>
	<head>
		<title>Perl index</title>
	</head>
	<body>
		<h1>Perl index</h1>
		<h2>$message</h2>
		<h2>$test</h2>
	</body>
</html>
HTML