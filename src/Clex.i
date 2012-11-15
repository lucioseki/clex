%module Clex_module
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"

typedef std::string string;
namespace std{
    %template(StrVector) vector<string>;
    %template(StrPair)  pair<string, string>;
    %template(StrPairVector) vector<pair<string, string> >;
}
typedef std::vector<std::string> vector<string>;
typedef std::vector<std::pair < std::string, std::string> > vector<pair<string, string> >;

%{
#include "Clex.h"
%}
%include "Clex.h"
