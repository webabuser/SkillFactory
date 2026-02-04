#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QCloseEvent>
#include "usermanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void loadUsers();
    void onUserClicked();  // Слот для клика по пользователю

    void on_actionBlockUser_triggered();
    void on_actionUnBlockUser_triggered();

    void on_actionDeleteUser_triggered();

    void on_actionRefreshUsers_triggered();

    void onSearchButtonClicked();
    void onSearchReturnPressed();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    UserManager *usermanager;
    QLineEdit *searchLineEdit;

    void showUserMessages(quint8 user_id);
    void setupSearch();
    bool confirmExit();
};

#endif // MAINWINDOW_H
