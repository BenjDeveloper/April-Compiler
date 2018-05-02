# April Syntax Cheat Sheet 
![alt text](https://github.com/PandiCornDeveloper/April-Compiler/blob/April-Windows-Pandicorn/d25.png)

### Data Types
*    int
*    double
*    string
*    bool

### Declarations
Declarations use is intrinsic. The intrinsic types are


| *Explicit statement*                  | *Implied statement*         |
|---------------------------------------|-----------------------------|
| **var [name]:[type] = [Assignment];** | **[name] := [Assignment];** |
| var x:int = 1;                        | x:=1;                       |
| var x:double = 1.2;                   | x:=1.2;                     |
| var x:string = "Hi, April";           | x:="Hi, April";             |
| var x:bool = true;                    | x:=true;                    |



### Operators in April Programming
All operators in C++ perform some defined function. This table shows the operator, precedence (which determines who goes first), cardinality, and associativity in the C++ program.

| Operator | Cardinality | Associativity |
|----------|-------------|---------------|
| () [] {} | unary       | left to right |
| not      | unary       | left to right |
| -- ++    | unary	     | left to right |
| * / 	   | binary	     | left to right |
| + –	   | binary	     | left to right |
| < <= > >=| binary	     | left to right |
| == !=	   | binary	     | left to right |
| and	   | binary	     | left to right |
| or       | binary	     | left to right |
| not      | binary	     | left to right |


| ?:       | ternary	 | right to left |


"global"            { return TOKEN(TGLOBAL); }
"var"               { return TOKEN(TVAR); }
"fn"                { return TOKEN(TFN); }

"return"            { return TOKEN(TRETURN); }

"!="				{ return TOKEN(TCOMNE); }
"=="				{ return TOKEN(TCOMEQ); }
"<="				{ return TOKEN(TCOMLE); }
">="				{ return TOKEN(TCOMGE); }
"<"					{ return TOKEN(TCOMLT); }
">"					{ return TOKEN(TCOMGT); }
"<<"				{ return TOKEN(TLTL); }
":="                { return TOKEN(TCOEQU); }
"+="                { return TOKEN(TASIGPLUS); }
"-="                { return TOKEN(TASIGMINUS); }
"*="                { return TOKEN(TASIGMULT); }
"/="                { return TOKEN(TASIGDIV); }
":"                 { return TOKEN(TCOLON); }
"="                 { return TOKEN(TEQUAL); }
","                 { return TOKEN(TCOMMA); }
"&"					{ return TOKEN(TAMPER); }



### Flow Control in April Programming
The following April structures direct the flow of control through the program. If you’re an experienced programmer, the function of these structures will be familiar from other languages.

#### IF
The following command evaluates booleanExpression. If it evaluates to true, then control passes to expressions1. If not, then control passes to the optional expressions2.

```c++

if (booleanExpression)
{
    expressions1;
}
else
{
    expressions2;
}
```

#### FOR
The following command evaluates booleanExpression. If this evaluates to true, then control passes to expressions. At the end of the block, control passes back to booleanExpression and repeats the process.

```c++
for (booleanExpression)
{
    expressions;
}
```

