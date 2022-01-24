#ifndef CSVIMPORTER_H
#define CSVIMPORTER_H

#include <QObject>
#include "file.h"
#include "exceptions.h"
#include "cvtablemodel.h"

class Logger;
class CsvImporter : public QObject
{
 Q_OBJECT
public:
 /*public*/ CsvImporter(File* file, CvTableModel* cvModel, QObject* parent = nullptr) /*throw (IOException)*/;


signals:

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CsvImporter");

};

#endif // CSVIMPORTER_H
