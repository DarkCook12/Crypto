/********************************************************************************
** Form generated from reading UI file 'crypto.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRYPTO_H
#define UI_CRYPTO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Crypto
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_fileInputForSign;
    QGroupBox *groupBox;
    QTextEdit *textEdit_FileNameSign;
    QPushButton *pushButton_Sign;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_fileInputForCheck;
    QPushButton *pushButton_CheckSign;
    QTextEdit *textEdit_FileNameCheckSign;
    QPushButton *pushButton_Keys;
    QTextEdit *textEdit_keys;
    QGroupBox *groupBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Crypto)
    {
        if (Crypto->objectName().isEmpty())
            Crypto->setObjectName("Crypto");
        Crypto->resize(800, 600);
        Crypto->setMinimumSize(QSize(800, 600));
        Crypto->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(Crypto);
        centralwidget->setObjectName("centralwidget");
        pushButton_fileInputForSign = new QPushButton(centralwidget);
        pushButton_fileInputForSign->setObjectName("pushButton_fileInputForSign");
        pushButton_fileInputForSign->setGeometry(QRect(530, 100, 25, 25));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../Downloads/explorer.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_fileInputForSign->setIcon(icon);
        pushButton_fileInputForSign->setFlat(true);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 30, 761, 151));
        textEdit_FileNameSign = new QTextEdit(groupBox);
        textEdit_FileNameSign->setObjectName("textEdit_FileNameSign");
        textEdit_FileNameSign->setGeometry(QRect(10, 60, 500, 50));
        pushButton_Sign = new QPushButton(groupBox);
        pushButton_Sign->setObjectName("pushButton_Sign");
        pushButton_Sign->setGeometry(QRect(610, 70, 140, 25));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 200, 761, 141));
        pushButton_fileInputForCheck = new QPushButton(groupBox_2);
        pushButton_fileInputForCheck->setObjectName("pushButton_fileInputForCheck");
        pushButton_fileInputForCheck->setGeometry(QRect(520, 70, 25, 25));
        pushButton_fileInputForCheck->setIcon(icon);
        pushButton_fileInputForCheck->setFlat(true);
        pushButton_CheckSign = new QPushButton(groupBox_2);
        pushButton_CheckSign->setObjectName("pushButton_CheckSign");
        pushButton_CheckSign->setGeometry(QRect(610, 60, 140, 25));
        textEdit_FileNameCheckSign = new QTextEdit(groupBox_2);
        textEdit_FileNameCheckSign->setObjectName("textEdit_FileNameCheckSign");
        textEdit_FileNameCheckSign->setGeometry(QRect(10, 60, 500, 50));
        pushButton_Keys = new QPushButton(centralwidget);
        pushButton_Keys->setObjectName("pushButton_Keys");
        pushButton_Keys->setGeometry(QRect(620, 440, 140, 25));
        textEdit_keys = new QTextEdit(centralwidget);
        textEdit_keys->setObjectName("textEdit_keys");
        textEdit_keys->setGeometry(QRect(20, 380, 500, 151));
        textEdit_keys->setReadOnly(true);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 360, 761, 191));
        Crypto->setCentralWidget(centralwidget);
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        pushButton_fileInputForSign->raise();
        pushButton_Keys->raise();
        textEdit_keys->raise();
        menubar = new QMenuBar(Crypto);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Crypto->setMenuBar(menubar);
        statusbar = new QStatusBar(Crypto);
        statusbar->setObjectName("statusbar");
        Crypto->setStatusBar(statusbar);

        retranslateUi(Crypto);

        QMetaObject::connectSlotsByName(Crypto);
    } // setupUi

    void retranslateUi(QMainWindow *Crypto)
    {
        Crypto->setWindowTitle(QCoreApplication::translate("Crypto", "\320\246\320\270\321\204\321\200\320\276\320\262\320\260\321\217 \320\277\320\276\320\264\320\277\320\270\321\201\321\214", nullptr));
        pushButton_fileInputForSign->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("Crypto", "\320\237\320\276\320\264\320\277\320\270\321\201\321\214", nullptr));
        pushButton_Sign->setText(QCoreApplication::translate("Crypto", "\320\237\320\276\320\264\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Crypto", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 \320\277\320\276\320\264\320\277\320\270\321\201\320\270", nullptr));
        pushButton_fileInputForCheck->setText(QString());
        pushButton_CheckSign->setText(QCoreApplication::translate("Crypto", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214 \320\277\320\276\320\264\320\277\320\270\321\201\321\214", nullptr));
        pushButton_Keys->setText(QCoreApplication::translate("Crypto", "\320\222\321\213\320\262\320\276\320\264 \320\272\320\273\321\216\321\207\320\265\320\271", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Crypto", "\320\232\320\273\321\216\321\207\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Crypto: public Ui_Crypto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRYPTO_H
