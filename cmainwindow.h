#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget* parent = 0);
    ~CMainWindow();
private:
    Ui::CMainWindow* ui;
    bool isModified;
private slots:
    void createFile();
    void openFile();
    void saveFile();
    void runProgram();
    void exitProgram();
    void textModified();
};

#endif // CMAINWINDOW_H
