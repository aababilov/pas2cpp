//---------------------------------------------------------------------------
#include "ioutils.h"

#pragma hdrstop

#include <cstdarg>

//---------------------------------------------------------------------------
#define isidchar (isdigit(c) || isalpha(c) || c == '_')
#define nextchar (c = getc(input_file))
#ifdef __WIN32__
#define PATH_DELIMITER '\\'
#else
#define PATH_DELIMITER '/'
#endif
//---------------------------------------------------------------------------
using namespace std;
namespace
{
int ret_code, err_cnt, warn_cnt;
unsigned char c;
bool curly;  
string cmnt, cmnt_line;
char *p;
FILE *input_file, *output_file;
}
//---------------------------------------------------------------------------
int indent, line_no = 1;
string src_name, tmp_string;
char buf[256];
//---------------------------------------------------------------------------
bool no_cmnts, no_tmp, use_starray, file_dsa, use_vcl, create_winmain;
int tab_stops = 2;
string input_name, output_path, data_name;
char default_call = 'n';
//---------------------------------------------------------------------------
int yyerror(char *line)
{
  fprintf(stderr, "Error(line %d): %s\n", line_no, line);
  err_cnt++;
  return 0;
}
//---------------------------------------------------------------------------
int yywarning(char *line)
{
  fprintf(stderr, "Warning(line %d): %s\n", line_no, line);
  warn_cnt++;
  return 0;
}
//---------------------------------------------------------------------------
inline void needchar(void)
{
  if (feof(input_file))
  {
    fprintf(stderr, "An unlimited source!\n");
    exit(-1);
  }
  nextchar;
  if (c == '\n')
    line_no++;
}
//---------------------------------------------------------------------------
inline void read_identifier(void)
{
  for (tmp_string.clear(); isidchar; needchar())
    tmp_string += c;
}
//---------------------------------------------------------------------------
bool extract(const char *s)
{
  static char tmp;
  if (c != s[0]) return false;
  tmp = c;
  needchar();
  if (c == s[1])
  {
    needchar();
    return true;
  }
  else
  {
    ungetc(c, input_file);
    if (c == '\n') line_no--;
    c = tmp;
		return false;
  }
}
//---------------------------------------------------------------------------
bool extract(const char ac)
{
  return ac == c ? (needchar(), true) : false;
}
//---------------------------------------------------------------------------
void read_cmnt(void)
{
	static bool nl;
	static int old_line_no;
	old_line_no = line_no;
	for (; c <= ' '; needchar());
	for (;;)
	{
		switch (c)
		{
		case '/':
			needchar();
			switch (c)
			{
			case '/':
				do needchar(); while (c != '\r');
				break;
			case '*':
				needchar();
                while (!extract("*)")) nextchar();
				break;
			default:
				return;
			}
			break;
		case '#':
			do needchar(); while (c != '\r');
		}
	}
}
//---------------------------------------------------------------------------
#define DEFINE_RESWORD(word) {#word, #word, word}
#define DECLARE_IDENTIFIER(pas_v, cpp_v) {pas_v, cpp_v, IDENTIFIER}
#include "parser.cpp.h"
const struct
{
  const char *pas_ver, *cpp_ver;
  int token;
} words[] =
{                 
	DEFINE_RESWORD(BOOL),
	DEFINE_RESWORD(CHAR),
	DEFINE_RESWORD(WCHAR_T),
	DEFINE_RESWORD(INT),
	DEFINE_RESWORD(__INT64),
	DEFINE_RESWORD(LONG),
	DEFINE_RESWORD(SHORT),
	DEFINE_RESWORD(SIGNED),
	DEFINE_RESWORD(UNSIGNED),
	DEFINE_RESWORD(FLOAT),
	DEFINE_RESWORD(DOUBLE),

	DEFINE_RESWORD(STRUCT),
	DEFINE_RESWORD(CLASS),

	DEFINE_RESWORD(STATIC),

	DEFINE_RESWORD(VOLATILE),
	DEFINE_RESWORD(CONST),

	DEFINE_RESWORD(VIRTUAL),
	DEFINE_RESWORD(ASM),
	DEFINE_RESWORD(OPERATOR),
	DEFINE_RESWORD(IF),
	DEFINE_RESWORD(ELSE),
	DEFINE_RESWORD(WHILE),
	DEFINE_RESWORD(DO),
	DEFINE_RESWORD(FOR),
	DEFINE_RESWORD(RETURN),
	DEFINE_RESWORD(GOTO),
	DEFINE_RESWORD(THROW),
	DEFINE_RESWORD(TRY),
	DEFINE_RESWORD(CATCH),
	DEFINE_RESWORD(SWITCH),
	DEFINE_RESWORD(STATIC_CAST),
	DEFINE_RESWORD(CONST_CAST),
	DEFINE_RESWORD(REINTERPRET_CAST),
	DEFINE_RESWORD(DYNAMIC_CAST),

	DEFINE_RESWORD(PRIVATE),
	DEFINE_RESWORD(PROTECTED),
	DEFINE_RESWORD(PUBLIC),
	{"__published", PUBLISHED},
	{"__property", PROPERTY},
};
};
const struct
{
	const char *pas_ver, *cpp_ver;
  int type;
} consts[] =
{
  {"True",  "true",  TYPE_BOOL},
  {"False", "false", TYPE_BOOL},
  {"Nil",   "NULL",  TYPE_PTR}
};
//---------------------------------------------------------------------------
#define PROCESSED(_kind) { ret_code = _kind; goto code_read; }
#define TRYLIST(arr) for (int i = 0; i < ARRAYSIZE(arr); i++)     \
                       if (stricmp(arr[i].pas_ver, yylval.code.c_str()) == 0)
int yylex(void)
{
  cmnt_line += cmnt;
  cmnt.clear();   
  read_cmnt();
  yylval.code.clear();
  if (feof(input_file)) PROCESSED(0);
                                     
  if (isalpha(c) || c == '_')
  {
    read_identifier();
    yylval.code = tmp_string;
		TRYLIST(words)
      {
        yylval.code = words[i].cpp_ver;
        PROCESSED(words[i].token);
      }
    TRYLIST(consts)
      {
        yylval.code = consts[i].cpp_ver;
        yylval.i = consts[i].type;
        PROCESSED(CONSTANT);
      }
    if (stricmp("asm", yylval.code.c_str()) == 0)
    {
      cmnt = "\x01\x01\x01" + cmnt;
      for(;;)
      {
        while (c <= ' ') needchar();
        while (c != '(' && c != '{' && c != '/' && c != '\n')
        {
          cmnt += c;
          needchar();
					if (stricmp(&cmnt.end()[-3], "end") == 0 && !isidchar)
          {
						p = &cmnt.end()[- 4];
						while (isdigit(*p)) p--;
            if (!(isalpha(*p) || *p == '_'))
            {
              yylval.code = cmnt.substr(3, cmnt.length() - 6);
              if (yylval.code.end()[-1] != '\01') yylval.code.end()[-1] = '\x01';
              cmnt.clear();
              PROCESSED(ASMSTMT);
            }
          }
        }
        if (c == '\n')
          cmnt += '\x01';
        else
        {
          static long stored_pos;
          stored_pos = ftell(input_file);
          read_cmnt();
          if (stored_pos != ftell(input_file))
            if (cmnt.end()[-1] <= '\n') cmnt.end()[-1] = '\x01';
            else cmnt += '\x01';
          else
          {
            cmnt += c;
            needchar();
          }
        }
      }
    }
    PROCESSED(IDENTIFIER);
  }
  if (c == '$')
  {
    yylval.code = "0x";
    for (needchar(); isxdigit(c); needchar())
      yylval.code += c;
    yylval.i = TYPE_INT;
    PROCESSED(CONSTANT);
  }
  if (isdigit(c))
  {
    tmp_string.clear();
    yylval.i = TYPE_INT;
    while (isdigit(c))
    {
      tmp_string += c;
      needchar();
      if (c == '.')
      {
        needchar();
        if (isdigit(c))
        {
          tmp_string += '.';
          yylval.i = TYPE_DOUBLE;
        }
        else
        {
          ungetc(c, input_file);
          if (c == '\n') line_no--;
          c = '.';
          break;
        }
      }
      else
        if (tolower(c) == 'e')
        {
          tmp_string += c;
          needchar();
          do
          {
            tmp_string += c;
            needchar();
          }
          while (isdigit(c));
          yylval.i = TYPE_DOUBLE;
          break;
        }
    }
    ret_code = CONSTANT;
    yylval.code = tmp_string;
    goto code_read;
  }
  if (c == '\'' || c == '#')
  {
    static char
      esc_codes[] = "\r\n\t\b\v\a\0",
      esc_symbs[] = "rntbva0";
    static int chrcode, base, n_chars;
    n_chars = 0;
    while (true)
      switch (c)
      {
        case '#':
          needchar();
          tmp_string.clear();
          base = c == '$' ? (needchar(), 16) : 10;
          while (isxdigit(c))
          {
            tmp_string += c;
            needchar();
          }
          chrcode = strtol(tmp_string.c_str(), NULL, base);
          if ((p = strchr(esc_codes, chrcode)) != '\0')
          {
            yylval.code += '\\';
            yylval.code += esc_symbs[p - esc_codes];
          }
          else
          {
            yylval.code +=  "\\x";
            yylval.code += strupr(itoa(chrcode, buf, 16));
            if (c == '\'') yylval.code += "\"\"";
          }
          n_chars++;
          break;
        case '\'':
          for (needchar(); ; needchar(), n_chars++)
            switch (c)
            {
              case '\'':
                needchar();
                if (c == '\'') yylval.code += "\\\'";
                else goto ap_read;
                break;
              case '\"':
                yylval.code += "\\\"";
                break;
              case '\\':
                yylval.code += "\\\\";
                break;
              default:
                yylval.code += c;
            }
          ap_read:
          break;
        default:
          if (n_chars == 1)
          {
            yylval.code = "\'" + yylval.code + "\'";
            yylval.i = TYPE_CHAR;
          }
          else
          {
            yylval.code = "\"" + yylval.code + "\"";
            yylval.i = TYPE_STRING;
          }
          PROCESSED(CONSTANT);
      }
  }
  yylval.code = c;
  needchar();
  switch (yylval.code[0])
  {
    case ':':
      if (extract('=')) yylval.code = '=';;
      break;
    case '(':
      if (extract('.')) yylval.code = '[';
      break;
    case '.':
      if (extract('.')) PROCESSED(TWOFULLSTOP);
      if (extract(')')) PROCESSED(']');
      break;
    case '>':
      if (extract('=')) yylval.code = ">=";
      PROCESSED(COMPARE);
    case '<':
      if (extract('=')) yylval.code = "<=";
      else if (extract('>')) yylval.code = "!=";
      PROCESSED(COMPARE);
    case '=':
      PROCESSED(EQ);
  }
  ret_code = yylval.code[0];

  code_read:
  return ret_code;
}
//---------------------------------------------------------------------------
const char *extract_file_name(const char *name)
{
  const char *tmp;
  for (tmp = name + strlen(name) - 1; tmp >= name; tmp--)
    if (*tmp == PATH_DELIMITER) break;
  return tmp + 1;
}
//---------------------------------------------------------------------------
void write_cpp(const char *format, ...)
{
  va_list list;
  va_start(list, format);
  vfprintf(output_file, format, list);
  va_end(list);
}
//---------------------------------------------------------------------------
void newline(void)
{
  write_cpp("%s", cmnt_line.begin());
  if (cmnt_line.empty() || cmnt_line.end()[-1] != '\n') write_cpp("\n");
  cmnt_line.clear();
  for (int i = indent * tab_stops; i >= 1; i--)
    write_cpp(" ");
}
//---------------------------------------------------------------------------
void open_output(bool is_cpp)
{
  if (output_file) fclose(output_file);
  tmp_string = output_path + src_name + (is_cpp ? ".cpp" : ".h");
	output_file = fopen(tmp_string.c_str(), "w+");
  if (!output_file)
  {
    fprintf(stderr, "Cannot create file \"%s\"", tmp_string.begin());
    exit(-1);
  }
}
//---------------------------------------------------------------------------
void normalize(string &s)
{
  if (*s.begin() == '\"')
    s.erase(0, 1);
  if (!s.empty() && s.end()[-1] == '\"')
    s.resize(input_name.length() - 1);
}
//---------------------------------------------------------------------------
void initialize(void)
{
  normalize(input_name);
  normalize(output_path);

  if (!output_path.empty())
    if (output_path.end()[-1] != PATH_DELIMITER)
      output_path += PATH_DELIMITER;
  if (file_dsa)
  {
    tmp_string = output_path + "dstarray.h";
		output_file = fopen(tmp_string.c_str(), "w+");
    if (!output_file)
      fprintf(stderr, "Cannot create file \"%s\"", tmp_string.begin());
    else
    {
      fprintf(output_file,
        DIVISOR_LINE "\n"
        "#ifndef DSTARRAY_H\n"
        "#define DSTARRAY_H\n"
        DIVISOR_LINE "\n"
        "template <size_t lower, size_t upper, class T>\n"
        "class StaticArray\n"
        "{\n"
        "private:\n"
        "  typedef StaticArray<lower, upper, T> _Self;\n"
        "  T data[upper - lower + 1];\n"
        "public:\n"
        "  StaticArray(void) {}\n"
        "  StaticArray(const _Self &a)\n"
        "  {\n"
        "    memcpy(data, a.data, sizeof data);\n"
        "  }\n"
        "  T &operator [](size_t i)\n"
        "  {\n"
        "    return data[i - lower];\n"
        "  }\n"
        "  _Self &operator =(_Self &a)\n"
        "  {\n"
        "    memcpy(data, a.data, sizeof data);\n"
        "    return *this;\n"
        "  }\n"
        "  operator T*(void)\n"
        "  {\n"
        "    return data;\n"
        "  }\n"
        "};\n"
        DIVISOR_LINE "\n"
        "#endif");
      fclose(output_file);
      output_file = NULL;
    }
  }

  if (input_name.empty())
    exit(0);

  if (!data_name.empty())
  {
		input_file = fopen(data_name.c_str(), "r");
    if (input_file)
    {
      while (!feof(input_file))
      {
#define READ_AND_CHECK if (!fgets(buf, sizeof buf, input_file)) goto data_read; \
  ret_code = strlen(buf) - 1; if (buf[ret_code] == '\n') buf[ret_code] = '\0'
        READ_AND_CHECK;
        if (buf[0] == '[') c = buf[1];
        else
          if (c == 't' || c == 'T')
          {
            tmp_string = strupr(buf);
            READ_AND_CHECK;
            ADD_ZERO_BASED(tmp_string, buf);
          }
          else
            hpps.push_back(buf);
      }
      data_read:
      fclose(input_file);
      input_file = NULL;
    }
  }
  const char *exts[] = {"", ".pas", ".dpr", ".dpk"};
  for (int i = 0; i < ARRAYSIZE(exts) && input_file == NULL; i++)
  {
    tmp_string = string(input_name) + exts[i];
		input_file = fopen(tmp_string.c_str(), "r");
  }
  if (input_file == NULL)
  {
    fprintf(stderr, "Cannot open file \"%s\"\n", input_name.begin());
    exit(-1);
  }
	printf("Translating file \"%s\"...\n", tmp_string.begin());
	needchar();

	src_name = extract_file_name(tmp_string.c_str());
  if (src_name.length() > 4 && src_name.end()[-4] == '.')
    src_name.resize(src_name.length() - 4);

	string::iterator p;
	p = src_name.begin();
	if (!(isalpha(*p) || *p == '_'))
		*p = '_';
	for (; p != src_name.end(); p++)
    if (!(isalpha(*p) || isdigit(*p) || *p == '_'))
      *p = '_';
}
//---------------------------------------------------------------------------
void cleanup(void)
{
  fprintf(stderr, "Errors - %d, warnings: %d\n",
    err_cnt, warn_cnt);

  if (!cmnt.empty())
    write_cpp("\n%s", cmnt.begin());
  if (!feof(input_file) && !no_cmnts)
  {
    write_cpp("\n//");
    while (c <= ' ')
    {
      nextchar;
      if (feof(input_file))
        goto ready;
    }
    do
    {
      fputc(c, output_file);
      if (c == '\n') write_cpp("//");
      nextchar;
    }
    while (!feof(input_file));
  }
  ready:
  fclose(input_file);
  fclose(output_file);
}
//---------------------------------------------------------------------------
