#!/usr/bin/env python3

import os
import sys

if __name__ == '__main__':
    testname = 'Tests/{}'.format(sys.argv[1])
    cmd = f'Bin/assembler {testname}.s {testname}.out && Debug/stackmachine {testname}.out'
    print(cmd)
    os.system(cmd)
