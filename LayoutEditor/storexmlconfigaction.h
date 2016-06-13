#ifndef STOREXMLCONFIGACTION_H
#define STOREXMLCONFIGACTION_H
#include "loadstorebaseaction.h"
#include "logger.h"
#include "liblayouteditor_global.h"

class File;
class LIBLAYOUTEDITORSHARED_EXPORT StoreXmlConfigAction : public LoadStoreBaseAction
{
    Q_OBJECT
public:
    explicit StoreXmlConfigAction(QObject *parent = 0);
    /*public*/ StoreXmlConfigAction(QString s, QObject *parent = 0);
    static /*public*/ File* getFileName(JFileChooser* fileChooser);
    /*public*/ static File* getFileCustom(JFileChooser* fileChooser);

signals:

public slots:
    /*public*/ void actionPerformed(/*ActionEvent* e*/);
private:
    Logger* log;
    void common();
};

#endif // STOREXMLCONFIGACTION_H
