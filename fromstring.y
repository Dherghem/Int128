// Блок c объявлений
%{


#include "cparser.h"


//Функция лексического анализатора
int yylex()
{
  return getChar ();
};

void yyerror ()
{
  
}

%}




// Блок определения грамматики
%%

S:
    '-' NUM { negative (); }
   |
    NUM

NUM:
       NUM V 
     |
       V

V: '0' { putNumber (0); }
V: '1' { putNumber (1); }
V: '2' { putNumber (2); }
V: '3' { putNumber (3); }
V: '4' { putNumber (4); }
V: '5' { putNumber (5); }
V: '6' { putNumber (6); }
V: '7' { putNumber (7); }
V: '8' { putNumber (8); }
V: '9' { putNumber (9); }
%%
