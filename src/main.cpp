#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setGeometry(100, 100, 200, 200);
    window.setWindowTitle("Pacman");

    QPushButton button("Hello World", &window);
    button.setGeometry(10, 10, 180, 30);

    window.show();

    return app.exec();
}