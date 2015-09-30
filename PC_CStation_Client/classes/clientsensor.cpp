#include "clientsensor.h"

ClientSensor::ClientSensor(AbstractServer *parent) : ClientItem(parent)
{
    letter = ' ';
}

QString ClientSensor::getValueString()
{
    return "";
}

void ClientSensor::sendNow()
{
    if (is_enabled) {
        AbstractServer *server = dynamic_cast<AbstractServer*>(this->parent());
        if (server != NULL) {
            emit sendingInitiate(getValueString());
        }
    }
}
