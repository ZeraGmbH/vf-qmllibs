#ifndef UIVECTORGRAPICS_H
#define UIVECTORGRAPICS_H

class UiVectorgraphics
{
public:
    static void registerQml();
private:
    static void registerTypes(const char* uri);
    static bool m_wasRegistered;
};

#endif // UIVECTORGRAPICS_H
