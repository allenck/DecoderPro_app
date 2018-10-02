#include "indicatoritempanel.h"
#include "editor.h"
#include "detectionpanel.h"
#include "borderlayout.h"
#include "indicatortrackicon.h"
#include "dataflavor.h"
#include "indicatortrackiconxml.h"

//IndicatorItemPanel::IndicatorItemPanel(QWidget *parent) :
//    FamilyItemPanel(parent)
//{
//}
/**
*  ItemPanel for for Indicating track blocks
*/
///*public*/ class IndicatorItemPanel extends FamilyItemPanel {


/**
* Constructor for plain icons and backgrounds
*/
/*public*/ IndicatorItemPanel::IndicatorItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget *parent) : FamilyItemPanel(parentFrame, type, family, editor, parent)
{
    //super(parentFrame, type, family, editor);
    log = new Logger("IndicatorItemPanel");
}

/**
* Init for creation
* insert panels for detection and train id
*/
/*public*/ void IndicatorItemPanel::init()
{
 if (!_initialized)
 {
  _detectPanel= new DetectionPanel(this, this);
 //((BorderLayout*)layout())->addWidget(_detectPanel, BorderLayout::North);
  //thisLayout->addWidget(_detectPanel,0,Qt::AlignTop);
  thisLayout->insertWidget(0, _detectPanel);
  FamilyItemPanel::init();
 }
}

/**
* Init for update of existing track block
* _bottom3Panel has "Update Panel" button put into _bottom1Panel
*/
/*public*/ void IndicatorItemPanel::init(ActionListener* doneAction, QHash<QString, NamedIcon*>* iconMap) {
    FamilyItemPanel::init(doneAction, iconMap);
    _detectPanel= new DetectionPanel(this);
    //((BorderLayout*)layout())->addWidget(_detectPanel, BorderLayout::North);
    //layout()->addWidget(_detectPanel);
    thisLayout->insertWidget(0, _detectPanel);

}

/**
* Init for conversion of plain track to indicator track
*/
///*public*/ void init(ActionListener doneAction) {
//    super.init(doneAction, NULL);
//}

/*public*/ void IndicatorItemPanel::dispose() {
    if (_detectPanel!=NULL) {
        _detectPanel->dispose();
    }
}

/*protected*/ void IndicatorItemPanel::makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString /*displayKey*/) {
    FamilyItemPanel::makeDndIconPanel(iconMap, "ClearTrack");
}

/*************** pseudo inheritance to DetectionPanel *******************/

/*public*/ bool IndicatorItemPanel::getShowTrainName() {
    return _detectPanel->getShowTrainName();
}

/*public*/ void IndicatorItemPanel::setShowTrainName(bool show) {
    _detectPanel->setShowTrainName(show);
}
/*
public QString getErrSensor() {
    return _detectPanel->getErrSensor();
}

public void setErrSensor(QString name) {
    _detectPanel->setErrSensor(name);
}
*/
/*public*/ QString IndicatorItemPanel::getOccSensor() {
    return _detectPanel->getOccSensor();
}

/*public*/ QString IndicatorItemPanel::getOccBlock() {
    return _detectPanel->getOccBlock();
}

/*public*/ void IndicatorItemPanel::setOccDetector(QString name) {
    _detectPanel->setOccDetector(name);
}

/*public*/ QStringList IndicatorItemPanel::getPaths() {
    return _detectPanel->getPaths();
}

/*public*/ void IndicatorItemPanel::setPaths(QStringList paths) {
    _detectPanel->setPaths(paths);
}

/*******************************************************/

/*protected*/ DragJLabel* IndicatorItemPanel::getDragger(DataFlavor* flavor, QHash<QString, NamedIcon*>* map) {
    return new IndicatorDragJLabel(flavor, map, this);
}

///*protected*/ class IndicatorDragJLabel extends DragJLabel {
//    Hashtable <QString, NamedIcon> iconMap;

//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ IndicatorDragJLabel::IndicatorDragJLabel(DataFlavor* flavor, QHash<QString, NamedIcon*>* map, IndicatorItemPanel* self) : DragJLabel(flavor, self)
{
 //super(flavor);
 iconMap = map;
 this->self = self;
}
/*public*/ bool IndicatorDragJLabel::isDataFlavorSupported(DataFlavor* flavor)
{
 return DragJLabel::isDataFlavorSupported(flavor);
}
/*public*/ QObject* IndicatorDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
        if (!isDataFlavorSupported(flavor)) {
            return NULL;
        }
        if (iconMap==NULL) {
            self->log->error("IconDragJLabel.getTransferData: iconMap is NULL!");
            return NULL;
        }
        if (self->log->isDebugEnabled()) self->log->debug("IndicatorDragJLabel.getTransferData");
//        IndicatorTrackIcon* t = new IndicatorTrackIcon(_editor);

//        t.setOccBlock(_detectPanel->getOccBlock());
//        t.setOccSensor(_detectPanel->getOccSensor());
//        t.setShowTrain(_detectPanel->getShowTrainName());
//        t.setFamily(_family);

//        Iterator<Entry<QString, NamedIcon>> it = iconMap.entrySet().iterator();
//        while (it.hasNext()) {
//            Entry<QString, NamedIcon> entry = it.next();
//            t.setIcon(entry.getKey(), new NamedIcon(entry.getValue()));
//        }
//        t.setLevel(Editor::TURNOUTS);
//        return t;
    }
QString IndicatorDragJLabel::mimeData()
{
  IndicatorTrackIcon* icon;
 _dataFlavor = new DataFlavor(icon = new IndicatorTrackIcon(NULL), "IndicatorTrackIcon");
 icon->setOccBlock(self->getOccBlock());
 icon->setOccSensor(self->getOccSensor());
 icon->setPaths(self->getPaths());
 icon->setShowTrain(self->getShowTrainName());
 icon->setFamily(self->getFamilyName());
 icon->setLevel(Editor::TURNOUTS);
 QHashIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
 while (iter.hasNext())
 {
   iter.next();
   icon->setIcon(iter.key(), iter.value());
 }
// if(self->getOccBlock() != NULL)
//  _dataFlavor->setMimeTypeParameter("occblock", self->getOccBlock());
// if(self->getOccSensor() != NULL)
//  _dataFlavor->setMimeTypeParameter("occsensor", self->getOccSensor());
// _dataFlavor->setMimeTypeParameter("family", self->_family);

 IndicatorTrackIconXml* xml = new IndicatorTrackIconXml();
 QDomElement e = xml->store((QObject*)icon);
 xml->doc.appendChild(e);
 QString xmldata = xml->doc.toString();
 _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));

 return _dataFlavor->toString();
}

//};
