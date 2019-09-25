#include "analyse.hpp"

bool flag = true;
int brojac = 0;

void analyze_livness(){
    int num_of_blocks = basic_blocks.size();
    for(BasicBlock* bb:basic_blocks)   
        in_map[bb] = set<string>();
    
    while(flag){
        flag = false;
        for(int i=num_of_blocks-1;i>=0;i--){
            set_out(basic_blocks[i]);
            set_in(basic_blocks[i]);
        }
    }
   
    if(return_value != " ")
        out_map[basic_blocks.back()] = set<string>{return_value};      
}

void set_out(BasicBlock *bb){
    vector<int> followers = bb->_follow;
    set<string> out = set<string>();

    for(int f: followers){
        BasicBlock* bf = basic_blocks[f-1]; 
        set<string> in_bf = in_map[bf];
        for(string el: in_bf)
            out.insert(el);
    }
    
   // if(out_map[bb] != out){
    //    flag = true;
    //}
    out_map[bb] = out;
}

void set_in(BasicBlock *bb){
    set<string> in = out_map[bb]; 
    int num_of_instr = bb->_vec.size();
    for(int br=num_of_instr-1; br>=0; br--){
        Instruction* i = bb->_vec[br]; 
        set<string> used = i->used_vars();
        set<string> defined = i->defined_vars();

        for(string el: defined)
            in.erase(el);
        for(string el: used)
            in.insert(el);
    }

    if(in_map[bb] != in){
        flag = true;
    }
    in_map[bb] = in;
}


/* Pokusala sam sa referencama da resim problem, kako bi kad se promeni 
vrednost promenljive u mapi, ona se menjala i na mestima gde meni treba. Ali mi nije islo najbolje.
Problem: Kada naidjem na ifGoto instrukciju, i kada se pomocu nje skace na labelu
koja se definise negde kasnije u kodu, ja nemam informaciju kom bloku ta labela pripada */
void azuriraj(){
    for(BasicBlock* bb:basic_blocks){
        vector<int> foll = bb->_follow;
        for(unsigned i=0;i<foll.size();i++){
            int f = foll[i];
            if(f == 0){
                for(Instruction* instr : bb->_vec){
                    if(instr->_type == IF)
                        bb->_follow[i] =  labels_map[((IfGoto*)instr)->get_label()]; 
                }
            }
        }
    }
}

