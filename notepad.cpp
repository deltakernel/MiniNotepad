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
}

void Notepad::closeEvent(QCloseEvent *event)
{
    if (isChanged)
    {
        QString text = "";
        if (!file->fileName().isEmpty())
        {
            QFileInfo fileInfo(file->fileName());
            text = "<h2>You want to save the changes in " + fileInfo.fileName() + "?</h2>";
        }
        else
        {
            text = "<h2>You want to save the changes?</h2>";
        }
        
        int resp = QMessageBox::question(this, "", text, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        switch (resp)
        {
        case QMessageBox::Yes:
            save();
            QMainWindow::closeEvent(event);
            break;
        case QMessageBox::No:
            event->accept();
            QMainWindow::closeEvent(event);
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            QMainWindow::closeEvent(event);
            break;
        }
        
    }
 
    
}

// void Notepad::windowClosing()
// {

// }

void Notepad::message_status()
{
    QString message;
    if (file->fileName() != "")
    {
        QFileInfo fileInfo(file->fileName());
        message = fileInfo.fileName();
    }
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
    if(!textEdit->toPlainText().isEmpty() || isChanged) {
        if(QMessageBox::Yes == QMessageBox::question(this, "", "<h2><div>Deseja Salvar as alterações</div><div>feitas no Documento</div></h2>")) {
            save();
        } 
    } 
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
