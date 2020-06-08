#include "convertdialog.h"
#include "circuitbuilder.h"
#include "positionablelabel.h"
#include "circuitbuilder.h"
#include "turnouticon.h"
#include <QScrollArea>
#include"placewindow.h"
#include "instancemanager.h"
#include "indicatorturnouticon.h"
#include "oblock.h"
#include "turnouticon.h"
#include "indicatortrackicon.h"
#include "controlpaneleditor.h"

//class ConvertDialog extends JDialog {


ConvertDialog::ConvertDialog(CircuitBuilder* cb, PositionableLabel* pos, OBlock* block, QWidget *parent)
 : JDialog(cb->_editor, true)

{
    //super(cb._editor, true);
    _parent = cb;
    _pos = pos;
#if 0
    addWindowListener(new java.awt.event.WindowAdapter() {
        @Override
        public void windowClosing(java.awt.event.WindowEvent e) {
            _parent._editor.highlight(null);
        }
    });
#endif
    if (pos == nullptr) {
        dispose();
        return;
    }
    _filler = pos->makePaletteFrame("Dummy");
    QString title;
    ActionListener* updateAction;
    if (qobject_cast<TurnoutIcon*>(pos->self())) {
        title = "IndicatorTO";
        _panel = new CDIndicatorTOItemPanel(_filler, title, nullptr, nullptr, _parent->_editor, this);
//        {
//            @Override
//            protected void showIcons() {
//                 super.showIcons();
//                 displayIcons();
//            }
//            @Override
//            protected void hideIcons() {
//                super.hideIcons();
//                displayIcons();
//            }
//        };
//        updateAction = (ActionEvent a) -> {
//            convertTO(block);
//        };
    } else {
        title = "IndicatorTrack";
        _panel = new CDIndicatorItemPanel(_filler, title, nullptr,  _parent->_editor,this);
//        {
//            @Override
//            protected void showIcons() {
//                super.showIcons();
//                displayIcons();
//            }
//            @Override
//            protected void hideIcons() {
//                super.hideIcons();
//                displayIcons();
//            }
//        };
//        updateAction = (ActionEvent a) -> {
//            convertSeg(block);
//        };
    }
    _panel->init(updateAction);

/*            JPanel content = new JPanel();
    content.setLayout(new BoxLayout(content, BoxLayout.Y_AXIS));
    content.add(new JLabel(Bundle.getMessage("notIndicatorIcon")));
    content.add(_panel);
    Dimension dim = content.getPreferredSize();
    */
    JPanel* buttonPanel = _panel->getBottomPanel();
    _panel->getUpdateButton()->setText(tr("Convert Icon"));
    QPushButton* button = new QPushButton(tr("Continue"));
    //button.addActionListener((ActionEvent a) -> {
    connect(button, &QPushButton::clicked, [=]{
        dispose();
    });
    buttonPanel->layout()->addWidget(button);
    JPanel* p = new JPanel(new FlowLayout());
     p->layout()->addWidget(new JLabel(tr("Not all of the track icons are indicator icons. Do you want to convert them?")));
    _panel->layout()->addWidget(p/*, 0*/);
    QSize dim = _panel->sizeHint();

    QScrollArea* sp = new QScrollArea(/*_panel*/);
    sp->setWidget(_panel);
    sp->setWidgetResizable(true);
    dim = QSize(dim.width() +25, dim.height() + 25);
    sp->resize(dim);
    sp->resize(dim);
    layout()->addWidget(sp);
    setTitle((title));
    pack();
    ((PlaceWindow*)InstanceManager::getDefault("PlaceWindow"))->nextTo(cb->_editor, pos, this);
     setVisible(true);
}

/*
 * Do for dialog what FamilyItemPanel, ItemPanel and DisplayFrame
 * need to do for reSizeDisplay and reSize
 */
/*private*/ void ConvertDialog::displayIcons() {
    QSize newDim = _panel->sizeHint();
//    QSize deltaDim = _panel->shellDimension(_panel);
//    QSize dim = QSize(deltaDim.width() + newDim.width(), deltaDim.height() + newDim.height());
//    resize(dim);
    update();
    pack();
}

/*private*/ void ConvertDialog::convertTO(OBlock* block) {
    IndicatorTurnoutIcon* t = new IndicatorTurnoutIcon(_parent->_editor);
    t->setOccBlockHandle(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(block->getSystemName(), block));
    t->setTurnout(((TurnoutIcon*) _pos)->getNamedTurnout());
    t->setFamily(_panel->getFamilyName());

    QMap<QString,QMap<QString, NamedIcon*>*>* iconMap = ((IndicatorTOItemPanel*)_panel)->getIconMaps();
    QMapIterator<QString, QMap<QString, NamedIcon*>*> it(*iconMap);//.entrySet().iterator();
    while (it.hasNext()) {
        //Entry<String, HashMap<String, NamedIcon>> entry = it.next();
        QString status = it.key();
        QMapIterator<QString, NamedIcon*> iter(*it.value());
        while (iter.hasNext()) {
            //Entry<String, NamedIcon> ent = iter.next();
            t->setIcon(status, iter.key(), new NamedIcon(iter.value()));
        }
    }
    t->setLevel(Editor::TURNOUTS);
    t->setScale(_pos->getScale());
    t->rotate(_pos->getDegrees());
    finishConvert(t, block);
}

/*private*/ void ConvertDialog::convertSeg(OBlock* block) {
    IndicatorTrackIcon* t = new IndicatorTrackIcon(_parent->_editor);
    t->setOccBlockHandle(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(block->getSystemName(), block));
    t->setFamily(_panel->getFamilyName());

    QMap<QString, NamedIcon*>* iconMap = _panel->getIconMap();
    QMapIterator<QString, NamedIcon*> it(*iconMap);//.entrySet().iterator();
    while (it.hasNext()) {
        it.next();
        t->setIcon(it.key(), new NamedIcon(it.value()));
    }
    t->setLevel(Editor::TURNOUTS);
    t->setScale(_pos->getScale());
    t->rotate(_pos->getDegrees());
    finishConvert(t, block);
}

/*
 * Replace references to _oldIcon with pos
 */
/*private*/ void ConvertDialog::finishConvert(Positionable* pos, OBlock* block) {
    QList<Positionable*>* selectionGroup = _parent->_editor->getSelectionGroup();
    selectionGroup->removeOne(_pos);
    selectionGroup->append(pos);
    QList<Positionable*>* circuitIcons = _parent->getCircuitIcons(block);
    circuitIcons->removeOne(_pos);
    circuitIcons->append(pos);
    pos->setLocation(_pos->getLocation());
    _pos->remove();
    _parent->_editor->putItem(pos);
    pos->updateSize();
    _parent->_editor->highlight(nullptr);
    dispose();
    _filler->dispose();
}

