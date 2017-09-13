
#include <QProcess>
#include <QGridLayout>
#include <QDir>
#include <QLabel>

#include "windowmain.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(WT_TITLE);

    thisWindowLayout = new QGridLayout;

    mount = new QPushButton(WT_MOUNT);

    thisWindowLayout->addWidget(new QLabel("Last mounted items"));
    thisWindowLayout->addWidget(comboItems);

    thisWindowLayout->addWidget(new QLabel("Samba resource path"));
    thisWindowLayout->addWidget(editServer);

    thisWindowLayout->addWidget(new QLabel("Mount Point"));
    thisWindowLayout->addWidget(editMountPoint);

    thisWindowLayout->addWidget(lab_workgorup);
    thisWindowLayout->addWidget(editWorkGroup);

    thisWindowLayout->addWidget(checkLogin);

    thisWindowLayout->addWidget(lab_user);
    thisWindowLayout->addWidget(editLogin);
    thisWindowLayout->addWidget(lab_pass);
    thisWindowLayout->addWidget(editPassword);

    thisWindowLayout->addWidget(lab_adv);
    thisWindowLayout->addWidget(editAdvancedOptions);

    thisWindowLayout->addWidget(mount);

    thisWindowLayout->addWidget(buttonAdvanced);

    thisWindowLayout->addWidget(debug_text);

    connect(mount,          SIGNAL (released()),          this, SIGNAL (onMountButton()));
    connect(editServer,     SIGNAL(textChanged(QString)), this, SLOT(onChangedServer(QString)));
    connect(editMountPoint, SIGNAL(textChanged(QString)),  this, SIGNAL(changedServer(QString)));
    connect(checkLogin,     SIGNAL(stateChanged(int)),    this, SLOT(onUseLogin(int)));
    connect(comboItems,     SIGNAL(activated(QString)),   this, SLOT(onChangeLastItem(QString)));
    connect(buttonAdvanced, SIGNAL(released()),        this, SLOT(onAdvanced()));

    emit checkLogin->stateChanged(0);

    QWidget * wdg = new QWidget(this);
    wdg->setLayout(thisWindowLayout);
    setCentralWidget(wdg);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWorkGroup(QString workgroup)
{
    editWorkGroup->setText(workgroup);
}

void MainWindow::onAdvanced()
{
    advanced = !advanced;

    setAdvanced(advanced);
}

void MainWindow::setAdvanced(bool adv)
{
    advanced = adv;
    lab_workgorup->setVisible(advanced);
    editWorkGroup->setVisible(advanced);

    checkLogin->setVisible(advanced);
    lab_user->setVisible(advanced);
    editLogin->setVisible(advanced);
    lab_pass->setVisible(advanced);
    editPassword->setVisible(advanced);

    lab_adv->setVisible(advanced);
    editAdvancedOptions->setVisible(advanced);
    debug_text->setVisible(advanced);

    if (advanced)
    {
        buttonAdvanced->setText("Hide Advanced");
    }
    else
    {
        buttonAdvanced->setText("Show Advanced");
    }
}

QString MainWindow::getWorkGroup()
{
    return editWorkGroup->text();
}


void MainWindow::updateMountIndication(bool mounted)
{
    if (mounted)
    {
        mount->setText(WT_UNMOUNT);
    }
    else
    {
        mount->setText(WT_MOUNT);
    }
}

void MainWindow::debug(QString debug_text)
{
    this->debug_text->append(debug_text);
}


QString MainWindow::getMountPoint()
{
    return editMountPoint->text();
}

QString MainWindow::getServer()
{
    QString text(editServer->text());
    if (text.count("smb://") > 0)
    {
        text.replace("smb://", "\\\\");
        text.replace("/","\\");
    }
    return text;
}

void MainWindow::onChangedServer(QString text)
{
    text.replace('\\','_');
    text.replace("smb://", "__");
    text.replace('/','_');
    editMountPoint->setText("/mnt/samba/"+text);
}

void MainWindow::onUseLogin(int login)
{
    if (login)
    {
        editLogin->setEnabled(true);
        editPassword->setEnabled(true);
    }
    else
    {
        editLogin->setText("");
        editPassword->setText("");
        editLogin->setEnabled(false);
        editPassword->setEnabled(false);
    }
}

bool MainWindow::useLogin()
{
    return checkLogin->isChecked();
}

QString MainWindow::getUserName()
{
    return editLogin->text();
}

QString MainWindow::getUserPassword()
{
    return editPassword->text();
}

QString MainWindow::getAdvancedOptions()
{
    return editAdvancedOptions->text();
}

void MainWindow::updateLastItems(QStringList items)
{
    comboItems->clear();
    comboItems->addItems(items);
}

void MainWindow::onChangeLastItem(QString item)
{
    editServer->setText((item));
}
