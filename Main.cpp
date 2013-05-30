//---------------------------------------------------------------------------
#include "ioutils.h"

#pragma hdrstop     

//---------------------------------------------------------------------------

//#undef FROMBCB
#ifdef FROMBCB
YYSTYPE yylval;
#endif

void translate(void);

const char help_text[] =
  "usage: %s [options ...] filename\n"
  "\t-h, -? or no arguments     Help\n"
  "\t-s                         Create file \"dstarray.h\"\n"
  "\t-a                         Don\'t use StaticArray\n"
  "\t-i                         Ignore comments in source\n"
  "\t-c                         No temporary variables in for cycles\n"
  "\t-w                         Use WinMain instead of main\n"  
  "\t-txxx or -t xxx            Set tab stops\n"
  "\t-pxxx                      Set default calling convention:\n"
  "\t  -pm                        __msfastcall\n"
  "\t  -pc or -p-                 __cdecl\n"
  "\t  -p                         __pascal\n"
  "\t  -pr                        __fastcall\n"
  "\t  -ps                        __stdcall\n"
  "\t  -pf                        __safecall\n"
  "\t-o path or -opath          Specify output path\n"
  "\t-d filename or -dfilename  Specify data file\n";

void print_help(void)
{
  printf(help_text, extract_file_name(__argv[0]));
  exit(0);
}

#pragma argsused
int main(int argc, char* argv[])
{
  if (argc == 1)
    print_help();
  for (int i = 1; i < argc; i++)
    if (argv[i][0] == '-' || argv[i][0] == '/' || argv[i][0] == '\\')
      switch (argv[i][1])
      {
        case 'h':
        case '?':
          print_help();
          break;
        case 's':
          file_dsa = true;
          break;
        case 'i':
          no_cmnts = true;
          break;
        case 'a':
          use_starray = false;
          break;
        case 'c':
          no_tmp = true;
          break;
        case 'v':
          use_vcl = true;
          break;
        case 'w':
          create_winmain = true;
          break;
        case 't':
          if (argv[i][2]) tab_stops = atoi(argv[i] + 2);
          else if (++i < argc) tab_stops = atoi(argv[++i]);
          break;
        case 'p':
          default_call = argv[i][2];
          break;
        case 'o':
          if (argv[i][2]) output_path = argv[i] + 2;
          else if (++i < argc) output_path = argv[i];
          break;
        case 'd':
          if (argv[i][2]) data_name = argv[i] + 2;
          else if (++i < argc) data_name = argv[i];
          break;
      }
    else input_name = argv[i];

  initialize();
#ifdef FROMBCB
  freopen("unit1.h", "w+", stdout);
  while (yylex()) { fprintf(stdout, "%s", yylval.code.begin()); }
#else
  translate();
#endif

  cleanup();
  return 0;
}
//---------------------------------------------------------------------------





