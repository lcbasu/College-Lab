%{

	#include "y.tab.h"

%}

digit		[0-9]
small		[a-z]
capital		[A-Z]
name		[A-Z][a-z]+

fullName	{name}" "{name}
fullAddrs1	{digit}{2}"-"{digit}{2}"-"{digit}{2}" "{name}" "{name}
fullAddrs2	{name}" "{capital}{2}"{digit}{2}"-", PIN-"{digit}{6}

%%

fullName	{	return FN;	}
fullAddrs1	{	return FA1;	}
fullAddrs2	{	return FA2;	}

%%

int yywrap(void)
{
	return 1;
}
