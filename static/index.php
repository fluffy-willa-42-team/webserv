<?php
if ($_SERVER['REDIRECT_STATUS'] === '200') {
    echo "This is the initial request.";
} else {
    echo "This is a redirected request.";
}
?>
<html>
	<head>
		<title>PHP index</title>
	</head>
	<body>
		<h1>PHP index</h1>
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
