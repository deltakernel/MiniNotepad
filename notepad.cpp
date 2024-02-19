#include "notepad.h"

Notepad::Notepad(QMainWindow *parent)
    : QMainWindow{parent}
    , file(new(QFile))
    , menuBar(new QMenuBar(this))
    , status(new QStatusBar(this))
    , fileMenu(new QMenu("File", this))
    , openAction(new QAction("Open", this))
    , saveAction(new QAction("Save", this))
    , isChanged(false)
{
    setGeometry(600, 100, 600, 800);
    textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);
    setStatusBar(status);

    openAction->setShortcut(Qt::CTRL | Qt::Key_O);
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);

    connect(openAction, &QAction::triggered, this, &Notepad::open);
    connect(saveAction, &QAction::triggered, this, &Notepad::save);
    connect(textEdit, &QTextEdit::textChanged, this, &Notepad::on_textEdit_changed);
}

Notepad::~Notepad()
{
    if (isChanged)
    {
        QString text = "";
        if (file->fileName() != "")
        {
            QString fileName = file->fileName();
            text = "Do you want save changed text in " + fileName.left(fileName.lastIndexOf(QChar('\\')));
            if (QMessageBox::Yes == QMessageBox::question(this, "", text))
                save();
        }
    }
    close();
}

void Notepad::message_status()
{
    QString message;
    if (file->fileName() != "")
    {
        QFileInfo fileInfo(file->fileName());
        message = fileInfo.fileName();
    }
    //QString word = (isChanged)? "*" : "";
    //(isChanged)?  word="*" :  word="";
    status->showMessage(message + QString((isChanged)? "*" : ""));
}

void Notepad::save()
{
    if (file->fileName().isEmpty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Text File", "", "Text Files (*.txt);;All Files (*)");
        if (fileName != "")
        {
            file->setFileName(fileName);
            if (file->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(file);
                out << textEdit->toPlainText();
                file->close();
                isChanged = false;
            }
        }
        if (file->isOpen())
            file->close();
    }
    else
    {
        if (file->isOpen())
            file->close();
        if (file->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(file);
            out << textEdit->toPlainText();
            file->close();
            status->showMessage("");
            isChanged = false;
        }
    }
    if (!isChanged) 
        message_status();
}

void Notepad::on_textEdit_changed()
{
    isChanged = true;
    Notepad::message_status();
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt);;All Files (*)");
    // Open file case chosse file in explorer end file not is current file.
    if (fileName != "" || file->fileName() != fileName)
    {
        file->setFileName(fileName);
        if (file->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(file);
            textEdit->setText(in.readAll());
            isChanged = false;
        }
    }
    if (!isChanged)
        message_status();
}
