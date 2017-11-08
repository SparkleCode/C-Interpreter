import sys
def defineType(file, baseName, className, fieldList, visitorTypes, lentypes):
	file.write("\n")
	file.write("class " + className + " : public " + baseName + " {\n")

	file.write(" public:\n")

	# field definitions
	fields = fieldList.split(', ')
	for field in fields:
		if " " in field:
			file.write("  " + field + ";\n")
		else:
			file.write("  Expr* " + field + ";\n")

	file.write("\n")

	# constructor
	depth = len([x.strip() for x in fields if(" " not in x.strip())])
	for i in range(pow(lentypes, depth)):
		if len(fields) == 1:
			file.write("  explicit ")
		else:
			file.write("  ")
		file.write(className + "(")
		for j,f in enumerate(fields):
			if " " in f:
				file.write(f)
			if not j == len(fields)-1:
				file.write(", ")
		file.write(") {\n")

		# store parameters in fields
		for field in fields:
			name = field.split(" ")[-1]
			file.write("    this->" + name + " = " + name + ";\n")
		file.write("  }\n")

	# visitor
	for t in visitorTypes:
		typeClass = t.split(':', 1)[1].strip()
		typeName = t.split(':', 1)[0].strip()
		file.write("\n")
		file.write("  " + typeClass + " accept(IVisit" + baseName + typeName + "* visitor) override {\n")
		file.write("    std::cout << \"" + className + "\" << std::endl;\n")
		file.write("    return visitor->visit" + className + baseName + "(this);\n")
		file.write("  }\n")

	file.write("};\n")

def defineVisitor(file, baseName, types, visitorTypes):
	file.write("\n")

	# forward defs
	for line in types:
		className = line.split(':', 1)[0].strip()
		file.write("class " + className + ";\n")

	for t in visitorTypes:
		typeClass = t.split(':', 1)[1].strip()
		typeName = t.split(':', 1)[0].strip()

		file.write("\n")
		file.write("class IVisit" + baseName + typeName + " {\n")
		file.write(" public:\n")
		for line in types:
			className = line.split(':', 1)[0].strip()
			file.write("  virtual " + typeClass + " visit" + className + baseName + "(")
			file.write(className + "* " + baseName.lower() + ") = 0;\n")
		file.write("};\n")

def defineAst(baseName, types, visitorTypes):
	file = open(sys.argv[1] + '/' + baseName + '.h', "w")

	file.write("// generate file\n")
	file.write("// copyright 2017\n")
	file.write("#pragma once\n")
	file.write("#include <vector>\n")
	file.write("#include <string>\n")
	file.write("#include <iostream>\n")

	defineVisitor(file, baseName, types, visitorTypes)

	file.write("\n")
	file.write("class " + baseName + " {\n")
	file.write("  // abstract base class for " + baseName + "\n")
	file.write(" public:\n")
	for t in visitorTypes:
		typeClass = t.split(':', 1)[1].strip()
		typeName = t.split(':', 1)[0].strip()
		file.write("  virtual " + typeClass + " accept(IVisit" + baseName + typeName + "* visitor) = 0;\n")
	file.write("};\n")

	for line in types:
		className = line.split(':', 1)[0].strip()
		fields = line.split(':', 1)[1].strip()
		defineType(file, baseName, className, fields, visitorTypes, len(types))

	file.close();

command = [
	"Binary   : left, Token op, right",
	"Grouping : expression",
	"Literal  : std::string value",
	"Unary    : Token op, right"
]
visitorTypes = [
	"String : std::string",
]
defineAst("Expr", command, visitorTypes)
