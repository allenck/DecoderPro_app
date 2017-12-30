#include "scriptfilechooser.h"
#include "fileutil.h"
#include "scripts/jmriscriptenginemanager.h"
#include "scripts/scriptenginemanager.h"
#include "filefilter.h"
#include "scripts/scriptenginefactory.h"
#include "filenameextensionfilter.h"
/**
 *
 * @author rhwood
 */
///*public*/ class ScriptFileChooser extends JFileChooser {

/*public*/ ScriptFileChooser::ScriptFileChooser(QObject* parent) : JFileChooser(FileUtil::getScriptsPath(), parent){
    //super(FileUtil.getScriptsPath());
    this->init();
}

/*public*/ ScriptFileChooser::ScriptFileChooser(QString path, QObject* parent) : JFileChooser(path, parent) {
    //super(path);
    this->init();
}

/*public*/ ScriptFileChooser::ScriptFileChooser(File* dir, QObject* parent) : JFileChooser(dir, parent) {
    //super(dir);
    this->init();
}

/*private*/ void ScriptFileChooser::init() {
    QList<QString> allExtensions = QList<QString>();
    QMap<QString, FileFilter> filters = QMap<QString, FileFilter>();
    QList<QString> filterNames = QList<QString>();
#if 0 // TODO:
//    JmriScriptEngineManager::getDefault()->getManager().getEngineFactories().stream().forEach((ScriptEngineFactory factory) ->
    foreach(ScriptEngineFactory* factory, JmriScriptEngineManager::getDefault()->getManager()->getEngineFactories())
    {
        QList<QString> extensions = factory->getExtensions();
        //allExtensions.addAll(extensions);
        foreach(QString extension, extensions)
         allExtensions.append(extension);
        QString name = this->fileForLanguage(factory->getLanguageName());
        filterNames.append(name);

        filters.insert(name, FileNameExtensionFilter(name, extensions.toVector(); //String[extensions.size()])));
    }//);
    FileFilter* allScripts = new FileNameExtensionFilter(tr("allScripts"), allExtensions.toArray(QStringList());//new String[allExtensions.size()]));
    this->addChoosableFileFilter(allScripts);
    //filterNames.stream().sorted().forEach((filter) ->
    foreach(QString filter, filterNames)
    {
        this->addChoosableFileFilter(filters.value(filter));
    }//);
    this->setFileFilter(allScripts);
    this->setFileSelectionMode(JFileChooser::FILES_ONLY);
#endif
}

/*private*/ QString ScriptFileChooser::fileForLanguage(QString language) {
    try {
        return /*Bundle.getMessage*/(language);
    } catch (MissingResourceException ex) {
        if (!language.endsWith(/*Bundle.getMessage*/("files"))) { // NOI18N
            return language + " " + tr("files");
        }
        return language;
    }
}
