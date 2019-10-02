#ifndef DEFAULTIDTAGMANAGERXML_H
#define DEFAULTIDTAGMANAGERXML_H
#include "xmlfile.h"
#include "transpondingtagmanager.h"
class IdTagManager;
class DefaultIdTagManagerXml : public XmlFile
{
 Q_OBJECT
public:
 /*public*/ DefaultIdTagManagerXml(TranspondingTagManager* tagMan, QString baseFileName, QObject* parent= nullptr);
 /*public*/ void load();
 /*public*/ void store() throw (IOException);
 /*public*/ QString getDefaultIdTagFileName();
 /*public*/ QString getIdTagDirectoryName();
 /*public*/ QString getIdTagFileName();
 /*public*/ QString getFileLocation();


private:
 /*private*/ /*final*/ QString FILE_LOCATION;//= FileUtil.getUserFilesPath();
 /*private*/ TranspondingTagManager* manager;
 /*private*/ File* createFile(QString fileName, bool backup);
 /*private*/ void writeFile(QString fileName) throw (FileNotFoundException, IOException);
 /*private*/ void readFile(QString fileName) throw (JDOMException, IOException, IllegalArgumentException);
 /*private*/ static /*final*/ QString IDTAG_DIRECTORY_NAME;// = "idtags"; // NOI18N
 /*private*/ QString IDTAG_BASE_FILENAME;// = "IdTags.xml"; // NOI18N
 static Logger* log;
};

#endif // DEFAULTIDTAGMANAGERXML_H
