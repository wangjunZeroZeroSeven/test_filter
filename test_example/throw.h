#ifndef __THROW_H__
#define __THROW_H__

#include <stdexcept>

    class ExceptionWithCode: public std::runtime_error
    {
    public:
        explicit ExceptionWithCode(const std::string& msg, const int64_t& code): std::runtime_error(msg)
        {
            msg_code = code;
        }

        int64_t GetCode()
        {
            return msg_code;
        }

    private:
        int64_t msg_code;
    };

void test_throw()
{
    try
    {
        throw ExceptionWithCode("test error message..", 50);
    }
    catch(ExceptionWithCode& err)
    {
        std::cout << err.what() << "   ..." << err.GetCode() << std::endl;
    }
}

#endif