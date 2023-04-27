#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QGridLayout>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *widget = new QWidget();
    widget->resize(400, 300);

// Create a QGridLayout to arrange the blocks in a grid
    QGridLayout *layout = new QGridLayout(widget);

// Set the number of rows and columns in the grid
    int numRows = 10;
    int numCols = 10;
    QWidget* arr[10][10];
// Create the blocks and add them to the layout
    for(int row = 0; row < numRows; ++row) {
        for(int col = 0; col < numCols; ++col) {
            // Create a new block widget
            QWidget *block = new QWidget();
            arr[row][col] = block;
            // Set the block's background color
            block->setStyleSheet("background-color: gray;");

            // Add the block to the grid at the current row and column
            layout->addWidget(block, row, col);
        }
    }


// Set the layout for the widget
    widget->setLayout(layout);

// Show the widget
    widget->show();


    return app.exec();
}