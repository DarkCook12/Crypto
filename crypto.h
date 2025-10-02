#ifndef CRYPTO_H
#define CRYPTO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Crypto; }
QT_END_NAMESPACE

class Crypto : public QMainWindow
{
    Q_OBJECT

public:
    Crypto(QWidget *parent = nullptr);
    ~Crypto();

private slots:


    void on_pushButton_fileInputForSign_clicked();

    void on_pushButton_fileInputForCheck_clicked();

    void on_pushButton_Sign_clicked();

    void on_pushButton_Keys_clicked();

    void on_pushButton_CheckSign_clicked();


    void on_pushButton_fileInputForKeys_clicked();

    void on_pushButton_fileInputForSign_Keys_clicked();

    void on_pushButton_fileInputForCheck_Keys_clicked();

    void on_pushButton_fileInputForCheck_Params_clicked();

    void on_pushButton_fileInputForSign_Params_clicked();

private:
    Ui::Crypto *ui;
};
#endif // CRYPTO_H
