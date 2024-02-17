#include "notepad.h"

Notepad::Notepad() 
    : menuBar(new QMenuBar(this))
    , fileMenu(new QMenu("File", this))
    , openAction(new QAction("Open", this))
    , saveAction(new QAction("Save", this))
    , file(new (QFile))
    {
        textEdit = new QTextEdit(this);
        setCentralWidget(textEdit);

        fileMenu->addAction(openAction);
        fileMenu->addAction(saveAction);
        menuBar->addMenu(fileMenu);
        setMenuBar(menuBar);

        connect(openAction, &QAction::triggered, this, &Notepad::open);
        connect(saveAction, &QAction::triggered, this, &Notepad::save);
    }

    void Notepad::save()
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Text File", "", "Text Files (*.txt);;All Files (*)");
        file->setFileName(fileName);
        if (file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(file);
            out << textEdit->toPlainText();
            file->close();
        }
    }

void Notepad::open() 
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt);;All Files (*)");
        if(fileName != "" || file->fileName() != fileName) {
            file->setFileName(fileName);
            if(file->open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(file);
                textEdit->setText(in.readAll());
            }
        } 
    }