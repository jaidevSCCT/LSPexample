/*This program will only work ar console 
 *  wprintf, fwprintf, swprintf, vwprintf, vfwprintf, vswprintf - formatted wide-character output conversion
 *  The wprintf() family of functions is the wide-character equivalent 
 *  of the printf(3) family of functions.It performs formatted output of wide characters.

 *  The wprintf() and vwprintf() functions perform wide-character output to stdout. 
 *  stdout must not be byte oriented; see fwide(3) for more information.
 */

/*The setlocale() function is used to set or query the program's current locale.

If locale is not NULL, the program's current locale is modified according to the arguments.
 The argument category determines which parts of the program's current locale should be modified.

LC_ALL
    for all of the locale. 
LC_COLLATE
    for regular expression matching (it determines the meaning of range expressions 
    and equivalence classes) and string collation. 
LC_CTYPE
    for regular expression matching, character classification, conversion, 
    case-sensitive comparison, and wide character functions. 
LC_MESSAGES
    for localizable natural-language messages. 
LC_MONETARY
    for monetary formatting. 
LC_NUMERIC
    for number formatting (such as the decimal point and the thousands separator). 
LC_TIME
    for time and date formatting.*/

#include<stdio.h>
#include<wchar.h>
#include<stdlib.h>
#include<locale.h>

int main()
{
	int ret;
	wchar_t *wideChar = L"उदाहरण";		// means "example"
	setlocale(LC_CTYPE, "");
	ret = wprintf(L"The wide string is :  %ls \n", wideChar);
	if(ret == -1 )
		perror("wprintf");
	return 0;
}

/*OUTPUT : - 
$ ./a.out 
The wide string is :  उदाहरण 
*/
