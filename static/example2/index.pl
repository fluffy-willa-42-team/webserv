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
		<form action="/post" method="post" enctype="multipart/form-data">
			<label for="hello">Drop file</label>
			<input type="file" id="hello" name="fileToUpload">

			<input type="submit" value="submit">
		</form>
		<form id="deleteForm">
			<label for="filename">Enter the filename to delete: </label>
			<input type="text" id="filename" name="filename">
			<button type="button" id="deleteButton">Delete</button>
		</form>

		<script>
			document.getElementById('deleteButton').addEventListener('click', function() {
				var xhr = new XMLHttpRequest();
				xhr.open('DELETE', '/delete', true);

				xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
				xhr.send(JSON.stringify({ filename: document.getElementById('filename').value }));
			});
		</script>
	</body>
</html>
HTML