#ifndef ZERACOMPONENTS_H
#define ZERACOMPONENTS_H

class ZeraComponents
{
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // ZERACOMPONENTS_H
