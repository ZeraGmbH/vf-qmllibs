#ifndef HELPERSPLUGIN_H
#define HELPERSPLUGIN_H

class HelpersPlugin
{
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // HELPERSPLUGIN_H
