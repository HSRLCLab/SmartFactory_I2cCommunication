/**
 * @file I2cCommunication.cpp
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief I2c communication library for master and slave
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "I2cCommunication.h"


I2cCommunication::I2cCommunication() 
{
#ifdef MASTER
    Wire.begin();
#else
    Wire.begin(I2CSLAVEADDRESP);
    Wire.onRequest(RequestCallback);
    Wire.onReceive(ReadCallback);
#endif
}


String I2cCommunication::getReceivedEvent()
{
    DBFUNCCALLln("I2cCommunication::getReceivedEvent()");
    return (pReceivedI2cMessage->event);
}
/*
bool I2cCommunication::getReadFlag_I2c()
{
    DBFUNCCALLln("I2cCommunication::getReadFlag_I2c()");
    return READFLAG_I2C;
}

void I2cCommunication::setWriteEvent(String s)
{
    DBFUNCCALLln("I2cCommunication::setWriteEvent()");
    (pWriteMessage.event) = s;
}

void I2cCommunication::setReadFlag_I2c(bool flag)
{
    DBFUNCCALLln("setReadFlag_I2c");
    READFLAG_I2C = flag;
}
*/

#ifdef MASTER
void I2cCommunication::writeMessage(WriteI2cMessage &message)
{
    Wire.beginTransmission(I2CSLAVEADDRESP);
    Wire.write((uint8_t *) &message, (size_t)sizeof(message));
    Wire.endTransmission();
    delay(50);
}

ReceivedI2cMessage I2cCommunication::readMessage()
{
    Wire.requestFrom(I2CSLAVEADDRESP, sizeof(ReceivedI2cMessage));
    while(Wire.available() < sizeof(ReceivedI2cMessage))
    {
        delay(5);
    }
    ReceivedI2cMessage tempMessage;
    Wire.readBytes((char *) &tempMessage, sizeof(tempMessage));
    return tempMessage;
}

/*
String I2cCommunication::getReceivedState()
{
    DBFUNCCALLln("I2cCommunication::getReceivedState()");
    return (pReceivedMessage.state);
}

String I2cCommunication::getReceivedPosition()
{
    DBFUNCCALLln("I2cCommunication::getReceivedPosition()");
    return (pReceivedMessage.position);
}

Package I2cCommunication::getReceivedPackageInformation()
{
    DBFUNCCALLln("I2cCommunication::getReceivedPackageInformation()");
    return (pReceivedMessage.packageInformation);
}

void I2cCommunication::setWriteInformation(String s)
{
    DBFUNCCALLln("I2cCommunication::setWriteInformation");
    (pWriteMessage.information) = s;
}
*/
#else

void I2cCommunication::ReadCallback(int bytes)
{
    DBFUNCCALLln("I2cCommunication::ReadCallback(int bytes)");
    while (0 < Wire.available())
    {
        Wire.readBytes( (char*) pReceivedI2cMessage, sizeof(pReceivedI2cMessage));
    }
}

void I2cCommunication::RequestCallback()
{
    DBFUNCCALLln("I2cCommunication::RequestCallback()");
    Wire.write((char*) &pWriteI2cMessage);
}
#endif

void I2cCommunication::resetReceivedMessage()
{
    DBFUNCCALLln("I2cCommunication::resetMessages()");
    strcpy(pReceivedI2cMessage->event,"null");
    
    #ifdef MASTER
    strcpy(pReceivedI2cMessage->state, "null");
    pReceivedI2cMessage->position = -1;
    pReceivedI2cMessage->packageId = 0;
    strcpy(pReceivedI2cMessage->cargo, "null");
    strcpy(pReceivedI2cMessage->targetDest, "null");

    #else
    strcpy(pReceivedI2cMessage->information, "null");
    #endif
}

void I2cCommunication::resetWriteMessage()
{
    DBFUNCCALLln("I2cCommunication::resetWriteMessages()");
    strcpy(pWriteI2cMessage->event, "null");
    #ifdef MASTER
    strcpy(pWriteI2cMessage->information, "null");
    #else
    strcpy(pWriteI2cMessage->state, "null");
    pWriteI2cMessage->position = -1;
    pWriteI2cMessage->packageId = 0;
    strcpy(pWriteI2cMessage->cargo, "null");
    strcpy(pWriteI2cMessage->targetDest, "null");
    pWriteI2cMessage->error = false;
    pWriteI2cMessage->token = false;
    #endif
}

#ifdef MASTER
void I2cCommunication::setWriteMessage(char *event, char *information)
{
    DBFUNCCALLln("I2cCommunication::setWriteMessage()");
    strcpy(pWriteI2cMessage->event, "null");
    strcpy(pWriteI2cMessage->information, "null");
}
#else
void I2cCommunication::setWriteMessage(char *event, char *state, int position, unsigned int packageId, char *cargo, char *targetDest, bool error, bool token)
{
    DBFUNCCALLln("I2cCommunication::setWriteMessage()");
    strcpy(pWriteI2cMessage->event, event);
    strcpy(pWriteI2cMessage->state, state);
    pWriteI2cMessage->position = position;
    pWriteI2cMessage->packageId = packageId;
    strcpy(pWriteI2cMessage->cargo, cargo);
    strcpy(pWriteI2cMessage->targetDest, targetDest);
    pWriteI2cMessage->error = error;
    pWriteI2cMessage->token = token;
}
#endif


