#ifndef FAMILYITEMPANEL_H
#define FAMILYITEMPANEL_H
#include "itempanel.h"
#include <QPushButton>
#include "actionlistener.h"
#include "logger.h"

class JLabel;
class QRadioButton;
class JPanel;
class QGroupBox;
class IconDialog;
class DragJLabel;
class DataFlavor;
class NamedIcon;
class FamilyItemPanel : public ItemPanel
{
    Q_OBJECT
public:
    //explicit FamilyItemPanel(QWidget *parent = 0);
    /*public*/ FamilyItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent = 0);
    /*public*/ void init() ;
    /*public*/ void virtual init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap) ;
    /*public*/ void init(ActionListener* doneAction);
    /*public*/ virtual QMap<QString, NamedIcon *> *getIconMap();
    /*public*/ QString getFamilyName();
    //virtual /*public*/ void updateFamilyIcons();
    /*public*/ JPanel* getBottomPanel() ;
    /*public*/ QPushButton* getUpdateButton();
    /*public*/ void closeDialogs() override;
    /*public*/ virtual void dispose();


signals:

public slots:

private:
    JPanel*    _bottom1Panel = nullptr;  // Typically _showIconsButton and editIconsButton
    QWidget*    _bottom2Panel = nullptr;  // createIconFamilyButton - when all families deleted
    Logger* log;
    QPushButton* _showIconsButton = nullptr;
    QPushButton* _editIconsButton = nullptr;
    QPushButton*  _updateButton = nullptr;
    /*private*/ QMap<QString, NamedIcon*>* _currentIconMap = nullptr;
    /*private*/ QMap<QString, NamedIcon*>* _unstoredMap =  nullptr;
    /*private*/ void checkCurrentMap(QMap<QString, NamedIcon*>* iconMap);
    IconDialog* _dialog = nullptr;
    QButtonGroup* _familyButtonGroup = nullptr;

    /*private*/ QString findFamilyOfMap(QMap<QString, NamedIcon*>* iconMap, QMap<QString, QMap<QString, NamedIcon*>*>* families);
    /*private*/ void addShowButtonToBottom();
    /*private*/ void addFamilyButtonListener (QRadioButton* button, QString family);
    //QString     gbStyleSheet;

private slots:
    /*private*/ QWidget* makeCreateNewFamilyPanel();

protected:
    /*protected*/ QString    _family;
    /*protected*/ JPanel* _iconFamilyPanel = nullptr;  // Holds preview of _iconPanel & _dragIconPanel. They alternate being empty
    /*protected*/ ImagePanel* _dragIconPanel = nullptr; // a panel on _iconFamilyPanel - to drag to control panel, hidden upon [Show Icons]
    /*protected*/ ImagePanel* _iconPanel = nullptr;     // a panel on _iconFamilyPanel - all icons in family, shown upon [Show Icons]
    /*protected*/ JPanel* _previewPanel = nullptr;
    /*protected*/ JPanel* _familyButtonPanel;    // panel of radioButtons to select icon family

    /*protected*/ int _buttonPosition = 0;      // position of _iconFamilyPanel (TableItemPanels use 1)
    /*protected*/ static bool _suppressNamePrompts;// = false;
    /*protected*/ bool _isUnstoredMap = false;

    /*protected*/ virtual void makeBottomPanel(ActionListener* doneAction);
    /*protected*/ virtual void initIconFamiliesPanel();
    /*protected*/ JPanel* makeFamilyButtons (QStringList keySet);
    /*protected*/ void addFamilyPanels(JPanel *familyPanel);
    /*protected*/ void addIconsToPanel(QMap<QString, NamedIcon *> *iconMap, ImagePanel *iconPanel, bool dropIcon);
    /*abstract*/ virtual /*protected*/ DragJLabel* getDragger(DataFlavor* /*flavor*/, QMap <QString, NamedIcon*>* /*map*/, NamedIcon* /*icon*/);
    /*protected*/ virtual void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);
    /*protected*/ JPanel* makeDragIcon(NamedIcon* icon, JLabel* label);
    /*protected*/ virtual void setFamily(QString family) ;
    /*protected*/ virtual void openDialog(QString type, QString family, QMap<QString, NamedIcon *> *iconMap);
    /*protected*/ QString getValidFamilyName(QString family);
    /*protected*/ void addUpdateButtonToBottom(ActionListener* doneAction);
    /*protected*/ virtual JPanel* makeItemButtonPanel();
    /*protected*/ virtual void addCreateDeleteFamilyButtons();
    /*protected*/ void setPreviewBg(int index);
    /*protected*/ void updateBackground0(BufferedImage* im);
    /*protected*/ QString getIconBorderName(QString key);

protected slots:
    /*protected*/ virtual bool newFamilyDialog();
    /*protected*/ void updateFamiliesPanel();
    /*protected*/ void makeDragIconPanel(int position);
    /*protected*/ void familiesMissing();
    /*protected*/ bool isUnstoredMap();
    /*protected*/ void setFamilyButton();
    /*protected*/ void setEditor(Editor* ed) override;
    /*protected*/ void setIconMap(QMap<QString, NamedIcon *> *map);
    /*protected*/ bool addFamily(QString type, QString family, QMap<QString, NamedIcon*>* iconMap);
    /*protected*/ bool mapsAreEqual(QMap<QString, NamedIcon*>* map1, QMap<QString, NamedIcon*>* map2);
    /*protected*/ void deleteFamilySet();
    /*protected*/ virtual void hideIcons();
    /*protected*/ virtual void showIcons();

friend class ItemPalette;
friend class TableItemPanel;
friend class SignalHeadItemPanel;
friend class ButtonListener;
friend class SignalMastItemPanel;
friend class MemoryItemPanel;
friend class ReporterItemPanel;
friend class IndicatorTOItemPanel;
friend class IconDialog;
friend class MultiSensorIconDialog;
friend class MultiSensorItemPanel;
friend class TIconDragJLabel;
friend class IndicatorDragJLabel;
friend class IndicatorTOIconDialog;
};

class ButtonListener : public QObject
{
 Q_OBJECT
 QString family;
 FamilyItemPanel* self;
public slots:
 /*public*/ void actionPerformed();
 ButtonListener* init(QString f, FamilyItemPanel* self);
};
#endif // FAMILYITEMPANEL_H
