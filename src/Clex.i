%module Clex_module
%include "std_string.i"

typedef std::string string;

%{
#include "Clex.h"
%}
%include "Clex.h"
