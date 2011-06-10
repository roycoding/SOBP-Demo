SOBP-demo
by Roy Keyes (roy.coding@gmail)

SOBP-demo is a demo program that produces a spread-out Bragg peak from a proton beam in water. It is intended to be a very simple demo of Geant4 run on an Amazon EC2 server, displaying the result as a webpage, but can be run locally or on any server.

Once compiled, the demo program should be called as:

./sobp-demo.sh

The resulting plot will then be viewable with a webbrowser at

http://localhost

or 

http://127.0.0.1

or

the http address of the server on port 80.

Kill the webserver manually with Ctrl-C (or equivalent).


The results file is written out in CSV format and saved as SOBP-csv.txt.


SOBP-demo was develeped on Geant4.9.3 and tested on Geant4.9.4.
It also depends on Python and Matplotlib (Python plotting libary).




Known issues (a.k.a. BUGS!!!)
- The CSV output from command based scoring changed between 4.9.3 and 4.9.4, so this demo will break if you use it between those systems. You need to know which column will have the depth coordinated of the depth-dose curve:
    4.9.3: column 2
    4.9.4: column 1
