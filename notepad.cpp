#include "notepad.h"

Notepad::Notepad()
    : file(new (QFile))
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

        connect(openAction, &QAction::triggered, this, &Notepad::open);
        connect(saveAction, &QAction::triggered, this, &Notepad::save);
        connect(textEdit, &QTextEdit::textChanged, this, &Notepad::on_textEdit_changed);

    }

    Notepad::~Notepad()
    {
        close();
    }

    void Notepad::save()
    {
        if(file->fileName().isEmpty()){
            QString fileName = QFileDialog::getSaveFileName(this, "Save Text File", "", "Text Files (*.txt);;All Files (*)");
            if(fileName != "") {
                file->setFileName(fileName);
                if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QTextStream out(file);
                    out << textEdit->toPlainText();
                    file->close();
                    isChanged=false;
                }
            }
            if(file->isOpen()) file->close();
        } else {
            if(file->isOpen()) file->close();
            if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(file);
                out << textEdit->toPlainText();
                file->close();
                status->showMessage("");
                isChanged=false;
            }
        }
        if(!isChanged) status->showMessage(file->fileName());
    }



    void Notepad::on_textEdit_changed()
    {
        isChanged = true;
        status->showMessage(file->fileName() + "*");
    }

void Notepad::open() 
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt);;All Files (*)");
        // Open file case chosse file in explorer end file not is current file.
        if(fileName != "" || file->fileName() != fileName) {
            file->setFileName(fileName);
            if(file->open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(file);
                textEdit->setText(in.readAll());
                isChanged=false;
            }
        }
        if(!isChanged) status->showMessage(file->fileName());
 
    }
