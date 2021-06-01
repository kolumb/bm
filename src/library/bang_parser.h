#ifndef BANG_PARSER_H_
#define BANG_PARSER_H_

#include "./arena.h"
#include "./bang_lexer.h"

typedef struct Bang_Funcall_Arg Bang_Funcall_Arg;
typedef struct Bang_Funcall Bang_Funcall;
typedef union Bang_Expr_As Bang_Expr_As;
typedef struct Bang_Expr Bang_Expr;
typedef struct Bang_Funcall_Arg Bang_Funcall_Arg;
typedef struct Bang_Stmt Bang_Stmt;
typedef struct Bang_If Bang_If;
typedef union Bang_Stmt_As Bang_Stmt_As;
typedef struct Bang_Block Bang_Block;
typedef struct Bang_Proc_Def Bang_Proc_Def;
typedef struct Bang_Var_Def Bang_Var_Def;
typedef union Bang_Top_As Bang_Top_As;
typedef struct Bang_Top Bang_Top;
typedef struct Bang_Module Bang_Module;
typedef struct Bang_Var_Assign Bang_Var_Assign;

struct Bang_Funcall {
    Bang_Loc loc;
    String_View name;
    Bang_Funcall_Arg *args;
};

union Bang_Expr_As {
    String_View lit_str;
    Bang_Funcall funcall;
    bool boolean;
};

typedef enum {
    BANG_EXPR_KIND_LIT_STR,
    BANG_EXPR_KIND_LIT_BOOL,
    BANG_EXPR_KIND_FUNCALL,
} Bang_Expr_Kind;

struct Bang_Expr {
    Bang_Expr_Kind kind;
    Bang_Expr_As as;
};

struct Bang_Funcall_Arg {
    Bang_Expr value;
    Bang_Funcall_Arg *next;
};

typedef enum {
    BANG_STMT_KIND_EXPR,
    BANG_STMT_KIND_IF,
    BANG_STMT_KIND_VAR_ASSIGN,
} Bang_Stmt_Kind;

struct Bang_If {
    Bang_Loc loc;
    Bang_Expr condition;
    Bang_Block *then;
    Bang_Block *elze;
};

struct Bang_Var_Assign {
    String_View name;
    Bang_Expr value;
};

union Bang_Stmt_As {
    Bang_Expr expr;
    Bang_If eef;
    Bang_Var_Assign var_assign;
};

struct Bang_Stmt {
    Bang_Stmt_Kind kind;
    Bang_Stmt_As as;
};

struct Bang_Block {
    Bang_Stmt stmt;
    Bang_Block *next;
};

struct Bang_Proc_Def {
    String_View name;
    Bang_Block *body;
};

typedef enum {
    BANG_TYPE_I64
} Bang_Type;

struct Bang_Var_Def {
    Bang_Loc loc;
    String_View name;
    Bang_Type type;
};

typedef enum {
    BANG_TOP_KIND_PROC = 0,
    BANG_TOP_KIND_VAR,
    COUNT_BANG_TOP_KINDS,
} Bang_Top_Kind;

union Bang_Top_As {
    Bang_Var_Def var;
    Bang_Proc_Def proc;
};

struct Bang_Top {
    Bang_Top_Kind kind;
    Bang_Top_As as;
    Bang_Top *next;
};

struct Bang_Module {
    Bang_Top *tops_begin;
    Bang_Top *tops_end;
};

void bang_module_push_top(Bang_Module *module, Bang_Top *top);

String_View parse_bang_lit_str(Arena *arena, Bang_Lexer *lexer);
Bang_Funcall_Arg *parse_bang_funcall_args(Arena *arena, Bang_Lexer *lexer);
Bang_Funcall parse_bang_funcall(Arena *arena, Bang_Lexer *lexer);
Bang_Expr parse_bang_expr(Arena *arena, Bang_Lexer *lexer);
Bang_Block *parse_curly_bang_block(Arena *arena, Bang_Lexer *lexer);
Bang_If parse_bang_if(Arena *arena, Bang_Lexer *lexer);
Bang_Stmt parse_bang_stmt(Arena *arena, Bang_Lexer *lexer);
Bang_Proc_Def parse_bang_proc_def(Arena *arena, Bang_Lexer *lexer);
Bang_Type parse_bang_type(Bang_Lexer *lexer);
Bang_Top parse_bang_top(Arena *arena, Bang_Lexer *lexer);
Bang_Var_Def parse_bang_var_def(Bang_Lexer *lexer);
Bang_Module parse_bang_module(Arena *arena, Bang_Lexer *lexer);
Bang_Var_Assign parse_bang_var_assign(Arena *arena, Bang_Lexer *lexer);

#endif // BANG_PARSER_H_
