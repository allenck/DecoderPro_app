#ifndef DIALOGERRORHANDLER_H
#define DIALOGERRORHANDLER_H

#include "errorhandler.h"

#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DialogErrorHandler : public ErrorHandler
{
    Q_OBJECT
public:
    explicit DialogErrorHandler(QObject *parent = 0);
    /*public*/ void handle(ErrorMemo* e);
    /*public*/ void done();

signals:

public slots:

};

#endif // DIALOGERRORHANDLER_H
