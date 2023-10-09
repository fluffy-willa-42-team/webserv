#!/usr/bin/perl
use strict;
use warnings;
use CGI;

# Create a CGI object
my $cgi = CGI->new;

# Get the filename from the form input
my $filename = $cgi->param('filename');

# Check if the filename is provided
if (!$filename) {
    print $cgi->header;
    print "Please enter a filename to delete.";
    exit;
}

# Define the directory where files are stored (change this to your directory)
my $upload_dir = $ENV{'UPLOAD_DIR'};

# Construct the full path to the file
my $full_path = $upload_dir . $filename;

# Attempt to delete the file
if (unlink $full_path) {
    print $cgi->header;
    print "File '$filename' has been deleted.";
} else {
    print $cgi->header(-status => '404 Not Found');
    print "File '$filename' not found or unable to delete.";
}