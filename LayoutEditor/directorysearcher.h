#ifndef DIRECTORYSEARCHER_H
#define DIRECTORYSEARCHER_H

#include <QObject>
#include <QFileDialog>
#include "actionlistener.h"

class JTextField;
class PreviewDialog;
class JFrame;
class DirectorySearcher : public QObject
{
    Q_OBJECT
public:
    /*public*/ static DirectorySearcher* instance();
    /*public*/ QDir* searchFS();
    /*public*/ void cancelLooking();
    /*public*/ void close();
    /*public*/ void openDirectory(bool addDir);

signals:

public slots:
private:
    explicit DirectorySearcher(QObject *parent = 0);

    // For choosing image directories
    static QFileDialog* _directoryChooser;// = NULL;
    static DirectorySearcher* _instance;
    /*private*/ static QDir* getDirectory(QString msg, bool recurseDirs);
    QDir* _addDir;
    /*private*/ void showWaitFrame() ;
    /*private*/ void closeWaitFrame();
    PreviewDialog* _previewDialog;// = NULL;
    JFrame* _waitDialog = nullptr;
    JTextField* _waitText;// = new JTextField();
    bool _quitLooking;// = false;
    /*private*/ static bool hasImageFiles(QDir* dir);
    /*private*/ void doPreviewDialog(QDir* dir, ActionListener* addAction, ActionListener* moreAction,
                                 ActionListener* lookAction, ActionListener* cancelAction,
                                 int startNum);
    /*private*/ void getImageDirectory(QDir* dir, QStringList filter) ;
    void displayMore(QDir* dir, bool oneDir);
    void keepLooking();
    friend class AActionListener;
    friend class MActionListener;
    friend class LActionListener;
    friend class CActionListener;
};
class AActionListener : public  ActionListener {
 Q_OBJECT
    QDir* dir;
    DirectorySearcher* s;
public:
    /*public*/ AActionListener(QDir* d, DirectorySearcher* s);
    /*public*/ void actionPerformed(JActionEvent* a = 0);
};
class MActionListener : public  ActionListener {
    Q_OBJECT
    QDir* dir;
    bool oneDir;
    DirectorySearcher* s;
public:
    /*public*/ MActionListener(QDir* d, bool o, DirectorySearcher* s);
    /*public*/ void actionPerformed(JActionEvent* a = 0);
};
class LActionListener : public  ActionListener {
    Q_OBJECT
    DirectorySearcher* s;
public:
    LActionListener(DirectorySearcher* s);

    /*public*/ void actionPerformed(JActionEvent* a = 0);
};
class CActionListener : public  ActionListener {
    Q_OBJECT
    DirectorySearcher* s;
public:
    CActionListener(DirectorySearcher* s);
    /*public*/ void actionPerformed(JActionEvent* a = 0);
};

#endif // DIRECTORYSEARCHER_H
