use CGI;

my $cgi = CGI->new;
my $message;
if ($ENV{'REDIRECT_STATUS'} eq '200'){
	$message = 'This is a Perl generated message for GET';
} else {
	$message = 'This is a Perl generated message for redirect';
}

print $cgi->header;
print <<HTML;
<html>
	<head>
		<title>Perl index</title>
	</head>
	<body>
		<h1>Perl index</h1>
		<h2>$message</h2>
		<form action="/perl/postfile.pl" method="post" enctype="multipart/form-data">
			<label for="hello">Drop file</label>
			<input type="file" id="hello" name="fileToUpload">

			<input type="submit" value="submit">
		</form>
		<form action="/perl/delete.pl" method="POST">
			<label for="filename">Enter the filename to delete: </label>
			<input type="text" name="filename">
			<input type="submit" value="Delete">
		</form>
	</body>
</html>
HTML