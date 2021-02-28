#ifndef OPTIONSFILE_H
#define OPTIONSFILE_H
#include "xmlfile.h"
#include "exceptions.h"
#include "instancemanagerautodefault.h"

class IOException;
class DispatcherFrame;
class OptionsFile : public XmlFile, public InstanceManagerAutoDefault
{
    Q_OBJECT
    Q_INTERFACES(InstanceManagerAutoDefault)

public:
    OptionsFile(QObject* parent = nullptr);
    ~OptionsFile(){}
    OptionsFile(const OptionsFile&): XmlFile() {}
    /*public*/ static void setDefaultFileName(QString testLocation) ;
    /*public*/ void readDispatcherOptions(DispatcherFrame* f);// throw (JDOMException, IOException);
    /*public*/ void writeDispatcherOptions(DispatcherFrame* f);// throw (IOException);

private:
    /*private*/ static QString defaultFileName;// = FileUtil.getUserFilesPath() + "dispatcheroptions.xml";
    /*private*/ QDomDocument doc;// = null;
    /*private*/ QDomElement root;// = null;
    /*private*/ static Logger* log;
protected:
    /*protected*/ DispatcherFrame* dispatcher = nullptr;

};
Q_DECLARE_METATYPE(OptionsFile)
#endif // OPTIONSFILE_H
