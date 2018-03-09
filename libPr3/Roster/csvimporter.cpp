#include "csvimporter.h"
#include "loggerfactory.h"
#include "qfile.h"
#include <QTextStream>
#include <QStringList>

/**
 * Import CV values from a generic CSV format CV list file such as those written
 * by the CsvExportAction class.
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 * @author Alex Shepherd Copyright (C) 2003
 * @author Dave Heap Copyright (C) 2014
 */
// /*public*/ class CsvImporter {

    /*private*/ /*final*/ /*static*/ Logger* CsvImporter::log = LoggerFactory::getLogger("CsvImporter");

/*public*/ CsvImporter::CsvImporter(File* file, CvTableModel* cvModel, QObject* parent) throw (IOException) : QObject(parent){
//        FileReader fileReader=NULL;
//        BufferedReader bufferedReader=NULL;
QFile f(file->getPath());
QTextStream* bufferedReader;

    try {
        CvValue* cvObject;
        QString line = NULL;
        QString name = NULL;
        int value = 0;

//            fileReader = new FileReader(file);
//            bufferedReader = new BufferedReader(fileReader);
        if(!f.open(QIODevice::ReadOnly)) throw IOException(tr("File not found: ") + file->toString());
        bufferedReader = new QTextStream(&f);

        while ((line = bufferedReader->readLine()) != NULL)
        {
         QStringList lineStrings = line.split(" *, *");
            if (lineStrings.length() < 2) {
                bufferedReader->device()->close();
                throw  IOException();
            } else if (lineStrings[0] == ("CV")) {
                log->debug("Header OK");
            } else {
                name = lineStrings.at(0).trimmed();
                value = lineStrings.at(1).trimmed().toInt();
                cvObject = cvModel->allCvMap()->value(name);
                if (cvObject == NULL) {
                    log->warn("CV " + name + " was in import file, but not defined by the decoder definition");
                    cvModel->addCV(name, false, false, false);
                    cvObject = cvModel->allCvMap()->value(name);
                }
                cvObject->setValue(value);
            }
        }
    } catch (IOException e) {
        log->error("Error reading file: " + e.getMessage());
    } /*finally */{
        if(bufferedReader!=NULL) {
           bufferedReader->device()->close();
        }
//            if(fileReader!=NULL) {
//               fileReader.close();
//            }
    }
}

