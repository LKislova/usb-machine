#include "mainwindow.h"

MainWindow::MainWindow() {
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);

    optionsWidget = new OptionsWidget(this, new QSettings());
    optionsWidget->hide();

    usbConnection = new UsbConnection();
    codeHighlighter = new CodeHighlighter(this);
    searchwidget = new SearchWidget(this);
    modelingWidget = new ModelingWidget();

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);

    connect(mainWidget,
            SIGNAL(wantToClose(QTextDocument*, QString)),
            this, SLOT(closeFile(QTextDocument*, QString)));
    connect(mainWidget,
            SIGNAL(currentChanged(int)),
            this, SLOT(bindCurrentText(int)));
    connect(mainWidget,
            SIGNAL(disconnectActionsFrom(CustomEditText*)),
            this,
            SLOT(disconnectWidget(CustomEditText*)));
    connect(searchwidget, SIGNAL(searchString(QString)),
            this, SLOT(findInCurrent(QString)) );
    connect(searchwidget, SIGNAL(replaceString(QString, QString)),
            this, SLOT(replaceInCurrent(QString, QString)));
    connect(searchwidget, SIGNAL(replaceAllString(QString, QString)),
            this, SLOT(replaceAllInCurrent(QString, QString)));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::closeFile(QTextDocument * doc, const QString path) {
    statusBar()->showMessage(tr("Пытаюьсь закрыть вкладку"), 2000);
    if(maybeSave(doc)) {
        mainWidget->closeTabSlot(path);
    } else {
        statusBar()->showMessage(tr("Не могу закрыть эту вкладку"), 2000);
    }
}

void MainWindow::newFile() {
    setCurrentFile("");
}

void MainWindow::open() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::save() {
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::about() {
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> is a student programm "
               "for work with machine "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void MainWindow::documentWasModified() {
    setWindowModified(mainWidget->getTextEdit()->document()->isModified());
}

void MainWindow::createActions() {

    newAct = new QAction(tr("&Новый"), this);
    newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Открыть..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    //openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Сохранить"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    //saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Сохранить &Как..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    //saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(tr("В&ыход"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    //exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    cutAct = new QAction(tr("Выре&зать"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    //cutAction->setStatusTip(tr("Cut the current selection's contents to the "
    //                        "clipboard"));
    cutAct->setEnabled(false);

    copyAct = new QAction(tr("&Копировать"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    //copyAction->setStatusTip(tr("Copy the current selection's contents to the "
    //                         "clipboard"));
    copyAct->setEnabled(false);

    pasteAct = new QAction(tr("&Вставить"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    //pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current "
    //                          "selection"));

    optionsAct = new QAction(tr("&Настройки"), this);
    connect(optionsAct, SIGNAL(triggered()), this, SLOT(showOptions()));

    findAct = new QAction(tr("&Поиск"), this);
    connect(findAct, SIGNAL(triggered()), this, SLOT(find()));

    replaceAct = new QAction(tr("&Замена"), this);
    connect(replaceAct, SIGNAL(triggered()), this, SLOT(replace()));

    compileAction = new QAction(tr("&Компилировать"), this);
    connect(compileAction, SIGNAL(triggered()), this, SLOT(compile()));

    runAction = new QAction(tr("&Запустить"), this);
    connect(runAction, SIGNAL(triggered()), this, SLOT(runCode()));

    modelAction = new QAction(tr("&Моделировать"), this);
    connect(modelAction, SIGNAL(triggered()), this, SLOT(onModeling()));

    manualCtrlAction = new QAction(tr("Ручсное &управление"), this);
    connect(manualCtrlAction, SIGNAL(triggered()), this, SLOT(manualCtrl()));

    machineOffAction = new QAction(tr("&Выключить машину"), this);
    connect(machineOffAction, SIGNAL(triggered()), this, SLOT(machineOff()));
}

void MainWindow::createMenus() {
    QMenuBar * bar = menuBar();
    fileMenu = bar->addMenu(tr("&Файл"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = bar->addMenu(tr("&Правка"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(findAct);
    editMenu->addAction(replaceAct);

    compilationMenu = bar->addMenu(tr("&Компиляция"));
    compilationMenu->addAction(compileAction);
    compilationMenu->addAction(runAction);
    compilationMenu->addAction(modelAction);

    optionsMenu = bar->addMenu(tr("&Настройки"));
    optionsMenu->addAction(optionsAct);

    toolsMenu = bar->addMenu(tr("&Оборудование"));
    toolsMenu->addAction(manualCtrlAction);
    toolsMenu->addAction(machineOffAction);

    bar->addSeparator();

    helpMenu = bar->addMenu(tr("&Помощь"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("Файл"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Правка"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Готов"));
}

void MainWindow::readSettings() {
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings() {
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

bool MainWindow::maybeSave() {
    return maybeSave(mainWidget->getTextEdit()->document());
}

bool MainWindow::maybeSave(QTextDocument * doc) {
    if (doc->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                     tr("Документ был изменён.\n"
                        "Вы хотите сохранить изменения?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Не могу открыть файл %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    setCurrentFile(fileName, in.readAll());
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    statusBar()->showMessage(tr("Файл загружен"), 2000);
}

bool MainWindow::saveFile(const QString &fileName) {
    return saveDocument(mainWidget->getTextEdit()->document(),
                        &fileName);
}

bool MainWindow::saveDocument(QTextDocument *doc, const QString * path){
    QFile file(*path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Не могу открыть файл %1:\n%2.")
                             .arg(*path)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << doc->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    doc->setModified(false);
    //setCurrentFile(*path);
    statusBar()->showMessage(tr("Файл сохранен в ") + *path, 2000);
    return true;

}

void MainWindow::bindCurrentText(int i){
    bindTextActions();
}

void MainWindow::bindTextActions(){
    CustomEditText* current = mainWidget->getTextEdit();
    QAction* cut = current->getCutAction();
    QAction* copy = current->getCopyAction();
    QAction* paste = current->getPasteAction();

    connect(cutAct, SIGNAL(triggered()), cut, SIGNAL(triggered()));
    connect(copyAct, SIGNAL(triggered()), copy, SIGNAL(triggered()));
    connect(pasteAct, SIGNAL(triggered()), paste, SIGNAL(triggered()));
    connect(current, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(current, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    cutAct->setEnabled(cut->isEnabled());
    copyAct->setEnabled(copy->isEnabled());

    connect(current->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));

    codeHighlighter->setDocument(current->document());
}

void MainWindow::setCurrentFile(const QString &fileName) {
    QString text("");
    setCurrentFile(fileName, text);
}

void MainWindow::setCurrentFile(const QString &fileName, const QString &text) {
    curFile = fileName;
    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    mainWidget->newTab(shownName, text)->document()->setModified(false);
    setWindowModified(false);

    setWindowFilePath(shownName);
    bindTextActions();
}

QString MainWindow::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::disconnectWidget(CustomEditText* textEdit) {
    QAction* cut = textEdit->getCutAction();
    QAction* copy = textEdit->getCopyAction();
    QAction* paste = textEdit->getPasteAction();

    disconnect(cutAct, SIGNAL(triggered()), cut, SIGNAL(triggered()));
    disconnect(copyAct, SIGNAL(triggered()), copy, SIGNAL(triggered()));
    disconnect(pasteAct, SIGNAL(triggered()), paste, SIGNAL(triggered()));
    disconnect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    disconnect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));


    disconnect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
}

void MainWindow::showOptions(){
    optionsWidget->show();
}

void MainWindow::find(){
    this->searchwidget->show();

}

void MainWindow::replace(){
    this->searchwidget->show();

}
void MainWindow::replaceAll(){
    this->searchwidget->show();
}

void MainWindow::manualCtrl(){

}

void MainWindow::machineOff(){

}

void MainWindow::compile() {
    compilator = new Compilator(this->mainWidget->getCurrentPath().toStdString().c_str());
    compilator->compile();
    //this->thread()->currentThread()->sleep(5);
    statusBar()->showMessage(tr("Компилирую"), 2000);
}

void MainWindow::runCode() {
    compile();
    onFinishCompilation();
}

void MainWindow::onFinishCompilation() {
    mainWidget->clearTables();
    lines_t *lines = compilator->getLines();
    foreach(line_t* i, *lines){
        mainWidget->addLine(i);
    }
    statusBar()->showMessage(tr("Компилированы %1").arg(compilator->getLines()->size()), 2000);
}

void MainWindow::onModeling() {
    compile();
    lines_t *lines = compilator->getLines();
    statusBar()->showMessage(tr("Компилированы %1").arg(lines->size()), 2000);
    usbConnection->print_info();
    if (lines->size() != 0) {
        modelingWidget->plotLine(lines);
        modelingWidget->show();
    }
}


void MainWindow::findInCurrent(QString regexp){
    CustomEditText* textEdit = mainWidget->getTextEdit();
    textEdit->find(regexp);
    textEdit->show();
}
void MainWindow::replaceInCurrent(QString regexp, QString text){
    CustomEditText* textEdit = mainWidget->getTextEdit();
    textEdit->insertPlainText(text);
    textEdit->find(regexp);
    textEdit->show();
}
void MainWindow::replaceAllInCurrent(QString regexp, QString text){
    CustomEditText* textEdit = mainWidget->getTextEdit();
    while(textEdit->find(regexp)) {
        textEdit->insertPlainText(text);
    };

    textEdit->show();
}
