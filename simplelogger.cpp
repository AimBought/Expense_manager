#include "simplelogger.h"
#include <QtWidgets/qmessagebox.h>
#include <string>


SimpleLogger::SimpleLogger() {}

void SimpleLogger::logMessage(std::string message)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.setWindowTitle("Feedback");
    msgBox.exec();
}
