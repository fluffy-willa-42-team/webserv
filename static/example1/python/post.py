#!/usr/bin/env python3
import cgi
import os

# Create an instance of the FieldStorage class to parse the form data
form = cgi.FieldStorage()

# Print the CGI header
print("Content-type: text/html\r\n\r\n")

# Define the target directory where uploaded files will be stored
target_directory = "/home/willa/19/webserv/static/upload/"

# Check if the request method is POST
if os.environ.get("REQUEST_METHOD", "") == "POST":
    if "fileToUpload" in form:
        file_field = form["fileToUpload"]
        # Get the filename from the form data
        filename = os.path.basename(file_field.filename)

        # Construct the full path to the target file
        target_file = os.path.join(target_directory, filename)

        if os.path.exists(target_file):
            print("File already exists.")
        else:
            try:
                # Open the target file for writing
                with open(target_file, "wb") as f:
                    # Read and write the uploaded file in chunks
                    while True:
                        chunk = file_field.file.read(8192)
                        if not chunk:
                            break
                        f.write(chunk)

                print("File uploaded successfully.")
            except Exception as e:
                print("Error:", str(e))
    else:
        print("Error: No file uploaded.")
