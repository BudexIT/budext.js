import os
import sys

print("-- [budext.js] [Innard Preparator] Running")
print("-- [budext.js] [Innard Preparator] -- Input file: " + sys.argv[1])
print("-- [budext.js] [Innard Preparator] -- Output file: " + sys.argv[2])

# Recursively creates a file with custom contents in it
def makeFile(name, contents=""):
	naems = name.split("/");
	if len(naems) > 1:
		os.makedirs(name[0 : -len(naems[-1])], exist_ok=True)
	with open(name, 'w') as fp:
		fp.write(contents)

# Opens and dumps a file into a string
def loadFile(name):
	data = ""
	with open(name, "r") as fp:
		data = fp.read()
	return data

str = loadFile(sys.argv[1]);
makeFile(sys.argv[2], str)

print("-- [budext.js] [Innard Preparator] Operation Successful")