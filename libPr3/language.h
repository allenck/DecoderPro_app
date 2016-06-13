#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT language : public QObject
{
    Q_OBJECT
public:
    explicit language(QObject *parent = 0);
    static void loadLanguage(QString s_locale);
signals:
    
public slots:
    
};

#endif // LANGUAGE_H
