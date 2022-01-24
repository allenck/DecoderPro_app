#include "connectionlabel.h"
#include "connectionconfig.h"
#include "jmrixconfigpane.h"
#include "connectionstatus.h"

/**
 * A JLabel that listens to a system connection and reports its status
 *
 * @author Randall Wood
 */
// /*public*/ final class ConnectionLabel extends JLabel implements PropertyChangeListener {


    /*public*/ ConnectionLabel::ConnectionLabel(ConnectionConfig* connection, QWidget* parent) : JLabel(parent){
        //super();
        this->connection = connection;
        if (connection->name() == (JmrixConfigPane::NONE)) {
            this->setText("");
        } else {
            ConnectionStatus::instance()->addConnection(connection->getConnectionName(), connection->getInfo());
            this->update();
        }
        ConnectionStatus::instance()->addPropertyChangeListener(this);
    }

    /*protected*/ void ConnectionLabel::update() {
        if (this->connection->getDisabled()) {
            return;
        }
        QString name = this->connection->getConnectionName();
        if (name == "") {
            name = this->connection->getManufacturer();
        }
        if (ConnectionStatus::instance()->isConnectionOk(this->connection->getConnectionName(),this->connection->getInfo())) {
            this->setForeground(Qt::black);
            this->setText(tr("%1: using %2 on %3").arg(
                    name, this->connection->name(), this->connection->getInfo()));
        } else {
            this->setForeground(Qt::red);
            this->setText(tr("%1: ERROR %2 using %3").arg(
                    name, this->connection->name(), this->connection->getInfo()));
        }
        //this->revalidate();

    }

    //@Override
    /*public*/ void ConnectionLabel::propertyChange(PropertyChangeEvent* /*evt*/) {
        this->update();
    }
