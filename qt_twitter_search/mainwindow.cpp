#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QtNetwork>
#include <QtNetworkAuth>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    auth(new QOAuth1),
    in_progress(false)
{
    ui->setupUi(this);

    auth->setTemporaryCredentialsUrl(QUrl("https://api.twitter.com/oauth/request_token"));
    auth->setAuthorizationUrl(QUrl("https://api.twitter.com/oauth/authenticate"));
    auth->setTokenCredentialsUrl(QUrl("https://api.twitter.com/oauth/access_token"));

    auth->setClientIdentifier(QString("04mlIREq8buD2iTFZ7lt2uycV"));
    auth->setClientSharedSecret(QString("WZqxe6ahinqoBGGMjQrKb3gzHRzUajIlD4X9aoLYNvdSIy9j7M"));
    auth->setToken("2458993579-qI6nt2TdTbNGsXXBdzW6bjwxvD3WelZE97c0LqO");
    auth->setTokenSecret("gcxxoNAzMvCC6Rmh5nUk5NM3kGgWFL4gtiMc5VdQndUMq");

    connect(ui->searchBtn, SIGNAL(released()), this, SLOT(search()));

    connect(auth, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(new_reply(QNetworkReply*)));
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this,  SLOT(enableBtn(QString)));
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->searchBtn,  SLOT(click()));
    setHeader();
}

void MainWindow::setHeader()
{
    QStringList header;
    header << "User" <<  "Tweet Text" << "Date";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0, this->width() / 4);
    ui->tableWidget->setColumnWidth(1, this->width() / 2);
    ui->tableWidget->setColumnWidth(2, this->width() / 5);
}

void MainWindow::search()
{
    in_progress = true;
    enableBtn(ui->lineEdit->text());
    QUrl url("https://api.twitter.com/1.1/search/tweets.json");

    QUrlQuery query;
    query.addQueryItem("q", ui->lineEdit->text());
    url.setQuery(query);

    auth->get(url);
}

void MainWindow::enableBtn(QString)
{
    if (in_progress) {
        ui->searchBtn->setEnabled(false);
        this->setCursor(QCursor(Qt::CursorShape::WaitCursor));
        return;
    }

    bool is_text_empty = ui->lineEdit->text().size() == 0;

    ui->searchBtn->setEnabled(!is_text_empty);
    this->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
}

void MainWindow::new_reply(QNetworkReply* data)
{
    in_progress = false;
    enableBtn(ui->lineEdit->text());
    ui->tableWidget->clear();
    setHeader();

    if (data->error() != QNetworkReply::NoError) {
        qWarning() << "Error: " << data->errorString();
        QMessageBox::warning(this, "Request error", data->errorString());
        return;
    }

    auto response_data = data->readAll();
    QJsonDocument jsonResp = QJsonDocument::fromJson(response_data);
    auto statuses = jsonResp.object()["statuses"].toArray();

    int total_items = statuses.size();

    if (total_items == 0) {
        QMessageBox::warning(this, "Not Found", "Tweets not found. Try to change search text");
    }

    ui->tableWidget->setRowCount(total_items);

    for (int i = 0; i < total_items; ++i) {
        auto item = statuses[i];
        auto text = item.toObject()["text"].toString();
        auto created_at = item.toObject()["created_at"].toString();
        auto userName = item.toObject()["user"].toObject()["name"].toString();
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(userName));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(text));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(created_at));

    }

    data->close();
    data->deleteLater();
}

MainWindow::~MainWindow()
{
    delete ui;
}
