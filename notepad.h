#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>
#include <QStatusBar>

class Notepad : public QMainWindow
{
public:
    Notepad();
    ~Notepad();

    void message_statusbar(QString fileName);

private slots:
    void open();
    void save();
    void on_textEdit_changed();

private:
    QTextEdit *textEdit;
    QFile     *file;

    bool isChanged;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *openAction;
    QAction *saveAction;
    QStatusBar *status;
};