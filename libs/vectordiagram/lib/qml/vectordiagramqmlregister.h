#ifndef VECTORDIAGRAMQMLREGISTER_H
#define VECTORDIAGRAMQMLREGISTER_H

class VectorDiagramQmlRegister
{
public:
    static void registerQml();
private:
    static void registerTypes();
    static bool m_wasRegistered;
};

#endif // VECTORDIAGRAMQMLREGISTER_H
