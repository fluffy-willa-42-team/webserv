use CGI;

my $cgi = CGI->new;

print $cgi->header;
print <<HTML;
<html>
	<head>
		<title>Perl index</title>
	</head>
	<body>
		<h1>Perl index</h1>
		<h2>
			<?perl
			if ($ENV{'REDIRECT_STATUS'} eq '200') {
				print 'This is a Perl generated message for GET';
			} else {
				print 'This is a Perl generated message for redirect';
			}
			?>
		</h2>

		<form action="/perl/postfile.pl" method="post" enctype="multipart/form-data">
			<label for="hello">Drop file</label>
			<input type="file" id="hello" name="fileToUpload">

			<input type="submit" value="Hello">
		</form>
	</body>
</html>
HTML