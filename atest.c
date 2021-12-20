/*
test for argparser that parses short and long options and reads long options
from a configuration file.

Copyright 2020 Armin Diehl <ad@ardiehl.de>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Dec 20, 2021 Armin:
 initial version
*/


#include <stdio.h>
#include "argparse.h"
#include <string.h>

char * strArg;
int intArg1;
int intArg2;
int intArgC;
int intFlag;
int intValue;


int callback(argParse_handleT *a, char * arg) {
	printf("callback %d: '%c'(%d) '%s', arg: '%s'\n",a->index,(a->shortOption<32) || (a->shortOption>255) ? ' ' : a->shortOption,a->shortOption,a->longOption,arg);
	return 0;
}


AP_START(argopt)
	AP_HELP
	AP_OPT_INTVAL     ('v',"value" ,&intValue  ,"integer value")
	AP_OPT_INTVALF    ('f',"flag"  ,&intFlag   ,"flag, multiple times to increment -f- to decrement")
	AP_OPT_STRVAL     ('s',"str"   ,&strArg    ,"set string")
	AP_OPT_INTVAL     ('i', "int"  ,&intArg1   ,"set int")
	AP_OPT_INTVALFO   ('I',"int2"  ,&intArg2   , "increment or set int")
	AP_OPT_INTVAL_CB  ('c', "intc" ,&intArgC   ,"set int with callback", &callback)
AP_END;

int main(int argc, char *argv[]) {
	int rc;
	argParse_handleT *a;

	a = argParse_init(argopt, "atest.conf", "\natest is a simple test for argparse\n","\nafter parsing, the parsed args will be shown\n");
	rc = argParse (a, argc, argv, 1);
	printf("argParse returned %d\n",rc);
	if (rc >= 0) {
		printf("strArg: '%s' IntArg1: %d, intArg2: %d, intFlag: %d, intArgC: %d\n",strArg,intArg1,intArg2,intFlag,intArgC);
		if (a->optArgsCount) {
			printf("%d optional args: ", a->optArgsCount);
			for (int i=0;i<a->optArgsCount;i++) {
				printf("'%s' ",argParse_getOptArg(a,i));
			}
			printf("\n");
		}
	}

}
