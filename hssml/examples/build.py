import os
import sys

print("-- [budext.js] [Example Build] Running")

def buildFile(filein, fileout):
	naems = fileout.split("/");
	if len(naems) > 1:
		os.makedirs("build/examples/"+fileout[0 : -len(naems[-1])], exist_ok=True)
	os.chdir("build/hssml")
	os.system(("hssml.exe " if os.name == 'nt' else "./hssml ") + "../../hssml/examples/"+filein + " ../examples/"+fileout)

buildFile("simple_website/index.scss", "simple_website/index.html")

print("-- [budext.js] [Example Build] Success")