#include <QDebug>
#include <QMessageBox>
#include <QWidgetAction>
#include <QImageReader>
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    usermanager(new UserManager(this)),
    searchLineEdit(nullptr)
{
    ui->setupUi(this);

    if(usermanager->connectToDatabase()){
        loadUsers();
    }

    // Подключаем клик по элементу списка
    connect(ui->tw_users, &QListWidget::itemClicked,
            this, &MainWindow::onUserClicked);




    setupSearch();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadUsers()
{
    ui->tw_users->clear();

    // Создаем цветные иконки
    QPixmap blockedIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical).pixmap(20, 20);
   // QPixmap activeIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation).pixmap(20, 20);
    QPixmap deletedIcon = QApplication::style()->standardIcon(QStyle::SP_TrashIcon).pixmap(20, 20);

    QList<User> users = usermanager->getAllUsers();

    for(const User& user : users){
        QString userinfo = QString("%1 (%2 %3)").arg(user.login_)
                                                .arg(user.name_)
                                                .arg(user.surname_);

        QListWidgetItem *item = new QListWidgetItem(userinfo);

        // Устанавливаем иконку в зависимости от статуса
        if (user.status_ == "blocked") {
            item->setIcon(QIcon(blockedIcon));
        } else if (user.status_ =="deleted") {
            item->setIcon(QIcon(deletedIcon));
        }

        // Сохраняем ID и статус
        item->setData(Qt::UserRole, user.id_); // Сохраняем ID в данных
        item->setData(Qt::UserRole+1, user.status_);

        ui->tw_users->addItem(item);
    }

    ui->statusBar->showMessage(QString("Пользователей: %1").arg(users.size()));
}



void MainWindow::onUserClicked()
{
    // Получаем выбранный элемент
    QListWidgetItem *item = ui->tw_users->currentItem();
    if (!item) return;

    // Получаем ID пользователя из данных элемента
    quint8 user_id = item->data(Qt::UserRole).toUInt();
    showUserMessages(user_id);
}

void MainWindow::showUserMessages(quint8 user_id)
{
    QList<Message> messages = usermanager->getUserMessages(user_id);
    ui->tw_messages->clear();

    if (messages.isEmpty()) {
        ui->tw_messages->append("Сообщений нет");
        return;
    }

    for(const Message& msg : messages){
        QString msgInfo = QString("[%1] %2 -> %3  %4")
                .arg(msg.created_)
                .arg(msg.sender_login_)
                .arg(msg.receiver_login_)
                .arg(msg.text_);

        ui->tw_messages->append(msgInfo);
    }

    ui->statusBar->showMessage(
        QString("Сообщений пользователя: %1").arg(messages.size()),
        5000
                );
}



void MainWindow::on_actionBlockUser_triggered()
{
    QListWidgetItem *item = ui->tw_users->currentItem();
    if(!item){
        QMessageBox::warning(this, "Error", "Select user for blocking");
        return;
    }

    quint8 user_id = item->data(Qt::UserRole).toUInt();
    QString login = item->text().split(" ")[0];// получаем логин из текста

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  QString("Block user %1?").arg(login),
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        bool success = usermanager->blockUser(user_id, "Blocking user via GUI");
        if(success){
            ui->statusBar->showMessage(QString("User %1 blocked").arg(login), 3000);
            loadUsers();
        }
    }
}

void MainWindow::on_actionUnBlockUser_triggered()
{
    QListWidgetItem *item = ui->tw_users->currentItem();
    if(!item){
        QMessageBox::warning(this, "Error", "Select user for unblocking");
        return;
    }

    quint8 user_id = item->data(Qt::UserRole).toUInt();
    QString login = item->text().split(" ")[0];// получаем логин из текста

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  QString("UnBlock user %1?").arg(login),
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        bool success = usermanager->unblockUser(user_id, "UnBlocking user via GUI");
        if(success){
            ui->statusBar->showMessage(QString("User %1 unblocked").arg(login), 3000);
            loadUsers();
        }
    }
}

void MainWindow::on_actionDeleteUser_triggered()
{
    QListWidgetItem *item = ui->tw_users->currentItem();

    if(!item){
        QMessageBox::warning(this, "Error", "Select user for delete");
        return;
    }

    qint8 user_id = item->data(Qt::UserRole).toUInt();
    QString login = item->text().split(" ").at(0);

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                   QString("Delete user %1?").arg(login),
                                   QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        bool success = usermanager->deleteUser(user_id, "Deleting user via GUI");

        if(success){
            ui->statusBar->showMessage(QString("User %1 deleted").arg(login), 3000);
            loadUsers();
        }
    }
}

void MainWindow::on_actionRefreshUsers_triggered()
{
    loadUsers();
}

void MainWindow::onSearchButtonClicked()
{
    bool visible = searchLineEdit->isVisible();
    searchLineEdit->setVisible(!visible);
    if(!visible) searchLineEdit->setFocus();
}

void MainWindow::onSearchReturnPressed()
{
    QString searchtext = searchLineEdit->text();
    if(searchtext.isEmpty()) return;

    QTextDocument *doc = ui->tw_messages->document();

    //Сначала сброс предыдущей подсветки
    QTextCursor resetCursor(doc);
    resetCursor.beginEditBlock();

    QTextCharFormat defaultFormat;
    defaultFormat.setBackground(Qt::transparent);

    resetCursor.movePosition(QTextCursor::Start);
    while(!resetCursor.atEnd()){
        resetCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        resetCursor.mergeCharFormat(defaultFormat);
    }

    resetCursor.endEditBlock();

    //Новая подстветка
    QTextCursor cursor(doc);
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::cyan);

    cursor = doc->find(searchtext);

    while(!cursor.isNull()){
        cursor.mergeCharFormat(highlightFormat);
        //ui->tw_messages->viewport()->update(); //принудительная перерисовка
        //QCoreApplication::processEvents();    // for debuging
        cursor = doc->find(searchtext, cursor);
    }

}

void MainWindow::setupSearch()
{
    QAction *actionSearch = new QAction(QIcon(":/icons/icons/search_35.png"), "Search", this);
    ui->mainToolBar->addAction(actionSearch);

    searchLineEdit = new QLineEdit();
    searchLineEdit->setPlaceholderText("Search in messages...");
    searchLineEdit->setClearButtonEnabled(true);
    searchLineEdit->setMaximumWidth(200);
    searchLineEdit->setVisible(false);
qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();
    //добавляем строку поиска в верхний угол
    ui->verticalLayout_4->insertWidget(0, searchLineEdit);

    connect(actionSearch, &QAction::triggered, this, &MainWindow::onSearchButtonClicked);

    //Подсветка при нажатии Enter
    connect(searchLineEdit, &QLineEdit::returnPressed, this, &MainWindow::onSearchReturnPressed);

}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("О программе");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("<h3>GUI Server v1.0</h3>"
                   "<p>Админ-панель для управления пользователями и сообщениями.</p>"
                   "<p><b>Авторы:</b> Вития А.В.</p>"
                   "<p><b>Сборка:</b> " __DATE__ "</p>");
    msgBox.setIconPixmap(QPixmap(":/icons/icons/fingerprint_35.png").scaled(35, 35));

    msgBox.exec();

}

bool MainWindow::confirmExit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                                    QMessageBox::Yes | QMessageBox::No);
    return (reply == QMessageBox::Yes);
}


void MainWindow::on_actionExit_triggered()
{
    if(confirmExit()) QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(confirmExit()) event->accept();
    else event->ignore();
}
