# binder.py
# NaNoGenMo 2020 - Hoplites Comic - yvnat
# binds the comic into a readable whole

import sys
import os

dir = os.path.dirname(os.path.realpath(sys.argv[0]))+"/";

template = "ERROR"

path = "template.html";

try:
    file = open(dir+path, "r");
    template = file.read();
    file.close();
except FileNotFoundError:
    print("No such file", dir+path);

pages_dir = dir+"pages/";

dirs = list(os.walk(pages_dir))[0][1]
lastdir = max([int(i) for i in dirs]);
for directory in dirs:
    page = template;
    page = page.replace("@@PAGENUM", directory);
    
    prevdir = int(directory)-1;
    if (prevdir >= 0):
        prevlink = '<a href="./../'+str(prevdir)+'/page.html" class="button">Previous</a>';
    else:
        prevlink = '<a class="button"> - </a>';
    page = page.replace("@@PREVLINK", prevlink);
    
    nextdir = int(directory)+1;
    if (nextdir <= lastdir):
        nextlink = '<a href="./../'+str(nextdir)+'/page.html" class="button">Next</a>';
    else:
        nextlink = '<a class="button"> - </a>';
    page = page.replace("@@NEXTLINK", nextlink);
    
    page_path = dir+"pages/"+directory+"/page.html"
    file = open(page_path, "w");
    file.write(page);
    file.close();
    print("wrote", page_path);
