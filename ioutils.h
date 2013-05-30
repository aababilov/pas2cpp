//---------------------------------------------------------------------------

#ifndef ioutilsH
#define ioutilsH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <hash_map>
//---------------------------------------------------------------------------
#define TYPE_UNKNOWN 0
#define TYPE_BOOL 1
#define TYPE_INT 2
#define TYPE_DOUBLE 3
#define TYPE_PTR 4
#define TYPE_CHAR 5
#define TYPE_STRING 6
//---------------------------------------------------------------------------
#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))
#define DIVISOR_LINE "/" \
  "/------------------------------------------------------------------------------"
#define ADD_ZERO_BASED(name, upper)        \
  enums.insert(make_pair(name, enum_descr_t("0", upper)));
//---------------------------------------------------------------------------
using std::string;
using std::vector;
using std::hash_map;
using std::make_pair;
//---------------------------------------------------------------------------
typedef struct
{
  string code;
  int i;
  union
  {
    bool no_calc;
    char call_conv;
  };
} YYSTYPE;
typedef vector<string> stringlist_t;
struct enum_descr_t
{
  string lower, upper;
  enum_descr_t(const string &l = "@unknown@", const string &u = "@unknown@") :
    lower(l), upper(u) { }
};
typedef hash_map<string, enum_descr_t> enums_t;
//---------------------------------------------------------------------------
int yyerror(char *line);
int yywarning(char *line);
int yylex(void);
const char *extract_file_name(const char *name);
void write_cpp(const char *format, ...);
void newline(void);
void open_output(bool is_cpp = true);
void initialize(void);
void cleanup(void);
//---------------------------------------------------------------------------
extern int indent, line_no;
extern string src_name, tmp_string;
extern char buf[];
//---------------------------------------------------------------------------
extern bool no_cmnts, no_tmp, use_starray, file_dsa, use_vcl, create_winmain;
extern int tab_stops;
extern string input_name, output_path, data_name;
extern char default_call;
//---------------------------------------------------------------------------
extern enums_t enums;
extern stringlist_t hpps;
//---------------------------------------------------------------------------
#endif
 