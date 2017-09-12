#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>

#include "configuration.h"

#define WT_MOUNT "Mount"
#define WT_UNMOUNT "Unmount"
#define WT_TITLE "Samba Simple Client v0.01"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setWorkGroup(QString workgroup);

    void debug(QString debug_text);
    QString getWorkGroup();
    void updateMountIndication(bool mounted);
    QString getMountPoint();
    QString getServer();
    bool useLogin();
    QString getUserName();
    QString getUserPassword();
    QString getAdvancedOptions();
    void updateLastItems(QStringList items);

private:
    Ui::MainWindow *ui;
    QGridLayout* thisWindowLayout;

    QComboBox   * comboItems     = new QComboBox();
    QTextEdit   * debug_text     = new QTextEdit();
    QLineEdit   * editWorkGroup  = new QLineEdit();
    QLineEdit   * editMountPoint  = new QLineEdit();
    QLineEdit   * editServer  = new QLineEdit();
    QLineEdit   * editLogin  = new QLineEdit();
    QLineEdit   * editPassword  = new QLineEdit();
    QLineEdit   * editAdvancedOptions = new QLineEdit();

    QCheckBox * checkLogin = new QCheckBox("Use Login");

    QPushButton * mount;

private slots:
    void onChangedServer(QString text);
    void onUseLogin(int login);
    void onChangeLastItem(QString);

signals:
    void onMountButton();
    void changedServer(QString);
};

#endif // MAINWINDOW_H
