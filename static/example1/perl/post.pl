#!/usr/bin/perl

use CGI;
use File::Copy;

my $cgi = CGI->new;
print $cgi->header;

if ($cgi->request_method eq "POST") {
    my $file_field = $cgi->upload("fileToUpload");
    if ($file_field) {
        my $targetDirectory = $ENV{'UPLOAD_DIR'};
        my $targetFile = $targetDirectory . $cgi->param("fileToUpload");

        if (-e $targetFile) {
            print "File already exists.";
        } else {
            open my $fh, '>', $targetFile or die "Error opening file: $!";
            binmode $fh;

            while (my $chunk = $file_field->getline) {
                print $fh $chunk;
            }

            close $fh;

            print "File uploaded successfully.";
        }
    } else {
        print "Error: " . $cgi->cgi_error;
    }
}