#! /bin/bash

../bin/Linux-g++/sobp sobp.mac

python sobpplot.py SOBP-csv.txt

sudo python -m SimpleHTTPServer 80

