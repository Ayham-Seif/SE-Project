
#include "ast.h"

Node::Node(int line, int column)
{
	this->line = line;
	this->column = column;
	this->father = NULL;
}

ClassDef::ClassDef(Ident *n, Fields *fs, int l, int c): Node(l, c)
{
	this->name = n;
	this->fields = fs;
	
	n->father = this;
	fs->father = this;
}

Fields::Fields(int l, int c) : Node(l, c)
{
	this->fields = new vector<Field *>;
}

void
Fields::AddField(Field *f)
{
	this->fields->push_back(f);
	f->father = this;
}

Field::Field(int l, int c) : Node(l, c)
{
	
}

Variable::Variable(ExprType *et, VarDecls *vs, int l,int c) : Field(l, c)
{
	this->exprType = et;
	this->varDecls = vs;
	et->father = this;
	vs->father = this;
}

Method::Method(ExprType *et, Ident *n, Params *ps, Insts *is, int l, int c) : Field(l, c)
{
	this->exprType = et;
	this->name = n;
	this->params = ps;
	this->insts = is;
	et->father = this;
	n->father = this;
	ps->father = this;
	is->father = this;
}

Method::Method(Ident *n, Params *ps, Insts *is, int l, int c) : Field(l, c)
{
	this->exprType = NULL;
	this->name = n;
	this->params = ps;
	this->insts = is;
	n->father = this;
	ps->father = this;
	is->father = this;
}

VarDecls::VarDecls(int l, int c) : Node(l, c)
{
	this->varDecls = new vector<VarDecl *>;
}

VarDecls::VarDecls(VarDecl *vd, int l, int c) : Node(l, c)
{
	this->varDecls = new vector<VarDecl *>;
	this->AddVarDecl(vd);
}

void
VarDecls::AddVarDecl(VarDecl *vd)
{
	this->varDecls->push_back(vd);
	vd->father = this;
}

VarDecl::VarDecl(Ident *n, int l, int c) : Node(l, c)
{
	this->name = n;	
	n->father = this;
	this->expr = NULL;
}

VarDecl::VarDecl(Ident *n, Expr *e, int l, int c) : Node(l, c)
{
	this->name = n;
	this->expr = e;
	n->father = this;
	e->father = this;
}

Params::Params(int l, int c) : Node(l, c)
{
	this->params = new vector<Param *>;
}

Params::Params(Param *p, int l, int c) : Node(l, c)
{
	this->params = new vector<Param *>;
	this->AddParam(p);
}

void
Params::AddParam(Param *p)
{
	this->params->push_back(p);
	p->father = this;
}

Param::Param(ExprType *et, Ident *n, int l, int c) : Node(l, c)
{
	this->exprType = et;
	this->name = n;
	et->father = this;
	n->father = this;
}

ExprType::ExprType(int t, int l, int c) : Node(l, c)
{
	this->type = t;
}

Ident::Ident(string n, int l, int c) : Node(l, c)
{
	this->name = n;
	this->symbol = NULL;
}

//***********************************************************************
//					Expr
//***********************************************************************

Expr::Expr(int l, int c) : Node(l, c)
{

}

ExprList::ExprList(int l, int c) : Node(l, c)
{
	this->exprList = new vector<Expr *>;
}

ExprList::ExprList(Expr *e, int l, int c) : Node(l, c)
{
	this->exprList = new vector<Expr *>;
	this->AddExpr(e);
}

void
ExprList::AddExpr(Expr *e)
{
	this->exprList->push_back(e);
	e->father = this;
}


Integer::Integer(int v, int l, int c) : Expr(l, c)
{
	this->value = v;
	this->type = 1;
}

Real::Real(int v, int l, int c) : Expr(l, c)
{
	this->value = v;
	this->type = 2;
}

True::True(int l, int c) : Expr(l, c)
{
	this->type = 3;
}

False::False(int l, int c) : Expr(l, c)
{
}

Null::Null(int l, int c) : Expr(l, c)
{
	this->type = 3;
}

Paren::Paren(Expr *e, int l, int c) : Expr(l, c)
{
	this->expr = e;
	e->father = this;
}

IdentExpr::IdentExpr(Ident *id, int l, int c) : Expr(l, c)
{
	this->ident = id;
	id->father = this;
}

Assign::Assign(Ident *id, Expr *e, int l, int c) : Expr(l, c)
{
	this->ident = id;
	this->expr = e;
	id->father = this;
	e->father = this;
}

Invoke::Invoke(Ident *id, ExprList *el, int l, int c) : Expr(l, c)
{
	this->ident = id;
	this->exprList = el;
	id->father = this;
	el->father = this;
}

Not::Not(Expr *e, int l, int c) : Expr(l, c)
{
	this->expr = e;
	e->father = this;
}

Plus::Plus(Expr *e, int l, int c) : Expr(l, c)
{
	this->expr = e;
	e->father = this;
}

Minus::Minus(Expr *e, int l, int c) : Expr(l, c)
{
	this->expr = e;
	e->father = this;
}

Incr::Incr(Ident *id, bool ip, int l, int c) : Expr(l, c)
{
	this->ident = id;
	this->isPrev = ip;
	id->father = this;
}

Decr::Decr(Ident *id, bool ip, int l, int c) : Expr(l, c)
{
	this->ident = id;
	this->isPrev = ip;
	id->father = this;
}

Add::Add(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Sub::Sub(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Mult::Mult(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Div::Div(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Mod::Mod(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Smaller::Smaller(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Larger::Larger(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

SmallerEq::SmallerEq(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

LargerEq::LargerEq(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Equal::Equal(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

NotEq::NotEq(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

Or::Or(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

And::And(Expr *f, Expr *r, int l, int c) : Expr(l, c)
{
	this ->left = f;
	this->right = r;
	f->father = this;
	r->father = this;
}

//***********************************************************************
//					Instruction
//***********************************************************************

Inst::Inst(int l, int c) : Node(l, c)
{
}

Insts::Insts(int l, int c) : Node(l, c)
{
	this->insts = new vector<Inst *>;
}

Insts::Insts(Inst *i, int l, int c) : Node(l, c)
{
	this->insts = new vector<Inst *>;
	this->AddInst(i);
}

void
Insts::AddInst(Inst *i)
{
	this->insts->push_back(i);
	i->father = this;
}

ExprInst::ExprInst(Expr *e, int l, int c) : Inst(l, c)
{
	this->expr = e;
	e->father = this;
}

VarDeclsInst::VarDeclsInst(ExprType *et, VarDecls *vds, int l, int c) : Inst(l, c)
{
	this->exprType = et;
	this->vardecls = vds;
	et->father = this;
	vds->father = this;
}

If::If(Expr *e, Inst *i, int l, int c) : Inst(l, c)
{
	this->expr = e;
	this->inst = i;
	e->father = this;
	i->father = this;
}

IfElse::IfElse(Expr *e, Inst *i_if, Inst *i_else, int l, int c) : If(e, i_if, l, c)
{
	this->elseInst = i_else;
	i_else = this;
}

While::While(Expr *e, Inst *i, int l, int c) : Inst(l, c)
{
	this->expr = e;
	this->inst = i;
	e->father = this;
	i->father = this;
}

VarsDecl::VarsDecl(ExprType *et, VarDecls *vds, int l,int c) : Node(l, c)
{
	this->exprType = et;
	this->varDecls = vds;
	et->father = this;
	vds->father = this;
}

For::For(VarsDecl *vsd, Expr *e_cond, Expr *e_count, Inst *i, int l, int c) : Inst(l, c)
{
	this->varsDecl = vsd;
	this->exprCond = e_cond;
	this->exprCount = e_count;
	this->inst = i;
	vsd->father = this;
	e_cond->father = this;
	e_count->father = this;
	i->father = this;
}

Block::Block(Insts *is, int l, int c) : Inst(l, c)
{
	this->insts = is;
	is->father = this;
}

Return::Return(Expr *e, int l, int c) : Inst(l, c)
{
	this->expr = e;
	e->father = this;
}


//***********************
Error::Error(string message, int line, int column)
{
	this->message = message;
	this->line = line;
	this->column = column;
}

Errors::Errors()
{
	this->messages = new vector<Error *>;
}

void
Errors::AddError(std::string message, int line, int column)
{
	Error *error = new Error(message, line, column);
	this->messages->push_back(error);
}

void
Errors::Print()
{
	int size = this->messages->size();
	if(size == 0)
		cout << "Semntic analysis was done successfully! " << endl;
	else
	{
		cout << "There are " << size << " semantic errors: " << endl;
		for(int i = 0; i < size; i++)
		{ 
			cout << this->messages->at(i)->message << " at line: "
				<< this->messages->at(i)->line << " , column: "
				<< this->messages->at(i)->column << endl;
		}
	}
}




void
Node::accept(Visitor *v)
{
	
}

void
ClassDef::accept(Visitor *v)
{
	v->Visit(this);
}

void
Fields::accept(Visitor *v)
{
	v->Visit(this);
}

void
Field ::accept(Visitor *v)
{
	v->Visit(this);
}

void
Variable ::accept(Visitor *v)
{
	v->Visit(this);
}

void
Method::accept(Visitor *v)
{
	v->Visit(this);
}

void
VarDecls::accept(Visitor *v)
{
	v->Visit(this);
}

void
VarDecl ::accept(Visitor *v)
{
	v->Visit(this);
}

void
Params::accept(Visitor *v)
{
	v->Visit(this);
}

void
Param ::accept(Visitor *v)
{
	v->Visit(this);
}

void
ExprType::accept(Visitor *v)
{
	v->Visit(this);
}

void
Ident::accept(Visitor *v)
{
	v->Visit(this);
}

void
Expr::accept(Visitor *v)
{
	v->Visit(this);
}

void
Integer::accept(Visitor *v)
{
	v->Visit(this);
}

void
Real::accept(Visitor *v)
{
	v->Visit(this);
}

void
True::accept(Visitor *v)
{
	v->Visit(this);
}

void
False::accept(Visitor *v)
{
	v->Visit(this);
}

void
Paren ::accept(Visitor *v)
{
	v->Visit(this);
}

void
IdentExpr::accept(Visitor *v)
{
	v->Visit(this);
}

void
Assign::accept(Visitor *v)
{
	v->Visit(this);
}

void
Invoke::accept(Visitor *v)
{
	v->Visit(this);
}

void
ExprList::accept(Visitor *v)
{
	v->Visit(this);
}

void
Not::accept(Visitor *v)
{
	v->Visit(this);
}

void
Minus::accept(Visitor *v)
{
	v->Visit(this);
}

void
Incr::accept(Visitor *v)
{
	v->Visit(this);
}

void
Add::accept(Visitor *v)
{
	v->Visit(this);
}

void
Mult::accept(Visitor *v)
{
	v->Visit(this);
}

void
Larger::accept(Visitor *v)
{
	v->Visit(this);
}

void
LargerEq::accept(Visitor *v)
{
	v->Visit(this);
}

void
Inst::accept(Visitor *v)
{
	v->Visit(this);
}

void
Insts::accept(Visitor *v)
{
	v->Visit(this);
}

void
ExprInst::accept(Visitor *v)
{
	v->Visit(this);
}

void
VarDeclsInst::accept(Visitor *v)
{
	v->Visit(this);
}

void
If::accept(Visitor *v)
{
	v->Visit(this);
}

void
IfElse::accept(Visitor *v)
{
	v->Visit(this);
}

void
While::accept(Visitor *v)
{
	v->Visit(this);
}

void
VarsDecl::accept(Visitor *v)
{
	v->Visit(this);
}


void
Block::accept(Visitor *v)
{
	v->Visit(this);
}

void
Return::accept(Visitor *v)
{
	v->Visit(this);
}



void
Null::accept(Visitor *v)
{
	v->Visit(this);
}

void
Plus::accept(Visitor *v)
{
	v->Visit(this);
}

void
Decr::accept(Visitor *v)
{
	v->Visit(this);
}

void
Sub::accept(Visitor *v)
{
	v->Visit(this);
}

void
Div::accept(Visitor *v)
{
	v->Visit(this);
}

void
Mod::accept(Visitor *v)
{
	v->Visit(this);
}

void
Smaller::accept(Visitor *v)
{
	v->Visit(this);
}

void
SmallerEq::accept(Visitor *v)
{
	v->Visit(this);
}

void
Equal::accept(Visitor *v)
{
	v->Visit(this);
}

void
NotEq::accept(Visitor *v)
{
	v->Visit(this);
}

void
Or::accept(Visitor *v)
{
	v->Visit(this);
}

void
And::accept(Visitor *v)
{
	v->Visit(this);
}

void
For::accept(Visitor *v)
{
	v->Visit(this);
}
