#ifndef EDITCIRCUITPATHS_H
#define EDITCIRCUITPATHS_H
#include "jmrijframe.h"
#include <QAbstractListModel>

class JToggleButton;
class Path;
class ListSelectionEvent;
class QListView;
class OPath;
class PathListModel;
class JTextField;
class Positionable;
class CircuitBuilder;
class OBlock;
class EditCircuitPaths : public JmriJFrame
{
    Q_OBJECT
public:
    //explicit EditCircuitPaths(QWidget *parent = 0);
    static int STRUT_SIZE;// = 10;
    static bool _firstInstance;// = true;
    static QPoint _loc;// = null;
    static QSize _dim;// = null;
    /*public*/ static /*final*/ QString TEST_PATH;// = "TEST_PATH";
    /*public*/ EditCircuitPaths(QString _title, CircuitBuilder* builder, OBlock* block, QWidget *parent = 0);
public slots:
    /*public*/ void valueChanged(ListSelectionEvent* e = 0);


signals:

public slots:
private:
    /*private*/ OBlock*          _block;
    /*private*/ CircuitBuilder*  _parent;
    // mouse selections of track icons that define the path
    /*private*/ QList<Positionable*>* _pathGroup;// = new ArrayList<Positionable>();

    /*private*/ JTextField*  _pathName;// = new JTextField();
//    /*private*/ QList*       _pathList;
    /*private*/ PathListModel* _pathListModel;
    QListView* _pathList;

    /*private*/ bool _pathChange;// = false;
    /*private*/ JTextField* _length;// = new JTextField();
    /*private*/ JToggleButton* _units;
    /*private*/ QWidget*  MakeButtonPanel();
    /*private*/ QWidget* makeContentPanel();
    /*private*/ void clearPath();
    /*private*/ void showPath(OPath* path);
    /*private*/ void makePath(OPath* path);
    /*private*/ bool checkForSavePath();
    /*private*/ void clearListSelection();
    /*private*/ void addPath();
    /*private*/ OPath* getBlockPath(QString name);\
    Logger* log;
    /*private*/ OPath* makeOPath(QString name, QList<Positionable*>* pathGp, bool showMsg);
    /*private*/ bool findErrors();
    /*private*/ QList<Positionable*>* makePathGroup(OPath* path);
    /*private*/ bool setPathLength(OPath* path);
    /*private*/ static bool pathsEqual(OPath* p1, OPath* p2);
    /*private*/ void changePathNameInIcons(QString name, OPath* path);

private slots:
    /*private*/ void changePathName();
    /*private*/ void deletePath();
    void on_doneClicked();
protected:
    /*protected*/ QList<Positionable*>* getPathGroup();
    /*protected*/ OBlock* getBlock();
    /*protected*/ void updatePath(bool pathChanged);

protected slots:
    /*protected*/ void closingEvent();
friend class PathListModel;
friend class CircuitBuilder;

};
class PathListModel : public QAbstractListModel
{
 Q_OBJECT
    EditCircuitPaths* parent;
public:
    PathListModel(EditCircuitPaths* parent);

    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void dataChange();
    /*public*/ Path* getSelectedValue();
};

#endif // EDITCIRCUITPATHS_H
