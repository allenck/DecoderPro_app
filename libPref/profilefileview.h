#ifndef PROFILEFILEVIEW_H
#define PROFILEFILEVIEW_H
#include "fileview.h"

class ProfileFileView : public FileView
{
    Q_OBJECT
public:
    explicit ProfileFileView(QObject *parent = 0);
    /*public*/ QString getDescription(File* f) ;
    /*public*/ bool isTraversable(File* f);
    /*public*/ ImageIcon* getIcon(File* f);

signals:

public slots:

};

#endif // PROFILEFILEVIEW_H
