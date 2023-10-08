#!/usr/bin/env python3
import cgi

# Create an instance of the FieldStorage class to parse the form data
form = cgi.FieldStorage()

# Get the value of the REDIRECT_STATUS environment variable
redirect_status = form.getfirst("REDIRECT_STATUS", "")

# Determine the message based on REDIRECT_STATUS
if redirect_status == '200':
    message = 'This is a Python generated message for GET'
else:
    message = 'This is a Python generated message for redirect'

# Print the CGI header
print("Content-type: text/html\n")

# Generate the HTML response
print(""" 
<html>
<head>
    <title>Python index</title>
</head>
<body>
    <h1>Python index</h1>
    <h2>{}</h2>
    <form action="/python/post.py" method="post" enctype="multipart/form-data">
        <label for="hello">Drop file</label>
        <input type="file" id="hello" name="fileToUpload">
        <input type="submit" value="submit">
    </form>
    <form action="/python/delete.py" method="post">
        <label for="filename">Enter the filename to delete: </label>
        <input type="text" name="filename">
        <input type="submit" value="Delete">
    </form>
</body>
</html>
""".format(message))