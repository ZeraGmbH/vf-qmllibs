#ifndef ZERAFA_H
#define ZERAFA_H

class ZeraFa
{
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // ZERAFA_H
