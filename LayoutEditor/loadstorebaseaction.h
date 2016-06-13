#ifndef LOADSTOREBASEACTION_H
#define LOADSTOREBASEACTION_H

#include "abstractaction.h"
#include <QFileDialog>

class JFileChooser;
class LoadStoreBaseAction : public AbstractAction
{
    Q_OBJECT
public:
    //explicit LoadStoreBaseAction(QObject *parent = 0);
    /*public*/ LoadStoreBaseAction(QString s, QObject *parent = 0);
    QString s;

signals:

public slots:
private:
    static JFileChooser* allFileChooser;// = new JFileChooser(FileUtil::getUserFilesPath());
    static JFileChooser* configFileChooser;// = new JFileChooser(FileUtil::getUserFilesPath());
    static JFileChooser* userFileChooser;// = new JFileChooser(FileUtil::getUserFilesPath());
    /*private*/ JFileChooser* getXmlFileChooser(QString path);
protected:
    /*protected*/ JFileChooser* getAllFileChooser();
    /*protected*/ JFileChooser* getConfigFileChooser() ;
    /*protected*/ JFileChooser* getUserFileChooser();


    friend class StoreXmlConfigAction;
    friend class StoreXmlUserAction;
};

#endif // LOADSTOREBASEACTION_H
