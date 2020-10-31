#include "throttlespreferences.h"
#include "fileutil.h"
#include "propertychangeevent.h"
#include <rosterentry.h>

//ThrottlesPreferences::ThrottlesPreferences(QObject *parent) :
//    QObject(parent)
//{
//}
// /*public*/ class ThrottlesPreferences {

/*public*/ ThrottlesPreferences::ThrottlesPreferences(QObject *parent)
{
    common();
}
/*public*/ ThrottlesPreferences::ThrottlesPreferences(const ThrottlesPreferences&)
{
    common();
}

void ThrottlesPreferences::common()
{
 init();
 QString dirname = FileUtil::getUserFilesPath()+ "throttle" +QDir::separator();
 FileUtil::createDirectory(dirname);
 prefFile = dirname+ "ThrottlesPreferences.xml";
 ThrottlesPrefsXml* prefs = new ThrottlesPrefsXml();
 QFile* file = new QFile(prefFile );
 QDomElement root;
 try
 {
  root = prefs->rootFromFile(file);
 }
 catch (FileNotFoundException e2)
 {
  log->info("Did not find throttle preferences file.  This is normal if you haven't saved the preferences before");
  root = QDomElement();
 }
 catch (Exception e) {
  log->error("Exception while loading throttles preferences: " + e.getMessage());
  root = QDomElement();
 }
 if (!root.isNull())
  load(root.firstChildElement("throttlesPreferences"));
}

void ThrottlesPreferences::init()
{
  log = new Logger("ThrottlesPreferences");
 _useExThrottle = true;
 _useToolBar = true;
 _useFunctionIcon = false;
 _resizeWinImg = false;
 _useRosterImage = true;
 _enableRosterSearch = true;
 _enableAutoLoad = true;
 _hideUndefinedFunButton = false;
 _ignoreThrottlePosition = true;
 _saveThrottleOnLayoutSave = true;
 dirty = false;

 _winDim =  QSize(800,600);

}

/*public*/ void ThrottlesPreferences::load(QDomElement e)
{
 if (e.isNull()) return;
 QString a;
 QString b;
 if ((a = e.attribute("isUsingExThrottle")) != "" )  setUseExThrottle( a==("true"));
 if ((a = e.attribute("isUsingToolBar")) != "" )  setUsingToolBar( a==("true") == 0 );
    if ((a = e.attribute("isResizingWindow")) != "" )  setResizeWindow( a==("true") );
    if ((a = e.attribute("isUsingFunctionIcon")) != "" )  setUsingFunctionIcon( a==("true") );
    if (((a = e.attribute("windowDimensionWidth")) != "" ) && ((b = e.attribute("windowDimensionHeight")) != "" ))
        setWindowDimension(  QSize ( a.toInt(),  b.toInt() ));
    if ((a = e.attribute("isSavingThrottleOnLayoutSave")) != "" ) setSaveThrottleOnLayoutSave( a==("true") );
    if ((a = e.attribute("isUsingRosterImage")) != "" )  setUseRosterImage( a==("true") );
    if ((a = e.attribute("isEnablingRosterSearch")) != "" )  setEnableRosterSearch( a==("true") );
    if ((a = e.attribute("isAutoLoading")) != "" )  setAutoLoad( a==("true")  );
    if ((a = e.attribute("isHidingUndefinedFunctionButtons")) != "" )  setHideUndefinedFuncButt( a==("true") );
    if ((a = e.attribute("isIgnoringThrottlePosition")) != "" )  setIgnoreThrottlePosition( a==("true")  );
    this->dirty = false;
}
/**
 * @return true if preferences need to be saved
 */
/*public*/ bool ThrottlesPreferences::isDirty() {
    return dirty;
}
/**
 * An extension of the abstract XmlFile. No changes made to that class.
 *
 */
//static class ThrottlesPrefsXml extends XmlFile { }

/*private*/ QDomElement ThrottlesPreferences::store() {
    QDomDocument doc;

    QDomElement e = doc.createElement("throttlesPreferences");
    e.setAttribute("isUsingExThrottle", isUsingExThrottle()?"true":"false");
    e.setAttribute("isUsingToolBar", isUsingToolBar()?"true":"false" );
    e.setAttribute("isUsingFunctionIcon", isUsingFunctionIcon()?"true":"false" );
    e.setAttribute("isResizingWindow", isResizingWindow()?"true":"false" );
    e.setAttribute("windowDimensionWidth", (int)getWindowDimension().width() );
    e.setAttribute("windowDimensionHeight", (int)getWindowDimension().height() );
    e.setAttribute("isSavingThrottleOnLayoutSave", isSavingThrottleOnLayoutSave()?"true":"false");
    e.setAttribute("isUsingRosterImage", isUsingRosterImage()?"true":"false");
    e.setAttribute("isEnablingRosterSearch", isEnablingRosterSearch()?"true":"false");
    e.setAttribute("isAutoLoading", isAutoLoading()?"true":"false");
    e.setAttribute("isHidingUndefinedFunctionButtons", isHidingUndefinedFuncButt()?"true":"false");
    e.setAttribute("isIgnoringThrottlePosition", isIgnoringThrottlePosition()?"true":"false");
    return e;
}

/*public*/ void ThrottlesPreferences::set(ThrottlesPreferences* tp)
{
    setWindowDimension (tp->getWindowDimension() );
    setUseExThrottle (tp->isUsingExThrottle() );
    setUsingToolBar(tp->isUsingToolBar() );
    setUsingFunctionIcon(tp->isUsingFunctionIcon() );
    setResizeWindow(tp->isResizingWindow());
    setSaveThrottleOnLayoutSave(tp->isSavingThrottleOnLayoutSave());
    setUseRosterImage(tp->isUsingRosterImage());
    setEnableRosterSearch(tp->isEnablingRosterSearch());
    setAutoLoad(tp->isAutoLoading());
    setHideUndefinedFuncButt(tp->isHidingUndefinedFuncButt());
    setIgnoreThrottlePosition(tp->isIgnoringThrottlePosition());

//    if (listeners != null)
//        for (int i = 0; i < listeners.size(); i++) {
//            PropertyChangeListener l = listeners.get(i);
//            PropertyChangeEvent e = new PropertyChangeEvent(this, "ThrottlePreferences", null, this );
//            l.propertyChange(e);
//        }
    emit propertyChange( new PropertyChangeEvent(this, "ThrottlePreferences", QVariant(), VPtr<ThrottlesPreferences>::asQVariant(this) ));
}

/*public*/ bool ThrottlesPreferences::compareTo(ThrottlesPreferences* tp)
{
    return( getWindowDimension() != tp->getWindowDimension() ||
            isUsingExThrottle() != tp->isUsingExThrottle() ||
            isUsingToolBar() != tp->isUsingToolBar() ||
            isUsingFunctionIcon() != tp->isUsingFunctionIcon() ||
            isResizingWindow() != tp->isResizingWindow()||
            isSavingThrottleOnLayoutSave() != tp->isSavingThrottleOnLayoutSave()||
            isUsingRosterImage() != tp->isUsingRosterImage()||
            isEnablingRosterSearch() != tp->isEnablingRosterSearch()||
            isAutoLoading() != tp->isAutoLoading() ||
            isHidingUndefinedFuncButt() != tp->isHidingUndefinedFuncButt() );
}

/*public*/ void ThrottlesPreferences::save() {
    if (prefFile == NULL)
        return;
    //XmlFile xf = new XmlFile(){};   // odd syntax is due to XmlFile being abstract
    XmlFile* xf = new XmlFile();
    xf->makeBackupFile(prefFile );
    QFile* file=new QFile(prefFile );
    QFileInfo* info = new QFileInfo(prefFile);
    try {
        //The file does not exist, create it before writing
        //QFile parentDir=file->getParentFile();
        QDir parentDir = info->absoluteDir();
        if(!parentDir.exists())
         //if (!parentDir.mkdir()) // make directory, check result
            if(!parentDir.mkdir(parentDir.path()))
                log->error("failed to make parent directory");
        //if (!file-createNewFile()) // create file, check result
        if(!file->open(QIODevice::ReadWrite))
            log->error("createNewFile failed");
    } catch (Exception exp) {
        log->error("Exception while writing the new throttles preferences file, may not be complete: "+exp.getMessage());
    }

    try {
        //Element root = new Element("throttles-preferences");
        QDomDocument doc("throttles-preferences SYSTEM \"/xml/DTD/throttles-preferences.dtd\"");
        QDomElement root;
        QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
        doc.appendChild(xmlProcessingInstruction);
        //QDomDocument doc = XmlFile::newDocument(root, XmlFile::dtdLocation+"throttles-preferences.dtd");
        // add XSLT processing instruction
        // <?xml-stylesheet type="text/xsl" href="XSLT/throttle.xsl"?>
/*TODO    		java.util.Map<String,String> m = new java.util.HashMap<String,String>();
        m.put("type", "text/xsl");
        m.put("href", jmri.jmrit.XmlFile.xsltLocation+"throttles-preferences.xsl");
        ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
        doc.addContent(0,p);*/
        root = doc.createElement("throttles-preferences");
        doc.appendChild(root);
        root.appendChild( store() );
        xf->writeXML(file, doc);
    }
    catch (Exception ex){
        log->warn("Exception in storing throttles preferences xml: "+ex.getMessage());
    }
}

/*public*/ QSize ThrottlesPreferences::getWindowDimension() {
    return _winDim ;
}
/*public*/ void ThrottlesPreferences::setWindowDimension(QSize d) {
    _winDim = d;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isUsingExThrottle() {
    return _useExThrottle;
}
/*public*/ void ThrottlesPreferences::setUseExThrottle(bool exThrottle) {
    _useExThrottle = exThrottle;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isUsingToolBar() {
    return _useToolBar;
}
/*public*/ void ThrottlesPreferences::setUsingToolBar(bool win4all) {
    _useToolBar = win4all;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isUsingFunctionIcon() {
    return _useFunctionIcon;
}
/*public*/ void ThrottlesPreferences::setUsingFunctionIcon(bool useFunctionIcon) {
    _useFunctionIcon = useFunctionIcon;
    this->dirty = true;
}
/**
 * Return true if throttle icons should be shown; this returns
 * isUsingExThrottle() &quot;&quot; isUsingFunctionIcon()
 *
 * @return true if throttle icons should be used.
 */
/*public*/ bool ThrottlesPreferences::isUsingIcons() {
    return (isUsingExThrottle() && isUsingFunctionIcon());
}

/*public*/ bool ThrottlesPreferences::isResizingWindow() {
    return _resizeWinImg;
}
/*public*/ void ThrottlesPreferences::setResizeWindow(bool winImg) {
    _resizeWinImg = winImg;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isUsingRosterImage() {
    return _useRosterImage;
}
/*public*/ void ThrottlesPreferences::setUseRosterImage(bool rosterImage) {
    _useRosterImage = rosterImage;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isEnablingRosterSearch() {
    return _enableRosterSearch;
}
/*public*/ void ThrottlesPreferences::setEnableRosterSearch(bool b) {
    _enableRosterSearch = b;
    this->dirty = true;
}
/*public*/ void ThrottlesPreferences::setAutoLoad(bool b) {
    _enableAutoLoad = b;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isAutoLoading() {
    return _enableAutoLoad;
}
/*public*/ void ThrottlesPreferences::setHideUndefinedFuncButt(bool b) {
    _hideUndefinedFunButton = b;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isHidingUndefinedFuncButt() {
    return _hideUndefinedFunButton;
}
/*public*/ void ThrottlesPreferences::setIgnoreThrottlePosition(bool b) {
    _ignoreThrottlePosition = b;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isIgnoringThrottlePosition() {
    return _ignoreThrottlePosition;
}
/*public*/ void ThrottlesPreferences::setSaveThrottleOnLayoutSave(bool b) {
    _saveThrottleOnLayoutSave = b;
    this->dirty = true;
}
/*public*/ bool ThrottlesPreferences::isSavingThrottleOnLayoutSave() {
 return _saveThrottleOnLayoutSave;
}

#if 0
/**
 * Add an AddressListener. AddressListeners are notified when the user
 * selects a new address and when a Throttle is acquired for that address
 *
 * @param l
 */
/*public*/ void addPropertyChangeListener(PropertyChangeListener l) {
    if (listeners == null)
        listeners = new ArrayList<PropertyChangeListener>(2);
    if (!listeners.contains(l))
        listeners.add(l);
}

/**
 * Remove an AddressListener.
 *
 * @param l
 */
/*public*/ void removePropertyChangeListener(PropertyChangeListener l) {
    if (listeners == null)
        return;
    if (listeners.contains(l))
        listeners.remove(l);
}
#endif
