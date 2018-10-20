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
    /*private*/ virtual QString getName(File* f);
    /*private*/ virtual QString getDescription(File* f);
    /*private*/ virtual QString getTypeDescription(File* f);
    /*private*/ virtual ImageIcon* getIcon(File* f);
    /*private*/ virtual bool isTraversable(File* f) ;

};

#endif // FILEVIEW_H
