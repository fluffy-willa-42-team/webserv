<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Check if the file was uploaded without errors
    if (isset($_FILES["fileToUpload"]) && $_FILES["fileToUpload"]["error"] == 0) {
        $targetDirectory = "upload/"; // Create a directory for storing uploaded files
        $targetFile = $targetDirectory . basename($_FILES["fileToUpload"]["name"]);

        // Check if the file already exists
        if (file_exists($targetFile)) {
            echo "File already exists.";
        } else {
            // Move the uploaded file to the target directory
            if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $targetFile)) {
                echo "File uploaded successfully.";
            } else {
                echo "Error uploading file.";
            }
        }
    } else {
        echo "Error: " . $_FILES["fileToUpload"]["error"];
    }
}
?>