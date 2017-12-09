"""
generate ast classes
"""
import sys

def define_type(file, base_name, class_name, field_list):
    """
    write type class to file
    """
    file.write("\n")
    file.write("class " + class_name + " : public " + base_name + " {\n")

    file.write(" public:\n")

    # field definitions
    fields = field_list.split(', ')
    for field in fields:
        if " " in field:
            file.write("  " + field + ";\n")
        else:
            file.write("  Expr* " + field + ";\n")

    file.write("\n")

    # constructor
    file.write("  " + class_name + "(" + field_list + ") {\n")
    # store parameters in fields
    for field in fields:
        name = field.split(" ")[-1]
        file.write("    this->" + name + " = " + name + ";\n")
    file.write("  }\n")

    # visitor
    file.write('\n')
    file.write("  void accept(IVisit" + base_name + "* visitor) {\n")
    file.write("    visitor->visit" + class_name + base_name + "(this);\n")
    file.write("  }\n")

    file.write("};\n")

def define_visitor(file, base_name, types):
    """
    write visitor interface to file
    """
    file.write("\n")

    # forward defs
    for line in types:
        class_name = line.split(':', 1)[0].strip()
        file.write("class " + class_name + ";\n")

    # interface
    file.write("\n")
    file.write("class IVisit" + base_name + " {\n")
    file.write(" public:\n")
    for line in types:
        class_name = line.split(':', 1)[0].strip()
        file.write("  virtual void visit" + class_name + base_name + "(")
        file.write(class_name + "* " + base_name.lower() + ") = 0;\n")
    file.write("};\n")

def define_ast(base_name, types):
    """
    generate ast from list of types
    """
    file = open(sys.argv[1] + '/' + base_name + '.h', "w")

    file.write("// generate file\n")
    file.write("// copyright 2017\n")
    file.write("#pragma once\n")
    file.write("#include <vector>\n")
    file.write("#include <string>\n")
    file.write("#include <iostream>\n")
    file.write('#include "./scanner/token.h"\n')

    define_visitor(file, base_name, types)

    file.write("\n")
    file.write("class " + base_name + " {\n")
    file.write("  // abstract base class for " + base_name + "\n")
    file.write(" public:\n")
    file.write("  virtual void accept(IVisit" + base_name + "* visitor) = 0;\n")
    file.write("};\n")

    for line in types:
        class_name = line.split(':', 1)[0].strip()
        fields = line.split(':', 1)[1].strip()
        define_type(file, base_name, class_name, fields)

    file.close()

COMMANDS = [
    "Binary   : Expr* left, Token op, Expr* right",
    "Grouping : Expr* expression",
    "Literal  : std::string value",
    "Unary    : Token op, Expr* right"
]

define_ast("Expr", COMMANDS)
