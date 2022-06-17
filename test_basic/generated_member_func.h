#ifndef GENERATED_MEMBER_FUNC_H_
#define GENERATED_MEMBER_FUNC_H_

#include <type_traits>
#include <iostream>
#include <typeinfo>

template<class T>
void reportType() {
    std::cout << "begin report --------------------------------------------" << typeid(T).name() << std::endl;
    if (std::is_default_constructible_v<T>) {
        std::cout << "Default constructible." << std::endl;
    } 
    else {
        std::cout << "Not default constructible!" << std::endl;
    }

    if (std::is_destructible_v<T>) {
        std::cout << "Destructible." << std::endl;
    }
    else {
        std::cout << "Not destructible!" << std::endl;
    }

    if (std::is_copy_constructible_v<T>) {
        std::cout << "Copy constructible." << std::endl;
    }
    else {
        std::cout << "Not copy constructible!" << std::endl;
    }

    if (std::is_copy_assignable_v<T>) {
        std::cout << "Copy assignable." << std::endl;
    }
    else {
        std::cout << "Not copy assignable!" << std::endl;
    }

    if (std::is_move_constructible_v<T>) {
        std::cout << "Move constructible." << std::endl;
    }
    else {
        std::cout << "Not move constructible!" << std::endl;
    }

    if (std::is_move_assignable_v<T>) {
        std::cout << "Move assignable." << std::endl;
    }
    else {
        std::cout << "Not move assignable!" << std::endl;
    }

    std::cout << "end report." << std::endl;
}

class EmptyClass {

};

struct EmptyStruct {

};

class ClassWithDefinedContructor {
public:
    ClassWithDefinedContructor(int a) {}
};

class ClassWithDeletedMoveContructor {
public:
    ClassWithDeletedMoveContructor(ClassWithDeletedMoveContructor&&) = delete;
};

class ClassHasMemberClassWithDeletedMoveContructor {
private:
    ClassWithDeletedMoveContructor c;
};

class ClassWithDefinedMoveContructor {
public:
    ClassWithDefinedMoveContructor(ClassWithDefinedMoveContructor&&) {}
};

class ClassWithDefinedCopyContructor {
public:
    ClassWithDefinedCopyContructor(const ClassWithDefinedCopyContructor&) {}
};

class ClassWithDeletedMoveAssignment {
public:
    ClassWithDeletedMoveAssignment& operator=(ClassWithDeletedMoveAssignment&&) = delete;
};

class ClassWithDeletedCopyContructor {
public:
    ClassWithDeletedCopyContructor(const ClassWithDeletedCopyContructor&) = delete;
};

class ClassWithDeletedCopyAssignment {
public:
    ClassWithDeletedCopyAssignment& operator=(const ClassWithDeletedCopyAssignment&) = delete;
};

class ClassWithDeletedContructor {
public:
    ClassWithDeletedContructor() = delete;
};

class ClassWithDeletedDestructor {
public:
    ~ClassWithDeletedDestructor() = delete;
};

class ClassWithDefinedDestructor {
public:
    ~ClassWithDefinedDestructor() {}
};

class ClassWithDefinedCopyAssignment {
public:
    ClassWithDefinedCopyAssignment& operator=(const ClassWithDefinedCopyAssignment&) {return *this;}
};

class ClassWithDefinedMoveAssignment {
public:
    ClassWithDefinedMoveAssignment& operator=(ClassWithDefinedMoveAssignment&&) {return *this;}
};


void test_generated_member_func() {
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << std::endl;
    reportType<EmptyClass>();
    reportType<EmptyStruct>();
    reportType<ClassWithDefinedContructor>();
    reportType<ClassWithDeletedMoveContructor>();
    reportType<ClassHasMemberClassWithDeletedMoveContructor>();
    reportType<ClassWithDefinedMoveContructor>();

    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << std::endl;
    reportType<ClassWithDeletedMoveContructor>();
    reportType<ClassWithDeletedMoveAssignment>();
    reportType<ClassWithDeletedCopyContructor>();
    reportType<ClassWithDeletedCopyAssignment>();
    reportType<ClassWithDeletedContructor>();
    reportType<ClassWithDeletedDestructor>();

    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << std::endl;
    reportType<ClassWithDefinedContructor>();
    reportType<ClassWithDefinedCopyContructor>();
    reportType<ClassWithDefinedMoveContructor>();
    reportType<ClassWithDefinedCopyAssignment>();
    reportType<ClassWithDefinedMoveAssignment>();
    reportType<ClassWithDefinedDestructor>();
}

#endif
