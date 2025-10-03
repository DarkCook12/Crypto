    #include "crypto.h"
#include "ui_crypto.h"
#include <QDebug>
#include <QFileDialog>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
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
//проверка комитов 3
static QString runJavaProcess(const QString& javaExe,
                              const QStringList& args,
                              int timeoutMs,
                              QString* stderrOut,
                              int* exitCode)
{
    QProcess p;
    p.start(javaExe, args);
    if (!p.waitForStarted(5000))
        return QStringLiteral("Не удалось запустить Java: %1").arg(javaExe);

    if (!p.waitForFinished(timeoutMs)) {
        p.kill();
        if (stderrOut) *stderrOut = QStringLiteral("Таймаут выполнения");
        if (exitCode)  *exitCode  = -1;
        return {};
    }
    if (stderrOut) *stderrOut = QString::fromUtf8(p.readAllStandardError());
    if (exitCode)  *exitCode  = p.exitCode();
    return QString::fromUtf8(p.readAllStandardOutput());
}

// Обёртки: настрой тут ОДИН из двух режимов — JAR или класс:
static QString javaExePath()
{
#ifdef Q_OS_WIN
    return "C:/Program Files/Java/jdk-25/bin/java.exe";
#else
    return "java";
#endif
}

static QString jarPath(int  number_operation)
{
    if(number_operation == 1){
        return QCoreApplication::applicationDirPath() + "/analyzer.jar"; //sign.jar
    }
    else if(number_operation == 2){
        return QCoreApplication::applicationDirPath() + "/analyzer.jar"; // check.jar
    }
    else if(number_operation == 3){
        return QCoreApplication::applicationDirPath() + "/analyzer.jar"; // generate_keys
    }
    return 0;
}

// ---- Вариант А: запуск JAR с Main-Class ----
static QStringList argsSign_Jar(const QString& file)  { return { "-jar", jarPath(1), "sign",  file }; } // добавить файл с параметрами и ключами static QStringList argsSign_Jar(const QString& file)  { return { "-jar", jarPath(), "sign",  file, params, keys }; }
static QStringList argsCheck_Jar(const QString& file) { return { "-jar", jarPath(2), "check", file }; } // добавить файл с параметрами и ключами static QStringList argsCheck_Jar(const QString& file) { return { "-jar", jarPath(), "check", file, params, keys }; }
static QStringList argsKeys_Jar()                     { return { "-jar", jarPath(3), "keys"       }; } // придумать как должно работать

// ---- Вариант Б: запуск по классу (если нет Main-Class в JAR) ----
// static QStringList argsSign_Cls (const QString& file){ return { "", jarPath(), "", "sign",  file }; }
// static QStringList argsCheck_Cls(const QString& file){ return { "", jarPath(), "", "check", file }; }
// static QStringList argsKeys_Cls()                    { return { "-", jarPath(), "Main", "keys"       }; }

static bool parseJson(const QString& json, QJsonObject* out, QString* error) // подумать над парсингом и как это выводить
{
    QJsonParseError pe{};
    auto doc = QJsonDocument::fromJson(json.toUtf8(), &pe);
    if (pe.error != QJsonParseError::NoError || !doc.isObject()) {
        if (error) *error = QStringLiteral("JSON parse error: %1\nRaw: %2").arg(pe.errorString(), json);
        return false;
    }
    *out = doc.object();
    return true;
}

//SIGN
void Crypto::on_pushButton_Sign_clicked()
{
    ui->textEdit_keys->clear();
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
    const auto out = runJavaProcess(javaExePath(), argsSign_Jar(filePath), 60000, &stderrText, &code);
    //   const auto out = runJavaProcess(javaExePath(), argsSign_Jar(filePath, filePathParams, filePathKeys), 60000, &stderrText, &code);
    if (code != 0 && !stderrText.isEmpty()) {
        QMessageBox::warning(this,"Подпись",QStringLiteral("Java stderr:\n%1").arg(stderrText));
        return;
    }

    QJsonObject o; QString perr;
    if (parseJson(out, &o, &perr)) {
        ui->textEdit_keys->append(QStringLiteral("SIGN: %1\nsize=%2\nsignature=%3")
                                  .arg(o.value("filename").toString())
                                  .arg(o.value("size").toInt())
                                  .arg(o.value("signature").toString()));
    } else {
        QMessageBox::warning(this,"Подпись","Ответ (не-JSON):\n" + out + (stderrText.isEmpty() ? "" : "\n\nstderr:\n"+stderrText));
    }
}

// CHECK
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
    const auto out = runJavaProcess(javaExePath(), argsCheck_Jar(filePath), 60000, &stderrText, &code);
    // const auto out = runJavaProcess(javaExePath(), argsCheck_Jar(filePath, filePathParams, filePathKeys), 60000, &stderrText, &code)
    if (code != 0 && !stderrText.isEmpty()) {
        QMessageBox::warning(this,"Подпись",QStringLiteral("Java stderr:\n%1").arg(stderrText));
        return;
    }

    QJsonObject o; QString perr;
    if (parseJson(out, &o, &perr)) {
        ui->textEdit_keys->append(QStringLiteral("CHECK: %1 -> ok=%2")
                                  .arg(o.value("filename").toString())
                                  .arg(o.value("ok").toBool() ? "true" : "false"));
       QMessageBox::information(this,"Проверка подписи","Подпись действительна");
    } else {
        QMessageBox::warning(this,"Подпись","Ответ (не-JSON):\n" + out + (stderrText.isEmpty() ? "" : "\n\nstderr:\n"+stderrText));
    }
}

//KEYS
void Crypto::on_pushButton_Keys_clicked() //gavno убрать
{
    ui->textEdit_keys->clear();

    QString stderrText; int code = 0;
    const auto out = runJavaProcess(javaExePath(), argsKeys_Jar(), 30000, &stderrText, &code);
    if (code != 0 && !stderrText.isEmpty()) {
        QMessageBox::warning(this,"Подпись",QStringLiteral("Java stderr:\n%1").arg(stderrText));
        return;
    }

    QJsonObject o; QString perr;
    if (parseJson(out, &o, &perr)) {
        ui->textEdit_keys->append(QStringLiteral("KEYS:\npublic=%1\nprivate=%2")
                                  .arg(o.value("publicKey").toString())
                                  .arg(o.value("privateKey").toString()));
    } else {
        QMessageBox::warning(this,"Подпись","Ответ (не-JSON):\n" + out + (stderrText.isEmpty() ? "" : "\n\nstderr:\n"+stderrText));
    }
}

void Crypto::on_pushButton_fileInputForSign_clicked()
{
    ui->textEdit_FileNameSign->clear();
    QWidget w;
    QString filePath_Sign = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Текстовые (*.txt);;Все файлы (*.*)");
    ui->textEdit_FileNameSign->setText(filePath_Sign);

}
void Crypto::on_pushButton_fileInputForCheck_clicked()
{
    ui->textEdit_FileNameCheckSign->clear();
    QWidget w;
    QString filePath_Check = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Текстовые (*.txt);;Все файлы (*.*)");
    ui->textEdit_FileNameCheckSign->setText(filePath_Check);

}
void Crypto::on_pushButton_fileInputForKeys_clicked() // gavno
{
    ui->textEdit_FileNameKeys->clear();
    QWidget w;
    QString filePath = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Текстовые (*.txt);;Все файлы (*.*)");
    ui->textEdit_FileNameKeys->setText(filePath);

}
void Crypto::on_pushButton_fileInputForSign_Keys_clicked()
{
    ui->textEdit_FileNameKeys->clear();
    QWidget w;
    QString filePath_Sign_Keys = QFileDialog::getExistingDirectory(&w,"Выбрать папку",QDir::homePath());
    ui->textEdit_FileNameKeys->setText(filePath_Sign_Keys);

}
void Crypto::on_pushButton_fileInputForCheck_Keys_clicked()
{
    ui->textEdit_FileNameCheckSign_Keys->clear();
    QWidget w;
    QString filePath_Sign_Keys = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Текстовые (*.txt);;Все файлы (*.*)");
    ui->textEdit_FileNameCheckSign_Keys->setText(filePath_Sign_Keys);
}
void Crypto::on_pushButton_fileInputForCheck_Params_clicked()
{
    ui->textEdit_FileNameCheck_Params->clear();
    QWidget w;
    QString filePath_Sign_Keys = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Параметры (*.propetries)");
    ui->textEdit_FileNameCheck_Params->setText(filePath_Sign_Keys);
}
void Crypto::on_pushButton_fileInputForSign_Params_clicked()
{
    ui->textEdit_FileNameParams->clear();
    QWidget w;
    QString filePath_Sign_Keys = QFileDialog::getOpenFileName(&w,"Открыть файл",QDir::homePath(),"Параметры (*.properties)");
    ui->textEdit_FileNameParams->setText(filePath_Sign_Keys);
}

