#ifndef SERVLETCONFIG_H
#define SERVLETCONFIG_H
#include <QStringListIterator>
#include <QObject>


class ServletContext;
/*public*/ class ServletConfig  : public QObject{
 Q_OBJECT
public:
    /*public*/ virtual QString getServletName() {return "";}

    /*public*/ virtual ServletContext* getServletContext() {return NULL;}

    /*public*/ virtual QString getInitParameter(QString /*string*/) {return "";}

    /*public*/ virtual QStringListIterator getInitParameterNames() =0;
};
#endif // SERVLETCONFIG_H
