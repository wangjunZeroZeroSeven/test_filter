#ifndef DELETE_H_
#define DELETE_H_

bool isLucky(int a) {
    return true;
}

// bool isLucky(bool a) = delete;
// bool isLucky(char a) = delete;
// bool isLucky(double a) = delete;

void test_is_lucky()
{
    isLucky(5);
    isLucky('a');
    isLucky(true);
    isLucky(3.f);
}

#endif