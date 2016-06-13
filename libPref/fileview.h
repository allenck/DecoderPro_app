#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QObject>

class ImageIcon;
class File;
class FileView : public QObject
{
    Q_OBJECT
public:
    explicit FileView(QObject *parent = 0);

signals:

public slots:
private:
    /*private*/ QString getName(File* f);
    /*private*/ QString getDescription(File* f);
    /*private*/ QString getTypeDescription(File* f);
    /*private*/ ImageIcon* getIcon(File* f);
    /*private*/ bool isTraversable(File* f) ;

};

#endif // FILEVIEW_H
