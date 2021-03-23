#ifndef __AUTO_LOCK_H__
#define __AUTO_LOCK_H__

#include <mutex>

// apply a auto lock in life
class AutoLock
{
public:
    AutoLock(std::mutex* pLock)
    {
        m_pLock = pLock;
        if (m_pLock)
        {
            m_pLock->lock();
        }
    }

    ~AutoLock()
    {
        if (m_pLock)
        {
            m_pLock->unlock();
        }
    }
private:
    std::mutex*  m_pLock;
};

#endif