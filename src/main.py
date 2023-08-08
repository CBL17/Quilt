from PyQt6.QtWidgets import QApplication, QMainWindow, QPushButton, QLineEdit, QVBoxLayout, QWidget, QHBoxLayout
from PyQt6.QtCore import QFile, QTextStream, QIODevice, Qt
import sys

import ctypes

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Testing.. >:)")
        self.setGeometry(100, 100, 400, 300)
        
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)

        self.input_line = QLineEdit()
        self.input_line.setToolTip("write here plz")
        
        self.button = QPushButton("Click Me!")
        self.button.setFixedHeight(25)
        self.button.setFixedWidth(100)
        
        main_layout = QHBoxLayout(central_widget)
        main_layout.addWidget(self.input_line, stretch=1)
        main_layout.addWidget(self.button, stretch=1)
        
        main_layout.setAlignment(Qt.AlignmentFlag.AlignBottom)
        
        self.button.clicked.connect(self.on_button_click)
        self.input_line.returnPressed.connect(self.on_input_return_pressed)
        

    def load_stylesheet(self):
        style_file = QFile("style.qss")
        if style_file.open(QIODevice.OpenModeFlag.ReadOnly | QIODevice.OpenModeFlag.Text):
            stream = QTextStream(style_file)
            self.setStyleSheet(stream.readAll())
            style_file.close()
            

    def on_button_click(self):
        print(self.input_line.text())
        
        
    def on_input_return_pressed(self):
        print(self.input_line.text())
        self.input_line.clear()


if __name__ == "__main__":
    
    # lib = ctypes.CDLL("C:\\Users\\Charles\\Desktop\\CS Projects\\Python\\cancer\\src\\main.dll")
    # test = lib.main()
        
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
