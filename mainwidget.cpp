#include "mainwidget.h"

MainWidget::MainWidget(QWidget * parent) : QWidget(parent) {
    this->setParent(parent);
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTab(int)));
    connect(tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(disconnectWidgets(int)));

    mainSplitter = new QSplitter(Qt::Vertical, this);
    supportSplitter = new QSplitter(Qt::Horizontal, this);
    mainLayout = new QVBoxLayout(this);
    createVarTable();
    createMainVarTable();

    supportSplitter->addWidget(tabWidget);
    supportSplitter->addWidget(varTable);

    mainSplitter->addWidget(supportSplitter);

    mainLayout->addWidget(mainSplitter);
    setLayout(mainLayout);

    mainSplitter->addWidget(mainVarTable);

    mainSplitter->setChildrenCollapsible(false);
    supportSplitter->setChildrenCollapsible(false);
}

void MainWidget::createMainVarTable(){
    mainVarTable = new QTableWidget(this);
    QStringList header;
    header << tr("t") << tr("X") << tr("Y") << tr("Z") << tr("F") << tr("S");
    mainVarTable->setColumnCount(header.count()); //t, x, y, z, f, s
    mainVarTable->setHorizontalHeaderLabels(header);
}

void MainWidget::createVarTable(){
    varTable = new QTableWidget(this);
    QStringList header;
    header << tr("Name") << tr("Value");
    varTable->setColumnCount(header.count()); //name, value
    varTable->setHorizontalHeaderLabels(header);
}


void MainWidget::closeTab(int index) {
    QTextDocument * doc =
            ((QPlainTextEdit*)tabWidget->widget(index))->document();
    QString path = pathesList[index];

    emit wantToClose(doc, path);
}

CustomEditText* MainWidget::getTextEdit() {
    return (CustomEditText*)tabWidget->currentWidget();
}

QString MainWidget::getCurrentPath() {
    return pathesList[tabWidget->currentIndex()];
}

CustomEditText* MainWidget::newTab(const QString &name) {
    return newTab(name, tr(""));
}

CustomEditText* MainWidget::setCurrentTabName(const QString &name) {
    int currentIndex = tabWidget->currentIndex();
    pathesList.replace(currentIndex, name);
    tabWidget->setTabText(currentIndex, name);
    return (CustomEditText* ) tabWidget->currentWidget();
}

QString MainWidget::incrementCounterInFileName(const QString &name) {
    QRegExp regexp("^(\\D*)(\\d*)$");
    int pos = -1;
    if ((pos = regexp.lastIndexIn(name.section('.', 0, 0))) != -1) {
        int n;
        if (regexp.cap(2).isEmpty()){
            n = 0;
        } else {
            n = regexp.cap(2).toInt();
        }
        return tr("%1%2.%3")
                .arg(regexp.cap(1))
                .arg(QString::number(n + 1))
                .arg(name.section('.', 1, -1));
    }
    return name + "1";
}

CustomEditText* MainWidget::newTab(
        const QString &name, const QString &contant) {
    if(pathesList.contains(name)){
        return newTab(incrementCounterInFileName(name), contant);
    } else {
        pathesList.append(name);
    }
    CustomEditText* text = new CustomEditText(this);
    text->setPlainText(contant);

    tabWidget->addTab(text, name);
    tabWidget->setCurrentWidget(text);
    tabWidget->adjustSize();
    return text;
}

void MainWidget::closeTabSlot(QString name) {
    int index = pathesList.indexOf(name);
    int tabsCount = tabWidget->count();
    if (index != -1 && tabsCount > index){
        QWidget * w = tabWidget->widget(index);
        if (w != NULL){
            w->deleteLater();
        }
        pathesList.removeAt(index);

        if (tabsCount == 1){
            newTab("untitled.txt");
        }
        tabWidget->removeTab(index);
    }
}

void MainWidget::disconnectWidgets(int index) {
    int count = tabWidget->count();
    for (int i = 0; i < count; i++){
        emit disconnectActionsFrom((CustomEditText*)tabWidget->widget(i));
    }

    emit currentChanged(index);
}

void MainWidget::clearTables() {
    mainVarTable->setRowCount(0);
}

void MainWidget::addLine(line_t *line) {
    int new_index = mainVarTable->rowCount();
    mainVarTable->insertRow(new_index);
    double x = get_var("x", line);
    double y = get_var("y", line);
    double z = get_var("z", line);
    double f = get_var("f", line);
    double s = get_var("s", line);
    //t, x, y, z, f, s
    QTableWidgetItem *newItemT = new QTableWidgetItem(tr("%1").arg(new_index));
    QTableWidgetItem *newItemX = new QTableWidgetItem(tr("%1").arg(x));
    QTableWidgetItem *newItemY = new QTableWidgetItem(tr("%1").arg(y));
    QTableWidgetItem *newItemZ = new QTableWidgetItem(tr("%1").arg(z));
    QTableWidgetItem *newItemF = new QTableWidgetItem(tr("%1").arg(f));
    QTableWidgetItem *newItemS = new QTableWidgetItem(tr("%1").arg(s));
    mainVarTable->setSortingEnabled(false);
    mainVarTable->setItem(new_index, 0, newItemT);
    mainVarTable->setItem(new_index, 1, newItemX);
    mainVarTable->setItem(new_index, 2, newItemY);
    mainVarTable->setItem(new_index, 3, newItemZ);
    mainVarTable->setItem(new_index, 4, newItemF);
    mainVarTable->setItem(new_index, 5, newItemS);
}
