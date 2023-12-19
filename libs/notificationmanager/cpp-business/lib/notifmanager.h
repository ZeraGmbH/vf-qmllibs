#ifndef NotifManager_H
#define NotifManager_H


class NotifManager
{
public:
    static void registerQml();
private:
    static void registerType();
    static bool m_wasRegistered;
};

#endif // NotifManager_H
