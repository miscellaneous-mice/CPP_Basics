#include <string>
#include <iostream>

struct Val{
    int a;
    int b;
};

class Sample : public Val{
    std::string messages;
public:
    static const std::string get_str(Sample& s, const std::string& message);
    void get_all_messages();
    static void* cls_method_1(Sample* s, int x, int y);
    static void* cls_method_2(Sample* s, int x, int y);
    static void Print_Vals(Sample& s);
};

const std::string Sample::get_str(Sample& s, const std::string& message){
    s.messages += message;
    return message;
}

void Sample::get_all_messages(){
    std::cout<<messages<<std::endl;
}

void* Sample::cls_method_1(Sample* s, int x, int y){
    s->a = x;
    s->b = y;
    return s;
}

void* Sample::cls_method_2(Sample* s, int x, int y){
    s->a = x;
    s->b = y;
    return s;
}

void Sample::Print_Vals(Sample& s){
    std::cout<<"First val : "<<s.a<<", Second Val : "<<s.b<<std::endl;
}


int main() {
    Sample* s = new Sample();
    std::cout<<s->get_str(*s, "Hello")<<std::endl;
    std::cout<<s->get_str(*s, "Sam")<<std::endl;
    s->get_all_messages();
    Sample* s1 = (Sample*)s->cls_method_1(s, 4, 5);
    Sample* s2 = (Sample*)s->cls_method_2(s, 2, 3);
    s1->Print_Vals(*s1);
    s2->Print_Vals(*s2);
    delete s;
    // delete s1;
    // delete s2;
    return 0;
}