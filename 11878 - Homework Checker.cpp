#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    char input [100];
    int cnt = 0;

    while ( gets (input) ) {
        int a, b, c;
        char dummy [100];
        strcpy (dummy, input);
        char *pch;
        pch = strtok (input, "+-=");
        a = atoi (pch);
        pch = strtok (NULL, "+-=");
        b = atoi (pch);
        pch = strtok (NULL, "+-=");

        if ( strcmp (pch, "?") == 0 ) continue;
        c = atoi (pch);

        int correct;

        if ( strchr (dummy, '+') ) correct = a + b;
        else correct = a - b;

        if ( correct == c ) cnt++;
    }

    printf ("%d\n", cnt);

    return 0;
}
