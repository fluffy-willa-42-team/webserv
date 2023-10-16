#!/usr/bin/python3

import sys
import json
import os

# Set the content type to JSON
print("Content-Type: application/json")

# Read the JSON data from the request body
try:
    content_length = int(os.environ["CONTENT_LENGTH"])
    request_body = sys.stdin.read(content_length)
    data = json.loads(request_body)
except (ValueError, KeyError):
    print("Status: 400 BAD REQUEST\r\n\r")
    print(json.dumps({"status": "error", "message": "Invalid JSON input"}))
    exit()

# Check if 'filename' parameter is in the JSON data
if 'filename' in data:
    filename = data['filename']
    directory = '/path/to/your/directory/'  # Change this to the directory where the file is located

    # Construct the full path to the file
    file_path = os.path.join(directory, filename)

    # Check if the file exists and delete it
    if os.path.exists(file_path):
        try:
            os.remove(file_path)
            print("Status: 204 SUCCESS\r\n\r")
            print(json.dumps({"status": "success", "message": "File deleted successfully"}))
        except Exception as e:
            print("Status: 404 FAILED\r\n\r")
            print(json.dumps({"status": "error", "message": f"Failed to delete the file: {str(e)}"}))
    else:
        print("Status: 404 FAILED\r\n\r")
        print(json.dumps({"status": "error", "message": "File not found"}))
else:
    print("Status: 404 FAILED\r\n\r")
    print(json.dumps({"status": "error", "message": "Missing 'filename' parameter"}))
