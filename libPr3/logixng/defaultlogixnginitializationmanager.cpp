#include "defaultlogixnginitializationmanager.h"
#include "printwriter.h"
#include "abstractnamedbean.h"

///*public*/  class DefaultLogixNGInitializationManager implements LogixNG_InitializationManager {


    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::add(LogixNG* logixNG) {
        initLogixNGs.append(logixNG);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::_delete(LogixNG* logixNG) {
        initLogixNGs.removeOne(logixNG);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::_delete(int index) {
        initLogixNGs.removeAt(index);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::moveUp(int index) {
        if ((index == 0) || (index >= initLogixNGs.size())) return;
        LogixNG* logixNG = initLogixNGs.at(index);
          initLogixNGs.removeAt(index);
        initLogixNGs.insert(index-1, logixNG);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::moveDown(int index) {
        if (index+1 >= initLogixNGs.size()) return;
        LogixNG* logixNG = initLogixNGs.at(index);
          initLogixNGs.removeAt(index);
        initLogixNGs.insert(index+1, logixNG);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QList<LogixNG*> DefaultLogixNGInitializationManager::getList() {
        return QList<LogixNG*>(initLogixNGs);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultLogixNGInitializationManager::printTree(QLocale locale, PrintWriter* writer, QString indent) {
        writer->println("LogixNG initialization table:");
        for (LogixNG* logixNG : initLogixNGs) {
            writer->write(indent);
            writer->write(logixNG->NamedBean::getSystemName());
            writer->write(QString(", "));
            writer->write(logixNG->NamedBean::getUserName());
            writer->println();
        }
        writer->println();
    }
