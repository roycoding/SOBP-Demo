# g4score.py

# Roy Keyes (roy@unm.edu)
# Started 3 March 2011

# Read Geant4 scoring mesh csv files.
# Very limited so far.

import csv
import numpy as np

def getxz(fname):
    '''Return depth-quantity pair of numpy arrays from CSV file data. Assume cylindrical mesh data.'''

    f = open(fname)

    c = csv.reader(f)

    x1 = []
    x2 = []
    d = []

    for j in c:
        # Skip header (each line has #'s)
        if j[0][0] != '#':
            x1 += [float(j[0])]
            x2 += [float(j[1])]
            d += [float(j[3])]

    x1 = np.array(x1)
    x2 = np.array(x2)
    d = np.array(d)

    return x1,x2,d
