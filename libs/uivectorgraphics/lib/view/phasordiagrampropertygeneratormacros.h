#ifndef PHASORDIAGRAMPROPERTYGENERATORMACROS_H
#define PHASORDIAGRAMPROPERTYGENERATORMACROS_H

#define Q_VECTOR_PROPERTY(type, variable, getter, setter) \
private: \
    Q_PROPERTY(type getter READ getter WRITE setter NOTIFY getter##Changed) \
    Q_SIGNAL void getter##Changed(); \
public: \
    type const& getter() const { return variable; } \
    Q_SLOT void setter(type const &v) { \
        m_vectorPainter.setter(v); \
        if(v == variable) \
            return; \
        variable = v; \
        emit getter##Changed(); \
        update(); \
    } \
private: \
    type variable;
// end Q_VECTOR_PROPERTY


#define Q_VECTOR_ARRAY_PROPERTY(type, idx, variable, getter, setter) \
public: \
    Q_PROPERTY(type getter##idx READ getter##idx WRITE setter##idx NOTIFY getter##Changed##idx) \
    Q_SIGNAL void getter##Changed##idx(); \
    type const& getter##idx() const { return variable##idx; } \
    Q_SLOT void setter##idx(type const &v) { \
        m_vectorPainter.setter(idx, v); \
        if(v == variable##idx) \
            return; \
        variable##idx = v; \
        emit getter##Changed##idx(); \
        update(); \
    } \
private: \
    type variable##idx;
// end Q_VECTOR_ARRAY_PROPERTY


#define Q_VECTOR_DATA_ARRAY_PROPERTY(idx) \
public: \
    Q_PROPERTY(QList<double> vectorData##idx READ vectorData##idx WRITE setVectorData##idx NOTIFY vectorDataChanged##idx) \
    Q_SIGNAL void vectorDataChanged##idx(); \
    const QList<double> &vectorData##idx() const { return m_vectorData##idx; } \
    Q_SLOT void setVectorData##idx(const QList<double> &v) \
    { \
        if (v.length() > 1) \
        m_vectorPainter.setVector(idx, QVector2D(v.at(0), v.at(1))); \
        if(v == m_vectorData##idx) \
            return; \
        m_vectorData##idx = v; \
        emit vectorDataChanged##idx(); \
        update(); \
    } \
private: \
    QList<double> m_vectorData##idx;
// end Q_VECTOR_DATA_ARRAY_PROPERTY

#endif // PHASORDIAGRAMPROPERTYGENERATORMACROS_H
