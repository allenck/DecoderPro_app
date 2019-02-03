#ifndef FAMILYITEMPANEL_H
#define FAMILYITEMPANEL_H
#include "itempanel.h"
#include <QPushButton>
#include "actionlistener.h"
#include "logger.h"

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

signals:

public slots:
//    void on_showIconsButton_clicked();
    void on_newFamilyButton_clicked();

private:
    JPanel*    _bottom1Panel = nullptr;  // Typically _showIconsButton and editIconsButton
    QWidget*    _bottom2Panel = nullptr;  // createIconFamilyButton - when all families deleted
    Logger* log;
    QPushButton*   _showIconsButton = nullptr;
    QPushButton* _editIconsButton = nullptr;
    QPushButton*   _updateButton = nullptr;
    /*private*/ QMap<QString, NamedIcon*>* _currentIconMap = nullptr;
    /*private*/ QMap<QString, NamedIcon*>* _unstoredMap =  nullptr;
    /*private*/ void checkCurrentMap(QMap<QString, NamedIcon*>* iconMap);
    IconDialog* _dialog = nullptr;
    QButtonGroup* _familyButtonGroup = nullptr;

    /*private*/ QString findFamilyOfMap(QMap<QString, NamedIcon*>* iconMap, QMap<QString, QMap<QString, NamedIcon*>*>* families);
    /*private*/ void addShowButtonToBottom();
    /*private*/ void addFamilyButtonListener (QRadioButton* button, QString family);
    QString     gbStyleSheet;

private slots:
    /*private*/ QWidget* makeCreateNewFamilyPanel();
    void on_showIconsButton();

protected:
    /*protected*/ QString    _family;
    /*protected*/ QWidget*    _iconFamilyPanel =nullptr;
    /*protected*/ ImagePanel* _dragIconPanel=nullptr; // contained in _iconFamilyPanel - sample to drag to control panel
    /*protected*/ ImagePanel* _iconPanel =nullptr;     // panel contained in _iconFamilyPanel - all icons in family
    /*protected*/ QWidget* _previewPanel = nullptr;
    /*protected*/ JPanel* _familyButtonPanel = nullptr;    // panel of radioButtons to select icon family

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
//    /*protected*/ virtual QWidget* makeBottom1Panel();
//    /*protected*/ virtual QWidget* makeBottom2Panel();
//    /*protected*/ virtual QWidget* makeBottom3Panel(ActionListener* doneAction, QWidget* bottom1Panel) ;
    /*protected*/ virtual void setFamily(QString family) ;
    /*protected*/ virtual void openDialog(QString type, QString family, QMap<QString, NamedIcon *> *iconMap);
    /*protected*/ void closeDialogs();
    /*protected*/ bool _suppressDragging;
    /*protected*/ QString getValidFamilyName(QString family);
    /*protected*/ void addUpdateButtonToBottom(ActionListener* doneAction);
    /*protected*/ JPanel* makeItemButtonPanel();
    /*protected*/ void addCreateDeleteFamilyButtons();
    /*protected*/ void setPreviewBg(int index);
    /*protected*/ void updateBackground0(BufferedImage* im);
    /*protected*/ QString getIconBorderName(QString key);

protected slots:
//    /*protected*/ void openEditDialog();
    /*protected*/ bool newFamilyDialog();
    /*protected*/ void updateFamiliesPanel();
    /*protected*/ void makeDragIconPanel(int position);
    /*protected*/ void familiesMissing();
    /*protected*/ bool isUnstoredMap();
    /*protected*/ void setFamilyButton();
    /*protected*/ void setEditor(Editor* ed);
    /*protected*/ void setIconMap(QMap<QString, NamedIcon *> *map);
    /*protected*/ bool addFamily(QString type, QString family, QMap<QString, NamedIcon*>* iconMap);
    /*protected*/ bool mapsAreEqual(QMap<QString, NamedIcon*>* map1, QMap<QString, NamedIcon*>* map2);
    /*protected*/ void deleteFamilySet();
    /*protected*/ virtual void hideIcons();
    /*protected*/ virtual void showIcons();
    void on_editIconsButton();

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
