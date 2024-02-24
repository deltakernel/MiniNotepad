#include <QApplication>
#include "notepad.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Notepad notepad;
    

    QMap<int, QString> commands ;
    
    for (int i = 0; i < argc; i++)
    {
        commands[i] = argv[i];
    }

    int index = commands.key("-d");//args.indexOf("-o");

    if(index  < (argc-1)){
        qDebug() << "args[" << index << "]= " << commands[index+1];
        notepad.show();
    } else {
        qDebug() << "Digite o comando corretamente\no especificador " << commands[index] << "deve receber um argumento"; 
        notepad.close();
    }

    return app.exec();
}
