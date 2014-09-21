#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QtWidgets>
#include <QLineEdit>


class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);
void init();
    QPushButton *searchButton;
    QPushButton *replaceButton;
    QPushButton *replaceAllButton;
    QLineEdit *searchLine;
    QLineEdit *replaceAllLine;
    QLabel* searchLabel;
    QLabel* replaceLabel;
    QHBoxLayout* searchLayout;
    QHBoxLayout* replaceLayout;
    QHBoxLayout* replaceAllLayout;
    QBoxLayout* mainLayout;
signals:
    void searchString(QString regexp);
    void replaceString(QString regexp, QString text);
    void replaceAllString(QString regexp, QString text);
public slots:
    void search();
    void replace();
    void replaceAll();

};

#endif // SEARCHWIDGET_H
