#!/usr/bin/env python3
import cgi
import os

# Create a CGI object
cgi_form = cgi.FieldStorage()

# Get the filename from the form input
filename = cgi_form.getvalue('filename')

# Check if the filename is provided
if not filename:
    print("Content-type: text/html\n")
    print("Please enter a filename to delete.")
else:
    # Define the directory where files are stored (change this to your directory)
    upload_dir = '/home/willa/19/webserv/static/upload/'

    # Construct the full path to the file
    full_path = os.path.join(upload_dir, filename)

    # Attempt to delete the file
    try:
        os.remove(full_path)
        print("Content-type: text/html\n")
        print(f"File '{filename}' has been deleted.")
    except FileNotFoundError:
        print("Content-type: text/html\n")
        print(f"File '{filename}' not found.")
    except Exception as e:
        print("Content-type: text/html\n")
        print(f"Error deleting file '{filename}': {e}")
