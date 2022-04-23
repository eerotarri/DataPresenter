/********************************************************************************
** Form generated from reading UI file 'valuetabledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALUETABLEDIALOG_H
#define UI_VALUETABLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ValueTableDialog
{
public:

    void setupUi(QDialog *ValueTableDialog)
    {
        if (ValueTableDialog->objectName().isEmpty())
            ValueTableDialog->setObjectName(QString::fromUtf8("ValueTableDialog"));
        ValueTableDialog->resize(400, 300);

        retranslateUi(ValueTableDialog);

        QMetaObject::connectSlotsByName(ValueTableDialog);
    } // setupUi

    void retranslateUi(QDialog *ValueTableDialog)
    {
        ValueTableDialog->setWindowTitle(QCoreApplication::translate("ValueTableDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ValueTableDialog: public Ui_ValueTableDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALUETABLEDIALOG_H
