# April Syntax Cheat Sheet 
![alt text](https://github.com/PandiCornDeveloper/April-Compiler/blob/April-New-Core/image/d25.png)

### Data Types in April Programming
*    int
*    double
*    string
*    bool
*    stream

### Declarations in April Programming
Declarations use is intrinsic. The intrinsic types are

#### Local Variables
| *Explicit statement*                     | *Implied statement*           |
|------------------------------------------|-------------------------------|
| **var [name]:[type] = [Assignment];**    | **[name] := [Assignment];**   |
| var x:int = 1;                           | x:=1;                         |
| var x:double = 1.2;                      | x:=1.2;                       |
| var x:string = "Hi, April";              | x:="Hi, April";               |
| var x:bool = true;                       | x:=true;                      |
| var x:stream = open("file.april", "w");  | x:= open("file.april", "w") ; |

#### Global Variables
| *Explicit statement*                     |
|------------------------------------------|
| **global [name]:[type] = [Assignment];** |
| global x:int = 1;                        |
| global x:double = 1.2;                   |
| global x:string = "Hi, April";           |
| global x:bool = true;                    |

#### Functions
```c++
fn [name]([arguments])
{
    [statements]
    return [expression]
}
example:

fn suma(x:int, y:int)
{
    c:= x + y;
    return c;
}

```

### Operators in April Programming
All operators in C++ perform some defined function. This table shows the operator, precedence (which determines who goes first), cardinality, and associativity in the C++ program.

| Operator  | Cardinality    | Associativity |
|-----------|----------------|---------------|
| () [] {}  | unary          | left to right |
| not       | unary          | left to right |
| -- ++     | unary	         | left to right |
| * / 	    | binary	     | left to right |
| + –	    | binary	     | left to right |
| < <= > >= | binary	     | left to right |
| += -=	    | binary	     | left to right |
| *=* /=    | binary	     | left to right |
| == !=	    | binary	     | left to right |
| and	    | binary	     | left to right |
| or        | binary	     | left to right |
| =         | binary	     | left to right |
| <<        | binary	     | left to right |
| &         | binary	     | left to right |

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
for booleanExpression
{
    expressions;
}
```

### Algorithms
Examples: 

#### Hello World
```c++
fn main()
{
    println("Hi April");
} 
main();
```

#### Raíz de Newtom
```c++
fn sqr(x:int) {
    z := 1.0;
    cont := 0;

    for cont < 10 {
        z = z-(((z*z)-x)/(2*z));
        println("cont: "+str(cont));
        cont += 1;
    }
    return z;
}

fn main()
{
    sqr(5);
    j := sqr(2);
    println("result: "+str(j));
}

main();
```

#### Recursividad Simple
```c++
global array:list = [8, 6, 8, 7, 78, 60];

fn foo1() {
    x := 0;
    for i in array {
        x += 1;
    }

    return 45;
}

fn foo(a:int) {
    
    for i in range(10) {
        if i == 5 {
            result := foo1();
            return result;
        } 
    }
}

fn foo2(a:int) {

    println("noche...");
    if a >= 10 {
        return foo(a);
    }
    return foo2(a+1);
}

fn main() {
    result := foo2(0);
    println("result: "+str(result));
    println("hola");
}

main();
```

#### Números pares e impares
```c++
fn main() {
    i := 0;

    for i < (100+1) {
        if (i % 2) == 0 {
            println("i: "+str(i)+", es par");
        } 
        else {
            println("i: "+str(i)+", NO es par");
        }

        i += 1;
    }   
}

main();
```
#### Ámbitos
```c++
fn main()
{
    x := 5;

    if true
    {
        k := 1;
        println("then x: "+str(x));
        println("then k: "+str(k));
        if false 
        {
            j := 6;
            println("then then j: "+str(j));
        }
        else 
        {
            j := 9;
            println("then else j: "+str(j));

            if false 
            {
                h := 6;
                println("then else then j: "+str(j));
            }
            else 
            {
                q := 0;

                w := 0;
                for (q < 3)
                {
                    w = 0;
                    println("q -->: "+str(q));
                    for (w < 3) 
                    {
                        println("w: "+str(w));
                        w += 1;
                    }
                    // println("z: "+str(z)); variable no definida
                    q += 1;
                }
                println("q: "+str(q));
                // println("w: %d", w); variable no definida
            }
            //println("h: %d", h); error
        }
    }
    else 
    {
        j := 0;
        println("else x: "+str(x));
        println("else j: "+str(j));
    }
    // manejo de ambitos
    k := 0;
    println("k: "+str(k));
    // println("j: %d", j); error: variable no definida
}

main();
```
