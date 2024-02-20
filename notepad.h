#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>
#include <QStatusBar>
#include <QMessageBox>
#include <QCloseEvent>

class Notepad : public QMainWindow
{
    Q_OBJECT
public:
    Notepad(QMainWindow *parent = nullptr);
    ~Notepad();

protected:
    void closeEvent(QCloseEvent *event) override;

// signals:
//     void windowClosing();

private slots:
    void open();
    void save();
    void message_status();
    void on_textEdit_changed();
    

private:
    QTextEdit *textEdit;
    QFile     *file;

    bool isChanged;

    QMenuBar   *menuBar;
    QMenu      *fileMenu;
    QAction    *openAction;
    QAction    *saveAction;
    QStatusBar *status;
};