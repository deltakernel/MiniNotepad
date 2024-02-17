#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>

class Notepad : public QMainWindow
{
public:
    Notepad();

private slots:
    void open();
    void save();

private:
    QTextEdit *textEdit;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
};