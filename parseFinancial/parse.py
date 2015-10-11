#!/usr/bin/env python3

import os
import numpy
import pickle

FILENAME = "data.pkl"

def save():
    data = {}

    DIR = "/home/denplusplus/Temp/Financial/quantquote_daily_sp500_83986/daily"
    for fname in os.listdir(DIR):
        parts = fname.split("_")
        r = numpy.genfromtxt(os.path.join(DIR, fname), delimiter=',', dtype=None, names=None)
        data[parts[1]] = r

    with open(FILENAME, "wb") as fOut:
        pickle.dump(data, fOut)

data = pickle.load(open(FILENAME, "rb"))
