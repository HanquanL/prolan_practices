class NoCopyClass1{
    private:
        NoCopyClass1(const NoCopyClass1 &);
        NoCopyClass1 &operator = (const NoCopyClass1 &);
    public:
        NoCopyClass1(){}
};

class NoCopyClass2{
    public:
        NoCopyClass2(){}
        NoCopyClass2(const NoCopyClass2 &) = delete;
        NoCopyClass2 &operator = (const NoCopyClass2 &) = delete;
};

int main(){
    NoCopyClass1 original1;
    NoCopyClass1 copy1a(original1);
    NoCopyClass1 copy1b = original1;
    
    NoCopyClass2 original2;
    NoCopyClass2 copy2a(original2); 
    NoCopyClass2 copy2b = original2; 
    return 0;
}