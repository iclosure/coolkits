#!/usr/bin/python3

# -*- coding: utf-8 -*-

'''
xcopy for any platform:

using:
==================================================
if __name__ == "__main__":
    import sys, os
    sys.path.insert(0, r"/path/to/linuxxcopy")
    import xcopy
    filters = ["*.py"]
    xc = xcopy(os.getcwd(), "/tmp/test", filters)
==================================================
'''

import os, shutil, fnmatch

class Xcopy:
    def __init__(self, src, dst, filters=[]):
        self.filters = filters
        self.excludeFilters = ["*_p.h", "precomp.h"]
        self.copytree(src, dst)
    
    def copytree(self, src, dst):
        '''
        based on shutil.copytree()
        '''
        names = os.listdir(src)
        if not os.path.isdir(dst):
            os.makedirs(dst)
        
        errors = []
        for name in names:
            srcname = os.path.join(src, name)
            dstname = os.path.join(dst, name)
            if os.path.isdir(srcname):
                if name == "private":
                    continue;
                self.copytree(srcname, dstname)
            elif os.path.isfile(srcname):
                if self.filterExclude(name):
                    continue;
                if self.filterExclude(name):
                    continue;
                if self.filtername(name):
                    print("copy %s" % srcname)
                    shutil.copy2(srcname, dstname)
        shutil.copystat(src, dst)
    def filtername(self, filename):
        for filter in self.filters:
            if fnmatch.fnmatch(filename, filter):
                return True
        return False
    def filterExclude(self, filename):
        for filter in self.excludeFilters:
            if fnmatch.fnmatch(filename, filter):
                return True
        return False

def execute(argv):
    if (len(argv) != 4):
        return
    return Xcopy(argv[1], argv[2], [argv[3]])

if __name__ == "__main__":
    import sys
    execute(sys.argv)