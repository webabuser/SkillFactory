#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    if(dbPtr)
       m_dbPtr = dbPtr;
    else
       m_dbPtr = make_shared<Database>();

    ui->loginWidget->setDatabase(m_dbPtr);
    ui->registerWiget->setDatabase(m_dbPtr);


    connect(ui->loginWidget, &LoginForm::registerRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->loginWidget, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->loginWidget, &LoginForm::rejected, this, &StartScreen::onRejectRequested);

    connect(ui->registerWiget, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->registerWiget, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->registerWiget, &RegistrationForm::rejected, this, &StartScreen::onRejectRequested);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::onLoggedIn(uint userId, QString userName)
{
    m_userId = userId;
    m_userName = userName;
    accept();
}

void StartScreen::onRejectRequested()
{
    reject();
}

QString StartScreen::userName() const
{
    return m_userName;
}

std::shared_ptr<Database> StartScreen::getDatabase() const
{
    return m_dbPtr;
}

int StartScreen::userId() const
{
    return m_userId;
}
