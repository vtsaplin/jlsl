#CPU=linux
CPU=ppc4

include /ps/src/dsc/co/Make.auto

PFUNCS = ./predefined_functions

SRCS =  test.cpp script_parser.cpp script_scope.cpp script_predefined_function.cpp \
		collector.cpp script_object.cpp script_string_object.cpp script_array_object.cpp \
		script_exception.cpp script_code_fragment.cpp script_enumerable_object.cpp \
		script_collection_object.cpp script_container.cpp \
		$(PFUNCS)/script_math.cpp \
		$(PFUNCS)/script_convert.cpp \
		$(PFUNCS)/script_io.cpp \
		$(PFUNCS)/script_vme.cpp

all: test.$(CPU)
	mv test.$(CPU) jlsl

test.$(CPU): $(SRCS)

clean:
	rm jlsl

