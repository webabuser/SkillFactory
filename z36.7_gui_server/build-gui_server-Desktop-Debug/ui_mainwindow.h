/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBlockUser;
    QAction *actionDeleteUser;
    QAction *actionUnBlockUser;
    QAction *actionRefreshUsers;
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_users;
    QListWidget *tw_users;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_messages;
    QTextBrowser *tw_messages;
    QMenuBar *menuBar;
    QMenu *menuMain;
    QMenu *menuActions;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(642, 617);
        actionBlockUser = new QAction(MainWindow);
        actionBlockUser->setObjectName(QStringLiteral("actionBlockUser"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionBlockUser->setIcon(icon);
        actionDeleteUser = new QAction(MainWindow);
        actionDeleteUser->setObjectName(QStringLiteral("actionDeleteUser"));
        QIcon icon1;
        iconThemeName = QStringLiteral("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionDeleteUser->setIcon(icon1);
        actionUnBlockUser = new QAction(MainWindow);
        actionUnBlockUser->setObjectName(QStringLiteral("actionUnBlockUser"));
        QIcon icon2;
        iconThemeName = QStringLiteral("dialog-ok");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionUnBlockUser->setIcon(icon2);
        actionRefreshUsers = new QAction(MainWindow);
        actionRefreshUsers->setObjectName(QStringLiteral("actionRefreshUsers"));
        QIcon icon3;
        iconThemeName = QStringLiteral("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionRefreshUsers->setIcon(icon3);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 20, 20, 20);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_users = new QLabel(centralWidget);
        label_users->setObjectName(QStringLiteral("label_users"));

        verticalLayout_3->addWidget(label_users);

        tw_users = new QListWidget(centralWidget);
        tw_users->setObjectName(QStringLiteral("tw_users"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tw_users->sizePolicy().hasHeightForWidth());
        tw_users->setSizePolicy(sizePolicy);
        tw_users->setMaximumSize(QSize(300, 16777215));
        tw_users->setMouseTracking(true);

        verticalLayout_3->addWidget(tw_users);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_messages = new QLabel(centralWidget);
        label_messages->setObjectName(QStringLiteral("label_messages"));

        verticalLayout_4->addWidget(label_messages);

        tw_messages = new QTextBrowser(centralWidget);
        tw_messages->setObjectName(QStringLiteral("tw_messages"));
        sizePolicy.setHeightForWidth(tw_messages->sizePolicy().hasHeightForWidth());
        tw_messages->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(tw_messages);


        horizontalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 642, 22));
        menuMain = new QMenu(menuBar);
        menuMain->setObjectName(QStringLiteral("menuMain"));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMain->menuAction());
        menuBar->addAction(menuActions->menuAction());
        menuBar->addAction(menu->menuAction());
        menuMain->addAction(actionExit);
        menuActions->addAction(actionBlockUser);
        menuActions->addAction(actionUnBlockUser);
        menuActions->addAction(actionDeleteUser);
        menuActions->addAction(actionRefreshUsers);
        menu->addAction(actionAbout);
        mainToolBar->addAction(actionRefreshUsers);
        mainToolBar->addAction(actionBlockUser);
        mainToolBar->addAction(actionUnBlockUser);
        mainToolBar->addAction(actionDeleteUser);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionBlockUser->setText(QApplication::translate("MainWindow", "BlockUser", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionBlockUser->setToolTip(QApplication::translate("MainWindow", "Block User", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionBlockUser->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionDeleteUser->setText(QApplication::translate("MainWindow", "DeleteUser", Q_NULLPTR));
        actionUnBlockUser->setText(QApplication::translate("MainWindow", "UnBlockUser", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionUnBlockUser->setToolTip(QApplication::translate("MainWindow", "UnBlock User", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRefreshUsers->setText(QApplication::translate("MainWindow", "RefreshUsers", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        label_users->setText(QApplication::translate("MainWindow", "Users:", Q_NULLPTR));
        label_messages->setText(QApplication::translate("MainWindow", "Messages:", Q_NULLPTR));
        menuMain->setTitle(QApplication::translate("MainWindow", "Main", Q_NULLPTR));
        menuActions->setTitle(QApplication::translate("MainWindow", "Actions", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
