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
print("Content-type: text/html\r\n\r\n")

script = """<script>
    document.getElementById('deleteButton').addEventListener('click', function() {
        var xhr = new XMLHttpRequest();
        xhr.open('DELETE', '/python/delete.py', true);

        xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
        xhr.send(JSON.stringify({ filename: document.getElementById('filename').value }));
    });
</script>"""

# Generate the HTML response
print(f""" 
<html>
<head>
    <title>Python index</title>
</head>
<body>
    <h1>Python index</h1>
    <h2>{message}</h2>
    <form action="/python/post.py" method="post" enctype="multipart/form-data">
        <label for="hello">Drop file</label>
        <input type="file" id="hello" name="fileToUpload">
        <input type="submit" value="submit">
    </form>
    <form id="deleteForm">
        <label for="filename">Enter the filename to delete: </label>
        <input type="text" id="filename" name="filename">
        <button type="button" id="deleteButton">Delete</button>
    </form>
    {script}
</body>
</html>
""")