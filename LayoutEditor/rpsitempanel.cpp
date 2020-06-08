#include "rpsitempanel.h"
#include "loggerfactory.h"
#include "rpspositionicon.h"
#include "editor.h"
#include "dataflavor.h"
#include "vptr.h"

///*public*/ class RPSItemPanel extends FamilyItemPanel {

/*public*/ RPSItemPanel::RPSItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor *editor)
 : FamilyItemPanel(parentFrame, type, family, editor)
{
    //super(parentFrame, type, family, editor);
}

//@Override
/*protected*/ void RPSItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString /*displayKey*/) {
    FamilyItemPanel::makeDndIconPanel(iconMap, "active");
}

/*
 * ****************************************************
 */
//@Override
/*protected*/ DragJLabel* RPSItemPanel::getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon) {
    return new RPSIconDragJLabel(flavor, map, icon, this);
}

//protected class IconDragJLabel extends DragJLabel {

//    HashMap<String, NamedIcon> iconMap;

    /*public*/ RPSIconDragJLabel::RPSIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon, RPSItemPanel* rpsItemPanel)
     : DragJLabel(flavor)
    {
        //super(flavor, icon);
     this->rpsItemPanel = rpsItemPanel;
     iconMap = map;
     this->icon = icon;
    }

    //@Override
    /*public*/ bool RPSIconDragJLabel::isDataFlavorSupported(DataFlavor* flavor) {
        return DragJLabel::isDataFlavorSupported(flavor);
    }

    //@Override
    /*public*/ QVariant RPSIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException, IOException){
        if (!isDataFlavorSupported(flavor)) {
            return QVariant();
        }

        if (rpsItemPanel->log->isDebugEnabled()) {
            rpsItemPanel->log->debug("IconDragJLabel.getTransferData");
        }
        RpsPositionIcon* r = new RpsPositionIcon(rpsItemPanel->_editor);
        r->setActiveIcon(new NamedIcon(iconMap->value("active")));
        r->setErrorIcon(new NamedIcon(iconMap->value("error")));
        r->setSize(r->getPreferredSize().width(), r->getPreferredSize().height());
        r->setLevel(Editor::SENSORS);
        return VPtr<RpsPositionIcon>::asQVariant(r);
    }
//}

/*private*/ /*final*/ /*static*/ Logger* RPSItemPanel::log = LoggerFactory::getLogger("RPSItemPanel");
