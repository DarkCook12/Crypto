 #include "crypto.h"
#include "ui_crypto.h"
#include "JavaExtentions.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
Crypto::Crypto(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Crypto)
{
    ui->setupUi(this);
}

Crypto::~Crypto()
{
    delete ui;
}


void Crypto::on_pushButton_Sign_clicked()
{
    const QString filePath = ui->textEdit_FileNameSign->toPlainText().trimmed();
    if (filePath.isEmpty() || !QFileInfo::exists(filePath)) {
        QMessageBox::warning(this, "Внимание", "Укажите существующий файл для подписи");
        return;
    }
    const QString filePathKeys = ui->textEdit_FileNameKeys->toPlainText().trimmed();
    if (filePathKeys.isEmpty() || !QFileInfo::exists(filePathKeys)) {
        QMessageBox::warning(this, "Внимание", "Укажите существующий файл ключей для подписи");
        return;
    }
    const QString filePathParams = ui->textEdit_FileNameParams->toPlainText().trimmed();
    if (filePathParams.isEmpty() || !QFileInfo::exists(filePathParams)) {
        QMessageBox::warning(this, "Внимание", "Укажите существующий файл параметров для подписи");
        return;
    }

    QString stderrText; int code = 0;
    const auto out = JavaExtentions::runJavaProcess(JavaExtentions::javaExePath(), JavaExtentions::argsSign_Jar(filePath, filePathKeys, filePathParams), 60000, &stderrText, &code);
    if (code != 0 && !stderrText.isEmpty()) {
        QMessageBox::warning(this,"Подпись",QStringLiteral("Java stderr:\n%1").arg(stderrText));
        return;
    }

    QMessageBox::information(this, "Результат подписи",
        out + (stderrText.isEmpty() ? "" : "\n\nstderr:\n" + stderrText));
}

void Crypto::on_pushButton_CheckSign_clicked()
{
    const QString filePath = ui->textEdit_FileNameCheckSign->toPlainText().trimmed();
    if (filePath.isEmpty() || !QFileInfo::exists(filePath)) {
        QMessageBox::warning(this, "Внимание", "Укажи существующий файл для проверки");
        return;
    }
    const QString filePathKeys = ui->textEdit_FileNameCheckSign_Keys->toPlainText().trimmed();
    if (filePathKeys.isEmpty() || !QFileInfo::exists(filePathKeys)) {
        QMessageBox::warning(this, "Внимание", "Укажи существующий файл ключей для проверки");
        return;
    }
    const QString filePathParams = ui->textEdit_FileNameCheck_Params->toPlainText().trimmed();
    if (filePathParams.isEmpty() || !QFileInfo::exists(filePathParams)) {
        QMessageBox::warning(this, "Внимание", "Укажи существующий файл параметров для проверки");
        return;
    }

    QString stderrText; int code = 0;
    const auto out = JavaExtentions::runJavaProcess(JavaExtentions::javaExePath(), JavaExtentions::argsCheck_Jar(filePath, filePathKeys, filePathParams), 60000, &stderrText, &code);
    if (code != 0 && !stderrText.isEmpty()) {
        QMessageBox::warning(this,"Подпись",QStringLiteral("Java stderr:\n%1").arg(stderrText));
        return;
    }

    QMessageBox::information(this, "Результат проверки",
        out + (stderrText.isEmpty() ? "" : "\n\nstderr:\n" + stderrText));
}


void fileInput(QTextEdit* target, const QString& filter, bool directoryMode = false ){
    target->clear();
    QWidget w;
    QString filePath;
    if(directoryMode){
        filePath = QFileDialog::getExistingDirectory(&w,"Выбрать папку",QDir::homePath());
    }
    else{
        filePath = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),filter);
    }
    if(!filePath.isEmpty()){
        target->setText(filePath);
    }


}
void Crypto::on_pushButton_fileInputForSign_clicked()
{
    fileInput(ui->textEdit_FileNameSign,"Все файлы (*.*)");
}
void Crypto::on_pushButton_fileInputForCheck_clicked()
{
    fileInput(ui->textEdit_FileNameCheckSign,"Все файлы (*.*)");
}
void Crypto::on_pushButton_fileInputForSign_Keys_clicked()
{
    fileInput(ui->textEdit_FileNameKeys,"",true);

}
void Crypto::on_pushButton_fileInputForCheck_Keys_clicked()
{
    fileInput(ui->textEdit_FileNameCheckSign_Keys,"Все файлы (*.*)");

}
void Crypto::on_pushButton_fileInputForCheck_Params_clicked()
{
    fileInput(ui->textEdit_FileNameCheck_Params,"Параметры (*.txt*)");
}
void Crypto::on_pushButton_fileInputForSign_Params_clicked()
{
    fileInput(ui->textEdit_FileNameParams,"Параметры (*.txt*)");
}


void Crypto::on_pushButton_clicked()
{
    int PC = 1;
    if (PC == 1){
        ui->textEdit_FileNameCheckSign->setText("C:/Users/user/Documents/отпросиловки конфетник.docx");
        ui->textEdit_FileNameKeys->setText("C:/Users/user/Documents");
        ui->textEdit_FileNameParams->setText("C:/Users/user/Documents/params.txt");
        ui->textEdit_FileNameSign->setText("C:/Users/user/Documents/отпросиловки конфетник.docx");
        ui->textEdit_FileNameCheckSign_Keys->setText("C:/Users/user/Documents/public_key.txt");
        ui->textEdit_FileNameCheck_Params->setText("C:/Users/user/Documents/params.txt");
    }
}

