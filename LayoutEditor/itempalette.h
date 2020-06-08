#ifndef ITEMPALETTE_H
#define ITEMPALETTE_H
#include "displayframe.h"
#include <QtXml>
#include <QFrame>
#include "liblayouteditor_global.h"

class ImageIndexEditor;
class ItemPanel;
class NamedIcon;
class Editor;
class CatalogTreeNode;
class ChangeEvent;
class LIBLAYOUTEDITORSHARED_EXPORT ItemPalette : public DisplayFrame
{
    Q_OBJECT
public:
    explicit ItemPalette(QWidget *parent = 0);
    /*public*/ static /*final*/ int STRUT_SIZE;// = 10;

    static QTabWidget* _tabPane;
    static QMap<QString, ItemPanel*>* _tabIndex;

    static QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* _iconMaps;
    // for now, special case 4 level maps since IndicatorTO is the only case.
    static QMap<QString, QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*>* _indicatorTOMaps;
    /*public*/ static void storeIcons();
    static CatalogTreeNode* store3levelMap(QString type, QMap<QString, QMap<QString, NamedIcon *> *> *familyMap);
    static /*public*/ void loadIcons(Editor* ed);
    static bool loadSavedIcons(Editor* ed);
    static QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>*
                                        loadIndicatorFamilyMap(CatalogTreeNode* node, Editor* ed);
    static QMap<QString, QMap<QString, NamedIcon*>*>* loadFamilyMap(CatalogTreeNode* node, Editor* ed);
    static void loadDefaultIcons(Editor* ed);
    static QMap<QString, QMap<QString, NamedIcon *> *> *loadDefaultFamilyMap(QDomNodeList families, Editor* ed);
    static QMap<QString, QMap<QString, QMap<QString, NamedIcon *> *> *> *loadDefaultIndicatorTOMap(QDomNodeList typeList, Editor*ed);
    static void buildTabPane(ItemPalette* palette, Editor* editor);
    static void addItemTab(ItemPanel* itemPanel, QString key, QString tabTitle);
    static void loadFamilies(QString typeName, QDomNodeList families, Editor* ed);
    static /*public*/ ItemPalette* getDefault(QString title,/* @Nonnull */Editor* ed);

    /*public*/ ItemPalette(QString _title, Editor* editor, QWidget* parent = 0);
    /*public*/ void stateChanged(ChangeEvent* e);
    /*public*/ void closePanels(QCloseEvent *e);
    static bool familyNameOK(QWidget* frame, QString type, QString family, QStringListIterator it);
    static /*public*/ QString convertText(QString name);
    static void loadMissingItemType(QString itemType, Editor* ed);
    static QDomNodeList getDefaultIconItemTypes() throw (JDOMException, IOException);
    /*public*/ void setEditor(Editor* ed);

signals:

public slots:
    void tabPaneChanged(int);
 private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ItemPalette");

  void init(QString title, Editor* ed);
  /*private*/ void makeMenus(Editor* editor);
  void changeEvent(QEvent *);
  /*private*/ ItemPanel* _currentItemPanel = nullptr;

protected:
  static /*protected*/ bool addFamily(QWidget* frame, QString type, QString family, QMap<QString, NamedIcon*>* iconMap);
  static /*protected*/ QMap<QString, QMap<QString, NamedIcon *> *> *getFamilyMaps(QString type);
  static /*protected*/ void removeIconMap(QString type, QString family);
  static /*protected*/ QMap<QString, NamedIcon*>* getIconMap(QString type, QString family);
  static /*protected*/ QMap<QString, NamedIcon*>* cloneMap(QMap<QString, NamedIcon*>* map);
  static /*protected*/ QWidget* makeBannerPanel(QString labelText, QWidget* field);
  static /*protected*/ bool addLevel4Family(JmriJFrame* frame, QString type, QString family, QMap<QString, QMap<QString, NamedIcon*>*>* iconMap);
  static /*protected*/ void addLevel4FamilyMap(QString type, QString family,
                                 QString key, QMap<QString, NamedIcon*>* iconMap);
  static /*protected*/ QMap<QString, QMap<QString, QMap<QString, NamedIcon *> *> *> *getLevel4FamilyMaps(QString type);
  // Currently only needed for IndicatorTO type
  static /*protected*/ QMap<QString, QMap<QString, NamedIcon *> *> *getLevel4Family(QString type, QString family) ;
  static /*protected*/ void removeLevel4IconMap(QString type, QString family, QString key);

friend class FamilyItemPanel;
friend class SignalHeadItemPanel;
friend class IconItemPanel;
friend class MultiSensorItemPanel;
friend class IndicatorTOItemPanel;
friend class IconDialog;
friend class NewFamilyActionListener;
friend class SignalMastItemPanel;
friend class IndicatorTOIconDialog;
};

class IPEditItemActionListener : public QObject
{
 Q_OBJECT
 Editor* editor;
public:
 IPEditItemActionListener();

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/) ;
public:
 IPEditItemActionListener* init(Editor* ed);
};

class IPWindowListener : public WindowListener
{
 ItemPalette* palette;
public:
 IPWindowListener(ItemPalette* palette);
 void windowClosing(QCloseEvent*e) override;
};
#endif // ITEMPALETTE_H
