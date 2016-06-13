#ifndef ITEMPALETTE_H
#define ITEMPALETTE_H
#include "jmrijframe.h"
#include <QtXml>
#include <QFrame>
#include "liblayouteditor_global.h"

class ImageIndexEditor;
class ItemPanel;
class NamedIcon;
class Editor;
class CatalogTreeNode;
class ChangeEvent;
class LIBLAYOUTEDITORSHARED_EXPORT ItemPalette : public JmriJFrame
{
    Q_OBJECT
public:
    explicit ItemPalette(QWidget *parent = 0);
    /*public*/ static /*final*/ int STRUT_SIZE;// = 10;

    static QTabWidget* _tabPane;
    static QMap<QString, ItemPanel*>* _tabIndex;

    static QMap<QString, QHash<QString, QHash<QString, NamedIcon*>*>*>* _iconMaps;
    // for now, special case 4 level maps since IndicatorTO is the only case.
    static QMap<QString, QHash<QString, QHash<QString, QHash<QString, NamedIcon*>*>*>*>* _indicatorTOMaps;
    /*public*/ static void storeIcons();
    static CatalogTreeNode* store3levelMap(QString type, QHash<QString, QHash<QString, NamedIcon*>*>* familyMap);
    static /*public*/ void loadIcons();
    static bool loadSavedIcons();
    static QHash<QString, QHash<QString, QHash<QString, NamedIcon*>*>*>*
                                        loadIndicatorFamilyMap(CatalogTreeNode* node);
    static QHash<QString, QHash<QString, NamedIcon*>*>* loadFamilyMap(CatalogTreeNode* node);
    static void loadDefaultIcons();
    static QHash<QString, QHash<QString, NamedIcon*>*>* loadDefaultFamilyMap(QDomNodeList families);
    static QHash<QString, QHash<QString, QHash<QString, NamedIcon*>*>*>* loadDefaultIndicatorTOMap(QDomNodeList typeList);
    /*public*/ ItemPalette(QString _title, Editor* editor, QWidget* parent = 0);
    /*public*/ void stateChanged(ChangeEvent* e);
    /*public*/ void closePanels(/*WindowEvent* e*/);
    static bool familyNameOK(QWidget* frame, QString type, QString family, QStringListIterator it);
    static /*public*/ QString convertText(QString name);

signals:

public slots:
    void tabPaneChanged(int);
 private:
  Logger* log;
  void init();
  /*private*/ void makeMenus(Editor* editor);
  void changeEvent(QEvent *);

protected:
  static /*protected*/ bool addFamily(QWidget* frame, QString type, QString family, QHash<QString, NamedIcon*>* iconMap);
  static /*protected*/ QHash<QString, QHash<QString, NamedIcon*>*>* getFamilyMaps(QString type);
  static /*protected*/ void removeIconMap(QString type, QString family);
  static /*protected*/ QHash<QString, NamedIcon*>* getIconMap(QString type, QString family);
  static /*protected*/ QHash<QString, NamedIcon*>* cloneMap(QHash<QString, NamedIcon*>* map);
  static /*protected*/ QWidget* makeBannerPanel(QString labelText, QWidget* field);
  static /*protected*/ bool addLevel4Family(JmriJFrame* frame, QString type, QString family,
                                 QHash<QString, QHash<QString, NamedIcon*>*>* iconMap);
  static /*protected*/ void addLevel4FamilyMap(QString type, QString family,
                                 QString key, QHash<QString, NamedIcon*>* iconMap);
  static /*protected*/ QHash<QString, QHash<QString, QHash<QString, NamedIcon*>*>*>*
                              getLevel4FamilyMaps(QString type);
  // Currently only needed for IndicatorTO type
  static /*protected*/ QHash<QString, QHash<QString, NamedIcon*>*>*
                              getLevel4Family(QString type, QString family) ;
  static /*protected*/ void removeLevel4IconMap(QString type, QString family, QString key);

friend class FamilyItemPanel;
friend class SignalHeadItemPanel;
friend class IconItemPanel;
friend class MultiSensorItemPanel;
friend class IndicatorTOItemPanel;
friend class IconDialog;
friend class NewFamilyActionListener;
};

class IPEditItemActionListener : public QObject
{
 Q_OBJECT
 Editor* editor;
public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/) ;
public:
 IPEditItemActionListener* init(Editor* ed);
};

#endif // ITEMPALETTE_H
