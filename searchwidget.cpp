#include "searchwidget.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent,Qt::Window)
  //Qt::Window|Qt::WindowMaximizeButtonHint//
{

   searchButton = new QPushButton(tr("Найти"));
   replaceButton =new QPushButton(tr("Заменить"));
   replaceAllButton =new QPushButton(tr("Заменить все"));
   searchLine =new QLineEdit();
   replaceAllLine =new QLineEdit();
   searchLabel =new QLabel(tr("Найти"));
   replaceLabel =new QLabel(tr("Заменить на"));
   searchLayout =new QHBoxLayout();
   replaceLayout =new QHBoxLayout();
   mainLayout =new QVBoxLayout();
   replaceAllLayout =new QHBoxLayout();

   searchLayout->addSpacing(0);
   searchLayout->addWidget(searchLabel);
   searchLayout->addSpacing(0);
   searchLayout->addWidget(searchLine);
   searchLayout->addSpacing(0);
   searchLayout->addWidget(searchButton);
   searchLayout->addSpacing(0);

   replaceLayout->addSpacing(0);
   replaceLayout->addWidget(replaceLabel);
   replaceLayout->addSpacing(0);
   replaceLayout->addWidget(replaceAllLine);
   replaceLayout->addSpacing(0);
   replaceLayout->addWidget(replaceButton);
   replaceLayout->addSpacing(0);


   replaceAllLayout->addStretch(1);
   replaceAllLayout->addWidget(replaceAllButton);
   replaceAllLayout->addSpacing(0);

   mainLayout->addLayout(searchLayout);
   mainLayout->addLayout(replaceLayout);
   mainLayout->addLayout(replaceAllLayout);
   setLayout(mainLayout);
   connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
   connect(replaceButton, SIGNAL(clicked()), this, SLOT(replace()));
   connect(replaceAllButton, SIGNAL(clicked()), this, SLOT(replaceAll()));

}

void SearchWidget::search(){
    emit searchString(searchLine->text());
}
void SearchWidget::replace(){
    emit replaceString(searchLine->text(), replaceAllLine->text());
}
void SearchWidget::replaceAll(){
    emit replaceAllString(searchLine->text(), replaceAllLine->text());
}
