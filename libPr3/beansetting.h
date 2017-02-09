#ifndef BEANSETTING_H
#define BEANSETTING_H

#include <QObject>
#include "namedbean.h"
#include "namedbeanhandle.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT BeanSetting : public QObject
{
    Q_OBJECT
public:
    //explicit BeanSetting(QObject *parent = 0);
    /*public*/ BeanSetting(NamedBean* t, QString pName, int setting);
    /*public*/ BeanSetting(NamedBean* t, int setting);
    /**
     * Convenience method; check if the Bean currently has the desired setting
     */
    /*public*/ bool check();
    /*public*/ NamedBean* getBean();
    /*public*/ QString getBeanName();
    /*public*/ int getSetting();

signals:
    
public slots:
private:
    /*private final*/ NamedBeanHandle<NamedBean*>* _namedBean;
    /*final private*/ int _setting;

    
};

#endif // BEANSETTING_H
