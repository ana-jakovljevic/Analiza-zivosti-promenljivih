#ifndef __INSTRUCTIONS_HPP__
#define __INSTRUCTIONS_HPP__ 

#include <vector>
#include <set>
#include <string>
#include <iostream>
using namespace std;

typedef enum{
    DODELA,
    IF,
    GOTO,
    LABELA,
    RETURN 
} InstructionType;

class Instruction{
public:
    virtual ~Instruction(){

    }
    virtual void ispisi() const = 0;
    virtual set<string> used_vars() const = 0;
    virtual set<string> defined_vars() const = 0;
    InstructionType _type;
};


class BasicBlock{
public:
    BasicBlock(vector<Instruction*> vec, vector<int> follow, int serial)
    : _vec(vec), _follow(follow), _serial(serial)
    {}
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
    vector<Instruction*> _vec;
    vector<int> _follow;
    int _serial;
};

typedef enum {
    VAR,
    CONST
} ValueType;

class Value{
public:
    virtual ~Value(){

    }
    virtual void ispisi() const = 0;
    ValueType _type;
};

class Assignment: public Instruction{
public:
    Assignment(string id,char op,Value* v1, Value* v2);
    Assignment(string id,Value* v1);
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
private:
    string _id;
    char _op;
    vector<Value*> _vec;
};

class ArrayAssignment:public Instruction {
public:
    ArrayAssignment(string id, Value* pos,Value* v)
    :_id(id),_pos(pos), _v(v)
    { _type = DODELA; }
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;        
private:
    string _id;
    Value* _pos;
    Value* _v;
};

class Goto: public Instruction{
public:
    Goto(string label)
    : _label(label)
    { _type = GOTO; }
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
private:
    string _label;
};

class IfGoto: public Instruction {
public:
    IfGoto(Value* v1, string op, Value* v2, string label)
    : _v1(v1), _op(op), _v2(v2), _label(label)
    { _type = IF; }
    void ispisi() const;
    string get_label() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
private:
    Value* _v1;
    string _op;
    Value* _v2;
    string _label;
};


class Label: public Instruction{
public:
    Label(string label_id)
    :_label_id(label_id)
    { _type = LABELA; }
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
private:
    string _label_id;
};


class Return: public Instruction{
public:
    Return(Value* v)
    :_v(v)
    { _type = RETURN; }
    void ispisi() const;
    set<string> used_vars() const;
    set<string> defined_vars() const;
private:
    Value* _v; 
};

class Constant: public Value{
public:
    Constant(float v)
    :_v(v)
    { _type = CONST; }
    void ispisi() const;
private:
    float _v;
};

class Variable: public Value{
public:
    Variable(string id)
    : _id(id)
    { _type = VAR; }
    void ispisi() const;
    string get_id() const;
private:
    string _id;
};



#endif 