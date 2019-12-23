#include "colordialog.h"
#include "loggerfactory.h"
#include "jcolorchooser.h"
#include <QFrame>
#include "positionable.h"
#include "positionablepopuputil.h"
#include "box.h"
#include <QBoxLayout>
#include "decoratorpanel.h"
#include "spinnernumbermodel.h"
#include "jmricolorchooser.h"
#include "placewindow.h"
#include "jtextfield.h"
#include "flowlayout.h"
#include <QPushButton>
#include "editor.h"
#include <QFontDialog>
#include "changelistener.h"
#include "colorselectionmodel.h"

ColorDialog::ColorDialog(QWidget *parent) : JDialog(parent)
{

}
/**
 * A dialog to color a Component in a Window.  The ColorChooser
 * interactively modifies the color of the component on the window
 * until the user either cancels or decides to keep the changes.
 * <p>
 * @author Pete Cressman Copyright (C) 2018
 * @since 4.13.1
 */
///*public*/ class ColorDialog extends JDialog implements ChangeListener {

    /*public*/ /*static*/ /*final*/ int ColorDialog::STRUT = 6;



/**
 *
 * @param client Window holding the component
 * @param t target whose color may be changed
 * @param type whicd attribute is being changed
 * @param ca callback to tell client the component's color was changed.
 * May be null if client doesen't care.
 */
/*public*/ ColorDialog::ColorDialog(QWidget *client, JComponent *t, int type, ActionListener* ca)
 : JDialog(client, true){
    //super(client, true);
    _target = t;
    _compTarget = (t);
    _type = type;
    if (qobject_cast<PositionableLabel*>(t->jself())) {
        PositionableLabel* pos = (PositionableLabel*)t;
        _util = pos->getPopupUtility();
        if (_util != nullptr) {
            _util->setSuppressRecentColor(true);
//            Positionable* p = pos->deepClone();
//            _saveUtil = p->getPopupUtility();
//            p->remove();
            _saveUtil = _util;
        }
   } else {
        _util = nullptr;
    }
    _saveOpaque = ((JComponent*)t)->isOpaque();
    _colorAction = ca;

    //JPanel* panel = new JPanel();
    QWidget* panel = this;
    panel->setLayout(new QVBoxLayout());//(panel, BoxLayout.Y_AXIS));
    panel->layout()->addWidget(Box::createVerticalGlue());
    panel->resize(400, 600);

    QString title;
    switch (type) {
        case ONLY:
            title = tr("Control Panel Color");
            _saveColor = ((JComponent*)t)->getBackground();
            break;
        case BORDER:
        {
            title = tr("Edit Border settings (onpanel)");
            _saveColor = _util->getBorderColor();
            SpinnerNumberModel* model = new SpinnerNumberModel(_util->getBorderSize(), 0, 100, 1);
            JPanel* p = makePanel(DecoratorPanel::makeSpinPanel(tr("Border Size"), new AJSpinner(model, BORDER),nullptr));
            panel->layout()->addWidget(p);
        }
            break;
        case MARGIN:
        {
            title = tr("Edit Margin settings (onpanel)");
            _saveColor = _util->getBackground();
            SpinnerNumberModel* model = new SpinnerNumberModel(_util->getMargin(), 0, 100, 1);
            JPanel* p = makePanel(DecoratorPanel::makeSpinPanel(tr("Margin Size"), new AJSpinner(model, MARGIN),nullptr));
            panel->layout()->addWidget(p);
        }
            break;
        case FONT:
        {
            title = tr("Edit Font settings (onpanel)");
            _saveColor = _util->getForeground();
//            ActionListener* fontAction = ((ActionEvent event) -> {
//                update(); // callback
//            });
            CDActionListener* fontAction = new CDActionListener(this);
#if 0
            FontPanel* fontPanel = new FontPanel(_util, fontAction);
            panel->layout()->addWidget(fontPanel);
            fontPanel->setFontSelections();
#else
      fontPanel = new QFontDialog(((QWidget*)_target->jself())->font());
      fontPanel->setOptions(QFontDialog::NoButtons);
      panel->layout()->addWidget(fontPanel);
#endif
        }
            break;
        case TEXT:
            title = tr("Edit Text Content & settings");
            _saveColor = _util->getBackground();
            _saveText = ((PositionableLabel*)t)->getUnRotatedText();
            panel->layout()->addWidget(makePanel(makeTextSpinnerPanel()));
            panel->layout()->addWidget(Box::createVerticalGlue());
            panel->layout()->addWidget(makePanel(makeTextPanel()));
            break;
        default:
            title = tr("Background Color Chooser");
            _saveColor = ((JComponent*)t)->getBackground();
    }
    panel->layout()->addWidget(Box::createVerticalStrut(STRUT));
    setTitle(/*Bundle.getMessage*/(title));

    _chooser = JmriColorChooser::extendColorChooser(new JColorChooser(_saveColor));
    _chooser->getSelectionModel()->addChangeListener((ChangeListener*)this);
    _chooser->setPreviewPanel(new JPanel());
    panel->layout()->addWidget(_chooser);
    panel->layout()->addWidget(Box::createVerticalStrut(STRUT));

    panel->layout()->addWidget(makeDoneButtonPanel());
    panel->layout()->addWidget(Box::createVerticalGlue());

//    super.addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            cancel();
//        }
//    });
    JDialog::addWindowListener(new CDWindowListener(this));

    //setContentPane(panel);
    setLocation(PlaceWindow::nextTo(client, (JComponent*)t, this));

    pack();
    setVisible(true);
}

JPanel* ColorDialog::makePanel(JPanel* p) {
    JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout());
    panel->layout()->addWidget(p);
    return panel;
}

JPanel* ColorDialog::makeTextSpinnerPanel() {
    JPanel* panel = new JPanel();
    panel->setLayout(new QHBoxLayout());//(panel, BoxLayout.X_AXIS));
    SpinnerNumberModel* model = new SpinnerNumberModel(_util->getFixedWidth(), 0, 1000, 1);
    panel->layout()->addWidget(DecoratorPanel::makeSpinPanel("fixedWidth", new AJSpinner(model, FWIDTH), (ChangeListener*)this));
    panel->layout()->addWidget(Box::createHorizontalStrut(STRUT));
    model = new SpinnerNumberModel(_util->getFixedHeight(), 0, 1000, 1);
    panel->layout()->addWidget(DecoratorPanel::makeSpinPanel("fixedHeight", new AJSpinner(model, FHEIGHT), (ChangeListener*)this));
    return panel;
}

JPanel* ColorDialog::makeTextPanel() {
    JPanel* panel = new JPanel();
    panel->setLayout(new FlowLayout());
    JTextField* textField = new JTextField(_saveText, 25);
#if 0
    textField.addKeyListener(new KeyListener() {
        @Override
        /*public*/ void keyTyped(KeyEvent evt) {
        }
        @Override
        /*public*/ void keyPressed(KeyEvent evt) {
        }
        @Override
        /*public*/ void keyReleased(KeyEvent evt) {
            JTextField tmp = (JTextField) evt.getSource();
            ((PositionableLabel)_target).setText(tmp.getText());
            update();
        }
    });
#endif
    panel->layout()->addWidget(textField);
    return panel;
}

/*protected*/ JPanel* ColorDialog::makeDoneButtonPanel() {
    JPanel* panel = new JPanel();
    panel->setLayout(new FlowLayout());
    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener((ActionEvent event) -> {
//            log.debug("Done button: color= {}", _chooser.getColor());
//            if (_colorAction != null) {
//                _colorAction.actionPerformed(null);
//            }
//            if (_util != null) {
//                _util.setSuppressRecentColor(false);
//            }
//            JmriColorChooser.addRecentColor(_chooser.getColor());
//            dispose();
//    });
    connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(onDoneButton()));
    panel->layout()->addWidget(doneButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener((ActionEvent event) -> {
//            cancel();
//        });
    connect(cancelButton,SIGNAL(clicked(bool)), this, SLOT(cancel()));

    panel->layout()->addWidget(cancelButton);

    return panel;
}

void ColorDialog::onDoneButton()
{
    log->debug(tr("Done button: color= %1").arg(_chooser->getColor().name()));
    if (_colorAction != nullptr) {
        _colorAction->actionPerformed();
    }
    if (_util != nullptr) {
        _util->setSuppressRecentColor(false);
    }
    JmriColorChooser::addRecentColor(_chooser->getColor());
    _done=true;
    dispose();

}
void ColorDialog::cancel() {
    if (_util != nullptr) {
        PositionableLabel* pl = (PositionableLabel*)_target->jself();
        pl->getEditor()->setAttributes(_saveUtil, (Positionable*)pl);
        _util->setSuppressRecentColor(false);
        pl->updateSize();
        if (_type == TEXT) {
            ((PositionableLabel*)_target)->setText(_saveText);
        }
    } else {
        ((PositionableLabel*)_target)->setBackground(_saveColor);
    }
    ((PositionableLabel*)_target)->setOpaque(_saveOpaque);
    log->debug(tr("Cancel: color= %1").arg(_saveColor.name()));
    dispose();
}

/*private*/ void ColorDialog::update() {
    if (_util != nullptr) {
        Positionable* pl = (Positionable*)_compTarget;
        pl->getEditor()->setAttributes(_util, pl);
    }
}

//@Override
/*public*/ void ColorDialog::stateChanged(ChangeEvent* e)
{
 QObject* obj = e->getSource();
 if (qobject_cast<AJSpinner*>(obj)) {
     int num =  ((AJSpinner*) obj)->value();
     switch (((AJSpinner*) obj)->_which) {
         case BORDER:
             _util->setBorderSize(num);
             break;
         case MARGIN:
             _util->setMargin(num);
             break;
         case FWIDTH:
             _util->setFixedWidth(num);
             break;
         case FHEIGHT:
             _util->setFixedHeight(num);
             break;
         default:
             log->warn(tr("Unexpected _which %1  in stateChanged").arg(((AJSpinner*) obj)->_which));
             break;
     }
 }
 else
 {
  log->debug(tr("stateChanged: color= %1").arg(_chooser->getColor().name()));
  if (_util != nullptr)
  {
   switch (_type)
   {
    case BORDER:
        _util->setBorderColor(_chooser->getColor());
        break;
    case MARGIN:
        _util->setBackgroundColor(_chooser->getColor());
        break;
    case FONT:
    case TEXT:
        _util->setForeground(_chooser->getColor());
        break;
    default:
     break;
   }
  } else {
      _compTarget->setOpaque(true);
      _compTarget->setBackground(_chooser->getColor());
  }
 }
 update();
}

/*private*/ /*final*/ /*static*/ Logger* ColorDialog::log = LoggerFactory::getLogger("ColorDialog");
