#include "fontpanel.h"
#include "loggerfactory.h"
#include <QVBoxLayout>
#include "jlabel.h"
#include "eventobject.h"
#include "positionablepopuputil.h"
#include <QFontDatabase>
#include <QStringList>
#include "flowlayout.h"
#include "decoratorpanel.h"

///*public*/ class FontPanel extends JPanel implements ItemListener {

/*static*/ /*final*/ QStringList FontPanel::JUSTIFICATION = QStringList() << tr("left") <<
        tr("center") <<
        tr("right");

/*static*/ /*final*/ QStringList FontPanel::STYLES = QStringList() <<tr("Plain") <<
    tr("Bold")<<
    tr("Italic")<<
    tr("Bold/italic");

/*static*/ /*final*/ QStringList FontPanel::FONTSIZE = QStringList() <<"6"<< "8"<< "10"<< "11"<< "12"<< "14"<< "16"<<
        "20"<< "24"<< "28"<< "32"<< "36";


/*public*/ FontPanel::FontPanel(PositionablePopupUtil* util, ActionListener* ca) {
    _util = util;
    _callBack = ca;
    setLayout(new QVBoxLayout());
    makeFontPanels();
}

/*private*/ JPanel* FontPanel::makeBoxPanel(QString caption, JComboBox* box) {
    JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout()); //(panel, BoxLayout.Y_AXIS));
    panel->layout()->addWidget(new JLabel(caption));
    //box->addItemListener(this);
    connect(box, SIGNAL(itemStateChanged(EventObject*)), this, SLOT(itemStateChanged(EventObject*)));
    panel->layout()->addWidget(box);
    return panel;
}

//@SuppressWarnings("unchecked")
/*private*/ void FontPanel::makeFontPanels() {

    JPanel* fontPanel = new JPanel();
    fontPanel->setLayout(new FlowLayout());
    QFont defaultFont = _util->getFont();
    //GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
    QFontDatabase db;
    QStringList fontFamilyNames = db.families(QFontDatabase::Latin); //ge.getAvailableFontFamilyNames();
    QVector<QFont> fonts = QVector<QFont>(fontFamilyNames.length());
    int k = 0;
    for (QString fontFamilyName : fontFamilyNames)
    {
        fonts.replace(k++, QFont(fontFamilyName, defaultFont.style(), defaultFont.pointSize()));
//            {
//                @Override
//                /*public*/ String toString() {
//                    return getFamily();
//                }
//            };
    }
    _fontFaceBox = new AJComboBox1(fonts, FACE);
    fontPanel->layout()->addWidget(makeBoxPanel("EditFont", _fontFaceBox)); // NOI18N
    QFont f = _util->getFont();
    QString family = f.family();
    _fontFaceBox->setCurrentText(family);
    connect(_fontFaceBox, SIGNAL(itemStateChanged(EventObject*)), this, SLOT(itemStateChanged(EventObject*)));

    _fontSizeBox = new AJComboBox1(FONTSIZE, SIZE);
    fontPanel->layout()->addWidget(makeBoxPanel("FontSize", _fontSizeBox)); // NOI18N
    _fontSizeBox->setCurrentText(QString::number(f.pointSize()));
    connect(_fontSizeBox, SIGNAL(itemStateChanged(EventObject*)), this, SLOT(itemStateChanged(EventObject*)));

    _fontStyleBox = new AJComboBox1(STYLES, STYLE); // plain, bold, italic
    fontPanel->layout()->addWidget(makeBoxPanel("FontStyle", _fontStyleBox)); // NOI18N
    QFont::Style s = f.style();
    int w = f.weight();
    if(w == QFont::Weight::Normal  && s == QFont::Style::StyleNormal)
     _fontStyleBox->setCurrentIndex(0); // plain
    else if(QFont::Weight::Bold && s == QFont::Style ::StyleNormal)
     _fontSizeBox->setCurrentIndex(1); // bold
    else if(w == QFont::Weight::Normal  && s == QFont::Style::StyleItalic)
     _fontSizeBox->setCurrentIndex(2); // italic
    else
     _fontSizeBox->setCurrentIndex(3); // bold/italic
    connect(_fontStyleBox, SIGNAL(itemStateChanged(EventObject*)), this, SLOT(itemStateChanged(EventObject*)));

    _fontJustBox = new AJComboBox1(JUSTIFICATION, JUST);
    fontPanel->layout()->addWidget(makeBoxPanel("Justification", _fontJustBox)); // NOI18N
    this->layout()->addWidget(fontPanel);
    connect(_fontJustBox, SIGNAL(itemStateChanged(EventObject*)), this, SLOT(itemStateChanged(EventObject*)));

}

/*public*/ void FontPanel::setFontSelections() {
    _fontFaceBox->setCurrentIndex(_fontFaceBox->findData(qvariant_cast<QFont>(_util->getFont())));
    int row = 4;
    for (int i = 0; i < FONTSIZE.length(); i++) {
        if (_util->getFontSize() == (FONTSIZE.at(i).toInt())) {
            row = i;
            break;
        }
    }
    _fontSizeBox->setCurrentIndex(row);
    _fontStyleBox->setCurrentIndex(_util->getFont().style());
    switch (_util->getJustification()) {
        case PositionablePopupUtil::LEFT:
            row = 0;
            break;
        case PositionablePopupUtil::RIGHT:
            row = 2;
            break;
        case PositionablePopupUtil::CENTRE:
            row = 1;
            break;
        default:
            row = 2;
    }
    _fontJustBox->setCurrentIndex(row);

    _callBack->actionPerformed(nullptr);
}

//@Override
/*public*/ void FontPanel::itemStateChanged(EventObject* e)
{
 AJComboBox1* comboBox = (AJComboBox1*)e->getSource();
 switch (comboBox->_which) {
  case SIZE:
  {
          QString size =  comboBox->currentText();
          _util->setFontSize((size.toFloat()));
          emit fontSizeChanged(size.toInt());
          break;
  }
  case STYLE:
  {
          int style = 0;
          switch (comboBox->currentIndex()) {
              case 0:
                  style = PLAIN;
                  break;
              case 1:
                  style = BOLD;
                  break;
              case 2:
                  style = ITALIC;
                  break;
              case 3:
                  style = (BOLD | ITALIC);
                  break;
              default:
                  log->warn(tr("Unexpected index %1  in itemStateChanged").arg(comboBox->currentIndex()));
                  break;
          }
          _util->setFontStyle(style);
          emit fontStyleChanged(comboBox->currentIndex());
          break;
  }
  case JUST:
  {
          int just = 0;
          switch (comboBox->currentIndex()) {
              case 0:
                  just = PositionablePopupUtil::LEFT;
                  break;
              case 1:
                  just = PositionablePopupUtil::CENTRE;
                  break;
              case 2:
                  just = PositionablePopupUtil::RIGHT;
                  break;
              default:
                  log->warn(tr("Unexpected index %1  in itemStateChanged").arg(comboBox->currentIndex()));
                  break;
          }
          _util->setJustification(just);
          break;
  }
  case FACE:
  {
          QFont font =  comboBox->currentData().value<QFont>();
          _util->setFont(font);
          emit fontFaceChanged(comboBox->currentText());
         break;
  }
  default:
          log->warn(tr("Unexpected _which %1  in itemStateChanged").arg(comboBox->_which));
          break;
 }
 _callBack->actionPerformed(nullptr);
}

/*private*/ /*final*/ /*static*/ Logger* FontPanel::log = LoggerFactory::getLogger("FontPanel");

