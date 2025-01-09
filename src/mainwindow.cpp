#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    wordCountTarget = 0;

    wordCountLabel = new QLabel("Words: 0");
    targetLabel = new QLabel("Target: 0");
    statusBar()->addPermanentWidget(wordCountLabel);
    statusBar()->addPermanentWidget(targetLabel);
    
    // Connect text change signal to word count update
    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::updateWordCount);


    createActions();
    createMenus();
    createToolBars();
    
    setWindowTitle(tr("I Control Fussi"));
    showFullScreen();
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}


void MainWindow::updateWordCount()
{
    QString text = textEdit->toPlainText();
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int wordCount = words.size();
    
    wordCountLabel->setText(QString("Words: %1").arg(wordCount));
    
    // Update color based on target
    if (wordCountTarget > 0) {
        if (wordCount >= wordCountTarget) {
            wordCountLabel->setStyleSheet("color: green;");

            showNormal();
             QMessageBox::information(this, "You can now save! :) ", 
            QString("Good boy you wrote %1 words")
            .arg(wordCountTarget));
        } else {
            showFullScreen();
            
            wordCountLabel->setStyleSheet("color: red;");
        }
    } else {
        wordCountLabel->setStyleSheet("");
    }
}

void MainWindow::setWordCountTarget()
{
    bool ok;
    int target = QInputDialog::getInt(this, tr("Set Word Count Target"),
                                    tr("Target word count:"), wordCountTarget,
                                    0, 1000000, 1, &ok);
    if (ok) {
        wordCountTarget = target;  // Changed from setWordCountTarget = target
        targetLabel->setText(QString("Target: %1").arg(target));
        updateWordCount(); // Update colors
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
 QString text = textEdit->toPlainText();
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int wordCount = words.size();
    



if (wordCountTarget == 0 || wordCount < wordCountTarget) {
            event->ignore(); // Prevent the window from closing
        QMessageBox::information(this, "Cannot Close", 
            QString("You need exactly %1 words to close. Current count: %2")
            .arg(wordCountTarget)
            .arg(wordCount));
    } else {
            if (textEdit->document()->isModified()) {
        event->ignore();
         maybeSave();

        return;
    }
        event->accept(); // Allow the window to close
    }
}

void MainWindow::createActions()
{
    // File actions
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, [this]() { saveFile(); });

    saveAsAct = new QAction(tr("Save &As..."), this);
    connect(saveAsAct, &QAction::triggered, this, [this]() { saveAsFile(); });

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    connect(printAct, &QAction::triggered, this, &MainWindow::print);

    // Remove or comment out exit action
    // exitAct = new QAction(tr("E&xit"), this);
    // exitAct->setShortcuts(QKeySequence::Quit);
    // connect(exitAct, &QAction::triggered, this, &QWidget::close);

    // Edit actions
    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    // Format actions
    fontAct = new QAction(tr("&Font..."), this);
    connect(fontAct, &QAction::triggered, this, &MainWindow::selectFont);

    // Help actions
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

        setTargetAct = new QAction(tr("How many words"), this);
        connect(setTargetAct, &QAction::triggered, this, &MainWindow::setWordCountTarget);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    // Remove exit action from menu
    // fileMenu->addSeparator();
    // fileMenu->addAction(exitAct);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    QMenu *formatMenu = menuBar()->addMenu(tr("F&ormat"));
    formatMenu->addAction(fontAct);

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(printAct);

    QToolBar *editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    QToolBar *wordCountToolBar = addToolBar(tr("Word Count"));
    wordCountToolBar->addAction(setTargetAct);
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::openFile()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}

bool MainWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        return saveAsFile();
    } else {
        return saveFile(currentFile);
    }
}

bool MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
}

void MainWindow::cut()
{
    textEdit->cut();
}

void MainWindow::copy()
{
    textEdit->copy();
}

void MainWindow::paste()
{
    textEdit->paste();
}

void MainWindow::undo()
{
    textEdit->undo();
}

void MainWindow::redo()
{
    textEdit->redo();
}

void MainWindow::selectFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);
    if (ok) {
        textEdit->setFont(font);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
        tr("Help you stay focused"));
}

bool MainWindow::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Qt Text Editor"),
        tr("The document has been modified.\n"
           "Do you want to save your changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
        return saveFile();
    else if (ret == QMessageBox::Cancel)
        return false;
    
    return true;
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Qt Text Editor"),
            tr("Cannot read file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Qt Text Editor"),
            tr("Cannot write file %1:\n%2.")
            .arg(fileName)
            .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = currentFile;
    if (shownName.isEmpty())
        shownName = "untitled.txt";
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("I Control Fussi")));
}
