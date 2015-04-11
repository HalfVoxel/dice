import csv
import os
import time

numfiles = 682

def partition():
    with open('/tmp/results.csv', 'r') as csvfile:
        reader = csv.reader(csvfile)
        for i in range(numfiles):
            part = []
            try:
                for j in range(1000):
                    part.append(next(reader))
                part = sorted(part, key=lambda tup: tup[20])
                print("sorted", i, j, "first:", part[0][20])
            except StopIteration:
                pass

            with open('/tmp/sorting'+str(i)+'.csv', 'w') as outfile:
                writer = csv.writer(outfile)
                writer.writerows(part)
            

def merge():
    for i in range(1, numfiles):
        print("i=", i)
        with open('/tmp/sorting0.csv', 'r') as file1:
            with open('/tmp/sorting'+str(i)+'.csv', 'r') as file2:
                with open('/tmp/sortingtmp.csv', 'w') as outfile:
                    read1 = csv.reader(file1)
                    read2 = csv.reader(file2)
                    row1 = next(read1)
                    row2 = next(read2)
                    writer = csv.writer(outfile)

                    while (row1 is not None) or (row2 is not None):
                        if (row2 is None) or ((row1 is not None) and row1[20]<row2[20]):
                            writer.writerow(row1)
                            try:
                                row1 = next(read1)
                            except StopIteration:
                                row1 = None
                        else:
                            writer.writerow(row2)
                            try:
                                row2 = next(read2)
                            except StopIteration:
                                row2 = None

        os.remove('/tmp/sorting0.csv')
        os.remove('/tmp/sorting'+str(i)+'.csv')
        os.rename('/tmp/sortingtmp.csv', '/tmp/sorting0.csv')

    os.rename('/tmp/sorting0.csv', '/tmp/results-sorted.csv')


partition()
merge()
