#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(destroyed()), this, SLOT(exitProgram()));
    connect(ui->codeEdit, SIGNAL(textChanged()), this, SLOT(textModified()));
    connect(ui->actionOpen_file, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionCreate_file, SIGNAL(triggered()), this, SLOT(createFile()));
    connect(ui->actionSave_file, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(exitProgram()));
    connect(ui->action_Run, SIGNAL(triggered()), this, SLOT(runProgram()));

    isModified = false;
    mw_syntaxHighlighter = new CSyntaxHighlighter(ui->codeEdit->document());
}

CMainWindow::~CMainWindow()
{
    delete mw_syntaxHighlighter;
    delete ui;
}

void CMainWindow::textModified()
{
    isModified = true;
}

void CMainWindow::openFile()
{
    if(isModified)
    {
        QMessageBox closeMsg;
        closeMsg.setIcon(QMessageBox::Question);
        closeMsg.setWindowTitle("The document has been modified");
        closeMsg.setText("You have unsaved changes.");
        closeMsg.setInformativeText("Do you want to save them?");
        closeMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        closeMsg.setDefaultButton(QMessageBox::Yes);
        int ret = closeMsg.exec();

        switch(ret)
        {
            case QMessageBox::Yes:
            {
                emit saveFile();
                break;
            }
            case QMessageBox::No:
                break;
        }

    }

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Turing Machine code (*.tm)"));
    QStringList fileNames;

    if(dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        QString fileName = fileNames.at(0);
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            QString strData = stream.readAll();
            ui->codeEdit->insertPlainText(strData);
            file.close();
        }
        else
        {
            //TODO: icon for this messageBox
            QMessageBox errorMsg(QMessageBox::Critical, tr("Error while opening file"), tr("File not found"));
            errorMsg.exec();
        }
    }
}

void CMainWindow::createFile()
{
    //TODO: icon for this messageBox
    if(isModified)
    {
        QMessageBox saveMsg;
        saveMsg.setIcon(QMessageBox::Question);
        saveMsg.setWindowTitle("The document has been modified");
        saveMsg.setText("Do you want to save your changes?");
        saveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        saveMsg.setDefaultButton(QMessageBox::Save);
        int ret = saveMsg.exec();

        switch(ret)
        {
            case QMessageBox::Save:
            {
                emit saveFile();
                break;
            }
            case QMessageBox::Discard:
            {
                ui->codeEdit->clear();
                break;
            }
        }
    }
    else
        ui->codeEdit->clear();
}

void CMainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "Turing Machine code (*.tm)");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << ui->codeEdit->toPlainText();
        file.close();
    }
    else
    {
        if(fileName != "")
        {
            //TODO: icon for this messageBox
            QMessageBox errorMsg(QMessageBox::Critical, tr("Error while saving file"), tr("Unable to open file"));
            errorMsg.exec();
        }
    }

    isModified = false;
}

void CMainWindow::exitProgram()
{
    //TODO: set icon for this messageBox
    if(isModified)
    {
        QMessageBox saveMsg;
        saveMsg.setIcon(QMessageBox::Question);
        saveMsg.setWindowTitle("The document has been modified");
        saveMsg.setText("Do you want to save your changes?");
        saveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        saveMsg.setDefaultButton(QMessageBox::Save);
        int ret = saveMsg.exec();

        switch(ret)
        {
            case QMessageBox::Save:
            {
                emit saveFile();
                break;
            }
        }
    }

    QMessageBox exitMsg;
    exitMsg.setIcon(QMessageBox::Question);
    exitMsg.setWindowTitle("Confirmation needed");
    exitMsg.setText("Do you really want to exit?");
    exitMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    exitMsg.setDefaultButton(QMessageBox::No);
    int ret = exitMsg.exec();

    switch(ret)
    {
        case QMessageBox::Yes:
            exit(0);
        case QMessageBox::No:
            break;
    }
}

void CMainWindow::runProgram()
{

}
