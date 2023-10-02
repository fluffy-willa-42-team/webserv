<html>
	<head>
		<title>PHP index</title>
	</head>
	<body>
		<h1>PHP index</h1>
		<h2>
			<?php
			if ($_SERVER['REDIRECT_STATUS'] === '200') {
				print 'This is a php generated message for get';
			} else {
				print 'This is a php generated message for redirect';
			}
			?>
		</h2>
	</body>
</html>

<style>
	body {
		background-color: goldenrod;
	}

	h1 {
		color: black;
		text-align: center;
		padding: 5em;
	}
</style>
