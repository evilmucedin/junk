#!/usr/bin/env python3

import numpy
import pickle as pkl
import random

from collections import OrderedDict

def tokenize(sentence):
    return sentence.split()

def sentences(path):
    count = 0
    with open(path, 'r') as f:
        for line in f:
            count += 1
            if count > 10000:
                break
            yield line.strip()

def build_dict(path):
    print('Building dictionary..', end="")
    wordcount = dict()
    for ss in sentences(path):
        for w in tokenize(ss):
            if w not in wordcount:
                wordcount[w] = 1
            else:
                wordcount[w] += 1

    counts = list(wordcount.values())
    keys = list(wordcount.keys())

    sorted_idx = numpy.argsort(counts)[::-1]

    worddict = dict()

    for idx, ss in enumerate(sorted_idx):
        worddict[keys[ss]] = idx + 2  # leave 0 and 1 (UNK)

    print(numpy.sum(counts), ' total words ', len(keys), ' unique words')

    return worddict

def grab_data(path, dictionary):
    ss = [tokenize(s) for s in sentences(path)]
    seqs = []
    labels = []
    for idx, words in enumerate(ss):
        coded = [dictionary[w] if w in dictionary else 1 for w in words]
        seqs.append(coded)
        labels.append(1)
        for i in range(random.randint(0, 5)):
            coded2 = coded[:]
            coded2[random.randint(0, len(coded2) - 1)] = random.randint(0, len(dictionary) - 1)
            labels.append(0)
    return seqs, labels

def main():
    filenameInput = "EnUSQueries20150901.2000.filtered.log.uniq"
    dictionary = build_dict(filenameInput)

    all_x, all_y = grab_data(filenameInput, dictionary)

    train_x = []
    train_y = []
    test_x = []
    test_y = []

    for x, y in zip(all_x, all_y):
        if random.randint(0, 10) < 8: 
            train_x.append(x)
            train_y.append(y)
        else:
            test_x.append(x)
            test_y.append(y)

    f = open('queries.pkl', 'wb')
    pkl.dump((train_x, train_y), f, -1)
    pkl.dump((test_x, test_y), f, -1)

    revDict = {}
    for k, v in dictionary.items():
        revDict[v] = k
    pkl.dump(revDict, f, -1)
    
    f.close()

    f = open('queries.dict.pkl', 'wb')
    pkl.dump(dictionary, f, -1)
    f.close()

if __name__ == '__main__':
    main()
