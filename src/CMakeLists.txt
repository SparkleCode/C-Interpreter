# require modern c++
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_EXTENSIONS OFF)

project(SparkleCodeMain)
add_subdirectory(scanner)

add_custom_command(
	OUTPUT Expr.h
	COMMAND python "${CMAKE_SOURCE_DIR}/src/tool/genExpr.py" "${CMAKE_SOURCE_DIR}/src"
	)

add_library(SparkleCodeMain SparkleCode.cpp Expr.h AstPrinter.h)
target_link_libraries(SparkleCodeMain Scanner)