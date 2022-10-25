import os
import sys

print("-- [budext.js] [Example Build] Running")

def buildFile(filein, fileout):
	naems = fileout.split("/");
	if len(naems) > 1:
		os.makedirs(fileout[0 : -len(naems[-1])], exist_ok=True)
	os.chdir("build/hssml")
	os.system("hssml.exe " + filein + " " + fileout)


buildFile("hssml/examples/simple_website/index.scss", "build/examples/simple_website/index.html")