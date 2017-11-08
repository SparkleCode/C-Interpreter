# require modern c++
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_EXTENSIONS OFF)

project(Scanner)

add_custom_command(
	OUTPUT Expr.h
	COMMAND python "${CMAKE_SOURCE_DIR}/src/tool/genExpr.py" "${CMAKE_SOURCE_DIR}/src"
	)

add_library(Scanner Token.cpp Scanner.cpp Expr.h)