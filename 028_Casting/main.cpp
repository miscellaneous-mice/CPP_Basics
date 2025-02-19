#include <typeinfo>
#include <map>
#include <memory>

#include "custom_types.h"

template<typename T>
void castStatic(void* entity){
    static_cast<T*>(entity)->info();
}

template<typename T>
void castDynamic(Base* entity){
    dynamic_cast<T*>(entity)->info();
}

template<typename T>
void castVoidDynamic(void* entity){
    dynamic_cast<T*>(static_cast<Base*>(entity))->info();
}

template<typename T>
void castStaticSharedPtr(std::shared_ptr<void> entity){
    std::static_pointer_cast<T>(entity)->info();
}

template<typename T>
void castDynamicSharedPtr(std::shared_ptr<Base> entity){
    std::dynamic_pointer_cast<T>(entity)->info();
}

template<typename T>
void castVoidDynamicSharedPtr(std::shared_ptr<void> entity){
    std::dynamic_pointer_cast<T>(std::static_pointer_cast<Base>(entity))->info();
}


int main(){
    {
        A* a = new A();
        B* b = new B();
        Base* base = new Base();

        std::cout<<"*****Static casting*****"<<std::endl;
        castStatic<A>(a);
        castStatic<B>(b);
        castStatic<Base>(base);

        delete a;
        delete b;
        delete base;
    }

    {
        Base* a = new A();
        Base* b = new B();
        Base* base = new Base();

        std::cout<<"*****Dynamic casting*****"<<std::endl;
        castDynamic<A>(a);
        castDynamic<B>(b);
        castDynamic<Base>(base);

        std::cout<<"*****Dynamic void casting*****"<<std::endl;
        castVoidDynamic<A>(a);
        castVoidDynamic<B>(b);
        castVoidDynamic<Base>(base);

        delete a;
        delete b;
        delete base;
    }

    {
        std::shared_ptr<A> a = std::make_unique<A>();
        std::shared_ptr<B> b = std::make_unique<B>();
        std::shared_ptr<Base> base = std::make_unique<Base>();

        std::cout<<"*****Smart pointer static casting*****"<<std::endl;
        castStaticSharedPtr<A>(std::move(a));
        castStaticSharedPtr<B>(std::move(b));
        castStaticSharedPtr<Base>(std::move(base));
    }

    {
        std::shared_ptr<Base> a = std::make_unique<A>();
        std::shared_ptr<Base> b = std::make_unique<B>();
        std::shared_ptr<Base> base = std::make_unique<Base>();

        std::cout<<"*****Smart pointer Dynamic casting*****"<<std::endl;
        castDynamicSharedPtr<A>(a);
        castDynamicSharedPtr<B>(b);
        castDynamicSharedPtr<Base>(base);


        std::cout<<"*****Smart void pointer Dynamic casting*****"<<std::endl;
        castVoidDynamicSharedPtr<A>(a);
        castVoidDynamicSharedPtr<B>(b);
        castVoidDynamicSharedPtr<Base>(base);
    }
    return 0;
}