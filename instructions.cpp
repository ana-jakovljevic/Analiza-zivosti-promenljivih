#include "instructions.hpp"

void BasicBlock::ispisi() const{
    //cout << "BasicBlock" << _serial << endl;
    for(Instruction* v: _vec)
        v->ispisi();
}

Assignment::Assignment(string id,char op,Value* v1, Value* v2){
    _id = id;
    _op = op;
    _vec = vector<Value*>(2);
    _vec[0] = v1;
    _vec[1] = v2;
    _type = DODELA;
}
Assignment::Assignment(string id,Value* v1){
    _id = id;
    _op = ' ';
    _vec = vector<Value*>(1);
    _vec[0] = v1;
}

void Assignment::ispisi() const{
    cout << _id << " := ";
    _vec[0]->ispisi();
    if(_op != ' '){
        cout << " " <<_op << " "; 
        _vec[1]->ispisi();
    }
    cout << ";" << endl;
}


set<string> Assignment::defined_vars() const{
    return set<string>{_id};
}
set<string>  Assignment::used_vars() const{
    set<string> ret = set<string>();
    if(_vec[0]->_type == VAR)
        ret.insert(((Variable*)_vec[0])->get_id());
    if(_op!= ' '){
        if(_vec[1]->_type == VAR)
        ret.insert(((Variable*)_vec[1])->get_id());
    }
    return ret;
}


void ArrayAssignment::ispisi() const{
    cout << _id << '[';
    _pos->ispisi();
    cout << "] = ";
    _v->ispisi();
    cout << ';' << endl;
}

set<string> ArrayAssignment::defined_vars() const{
    return set<string>();
}
set<string>  ArrayAssignment::used_vars() const{
    set<string> ret = set<string>();

    ret.insert(_id);
    if(_pos->_type == VAR){
        ret.insert(((Variable*)_pos)->get_id());
    }

    if(_v->_type == VAR)
        ret.insert(((Variable*)_v)->get_id());   

    return ret;
}


void Goto::ispisi() const{
    cout << "goto " << _label << ";" << endl;
}

set<string> Goto::used_vars() const{
    return set<string>();
}
set<string> Goto::defined_vars() const{
    return set<string>();
}


void IfGoto::ispisi() const{
    cout << "if ";
    _v1->ispisi();
    cout << " " << _op << " ";
    _v2->ispisi();
    cout << " goto " << _label << ";" << endl;
}

string IfGoto::get_label() const{
    return _label;
}


set<string> IfGoto::defined_vars() const{
    return set<string>();
}
set<string> IfGoto::used_vars() const{
    set<string> ret =  set<string>();
    if(_v1->_type == VAR)
        ret.insert(((Variable*)_v1)->get_id()); 
    if(_v2->_type == VAR)
        ret.insert(((Variable*)_v2)->get_id());  

    return ret;
}


void Label::ispisi() const{
    cout << _label_id << ':' << endl;
}

set<string> Label::used_vars() const{
    return set<string>();
}
set<string> Label::defined_vars() const{
    return set<string>();
}

void Return::ispisi() const{
    cout << "return ";
    _v->ispisi();
    cout << ';' << endl;
}

set<string> Return::used_vars() const{
    set<string> ret =  set<string>();
    if(_v->_type == VAR)
        ret.insert(((Variable*)_v)->get_id()); 
    return ret;
}
set<string> Return::defined_vars() const{
    return set<string>();
}

void Constant::ispisi() const{
    cout << _v;
}

void Variable::ispisi() const{
    cout << _id;
}

string Variable::get_id() const{
    return _id;
}