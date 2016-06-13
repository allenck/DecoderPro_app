#ifndef BLOCKVALUEFILE_H
#define BLOCKVALUEFILE_H
#include "xmlfile.h"

class BlockManager;
class BlockValueFile : public XmlFile
{
    Q_OBJECT
public:
    explicit BlockValueFile(QObject *parent = 0);
    /*public*/ void readBlockValues() /*throws org.jdom2.JDOMException, java.io.IOException */;
    /*public*/ void writeBlockValues() /*throws java.io.IOException*/;
signals:

public slots:
private:
    /*private*/ BlockManager* blockManager;// = null;
    /*private*/ static QString defaultFileName;// = FileUtil::getUserFilesPath()+"blockvalues.xml";
//	/*private*/ Document doc = null;
    /*private*/ QDomElement root;// = null;
    Logger* log;
};

#endif // BLOCKVALUEFILE_H
