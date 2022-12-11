#include <stdio.h>

typedef struct pref_token_kit pref_token_kit;

struct pref_token_kit
{
    char  token[256][512];
    short length[256];
    short count;
};

void parse( pref_token_kit *out, char* text )
{
    out->count = 0;
    // *** //
    char f = 0, s = 0, c = 0;
    // *** //
    for ( short i = 0; i < 10; i++ )
        out->length[i] = 0;
    // *** //
    for ( short i = 0; i < 1000; i++ )
    {
        switch( text[i] )
        {
            case ' ':  case '\t':
                if ( s == 0 )
                {
                    if ( f == 0 && out->length[out->count] > 0 )
                    {
                        f = 1;
                        out->token[out->count][out->length[out->count]] = (char) 0;
                        out->count++;
                    }
                }
                else
                {
                    f = 0;
                    out->token[out->count][out->length[out->count]] = text[i];
                    out->length[out->count]++;
                }
                break;
            case '\"': case '\'':
                if ( s == 0 )
                {
                    if ( out->length[out->count] > 0 )
                        out->count++;
                    // *** //
                    c = text[i];
                    s = 1;
                    f = 0;
                    out->token[out->count][out->length[out->count]] = text[i];
                    out->length[out->count]++;
                }
                else if ( s == 1 )
                {
                    if ( c == text[i] )
                    {
                        c = 0;
                        s = 0;
                        f = 0;
                        out->token[out->count][out->length[out->count]] = text[i];
                        out->length[out->count]++;
                    }
                    else
                    {
                        f = 0;
                        out->token[out->count][out->length[out->count]] = text[i];
                        out->length[out->count]++;
                    }
                }
                break;
            case '(': case ')': case '{': case '}': case '?': case '+': 
            case '#': case '=': case '<': case '>': case ';': case ':': case '-': 
            case '*': case '/': case '\\': case '$': case '&': case '!': case '|':
                if ( s == 0 )
                {
                    if ( out->length[out->count] > 0 )
                    {
                        out->token[out->count][out->length[out->count]] = (char) 0;
                        out->count++;
                    }
                    // *** //
                    out->token[out->count][out->length[out->count]] = text[i];
                    out->length[out->count]++;
                    out->token[out->count][out->length[out->count]] = (char) 0;
                    out->count++;
                }
                else
                {
                    f = 0;
                    out->token[out->count][out->length[out->count]] = text[i];
                    out->length[out->count]++;
                }
                // *** //
                break;
            case '\n': case '\r': case 0:
                out->token[out->count][out->length[out->count]] = (char) 0;
                out->count++;
                return;
            default:
                f = 0;
                out->token[out->count][out->length[out->count]] = text[i];
                out->length[out->count]++;
        }
    }
}

void print( pref_token_kit *out )
{
    for ( short a = 0; a < out->count; a++ )
    {
        printf( "[%i] -> %s \n", a+1, &out->token[a] );
    }
}

int main()
{
    pref_token_kit kit;
 
    parse( &kit, "Dim T As String = 'Hallo Welt'; X As Single = 2,58; Y As Single = 0,5" );
    
    print( &kit );

    return 0;
}
