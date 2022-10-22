import os
import sys

print("-- [budext.js] [Innard Preparator] Running")
print("-- [budext.js] [Innard Preparator] -- Input file: " + sys.argv[1])
print("-- [budext.js] [Innard Preparator] -- Output header file: " + sys.argv[2])
print("-- [budext.js] [Innard Preparator] -- Output source file: " + sys.argv[3])

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

input_file = loadFile(sys.argv[1]);

output_file = "\""

input_file_lines = input_file.split('\n');
for line in input_file_lines:
	final_line = ""
	for char in line:
		if char == "\"":
			final_line += "\\\""
		elif char == "\\":
			final_line += "\\\\"
		else:
			final_line += char
	final_line += "\\n\\\n"
	output_file += final_line

output_file += "\";"

naems = sys.argv[1].split("/");
varname = "g_innard_" + naems[-1].replace(".", "_");

outnaems = sys.argv[2].split("/");

makeFile(sys.argv[2], "#pragma once\nextern const char *" + varname + ";")
makeFile(sys.argv[3], "#include <innards/" + outnaems[-1] + ">\nconst char *" + varname + " = " + output_file)

print("-- [budext.js] [Innard Preparator] Operation Successful")