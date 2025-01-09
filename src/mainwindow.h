#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QEvent>
#include <QtGui/QCloseEvent>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QLabel>          // Add this for QLabel
#include <QInputDialog>    // Add this for QInputDialog
#include <QRegularExpression>  // Add this for modern regex support

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void openFile();
    bool saveFile();
    bool saveAsFile();
    void print();
    void cut();
    void copy();
    void paste();
    void undo();
    void redo();
    void selectFont();
    void about();
    void updateWordCount();  // Function to update word count
    void setWordCountTarget();

private:

    void createActions();
    void createMenus();
    void createToolBars();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    bool isTargetMet() const;
    void updateWindowState();
    QLabel *wordCountLabel;  // For displaying current word count
    QLabel *targetLabel;     // For displaying target
    int wordCountTarget;     // To store the target word count

 // Function to set target

    QTextEdit *textEdit;
    QString currentFile;

    
    // Menu actions
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *fontAct;
    QAction *aboutAct;
    QAction *setTargetAct;
};

#endif // MAINWINDOW_H