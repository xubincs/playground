#!/usr/bin/python

import sys
import subprocess
import time

def getRXBytes(name):

    p = subprocess.Popen(['ifconfig'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = p.communicate()

    bingo = False
    stake = 'RX bytes:'
    num = 0
    for line in stdout.split('\n'):
        if line.startswith(name):
            bingo = True
            continue
            
        pos = line.find(stake)
        if pos > 0 and bingo:
            sub = line[pos + len(stake):]
            num = int(sub[0: sub.find(' ')])
            bingo = False

    return num

if __name__ == '__main__':

#    getRXBytes('eth0')
    while True:
        bytes1 = getRXBytes('eth0')
        time.sleep(1)
        bytes2 = getRXBytes('eth0')
        print "%.2f kb/s"  % (8 * (bytes2 - bytes1) / 1000.0)

