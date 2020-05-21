#!/usr/bin/python3
 
print("Hello, World!")

import sys
import re


#一个python的文件有两种使用的方法，第一是直接作为脚本执行，第二是import到其他的python脚本中被调用（模块重用）执行。
# 因此if __name__ == 'main': 的作用就是控制这两种情况执行代码的过程，在if __name__ == 'main': 下的代码只有在第一种情况下
# （即文件作为脚本直接执行）才会被执行，而import到其他脚本中是不会被执行的。
if __name__=="__main__":
 f= open("hi.txt","w+")
 li=["hello\n","hi\n"]
 f.writelines(li)
 f.close()                                                                                                                                                                                                                                                                                                                                                                                               
 print("mind end!")


#!/usr/bin/env python
# -*- coding:utf-8 -*-
 
import mainwindow
 
import sys
from PyQt5.QtWidgets import QApplication
from PyQt5.QtWidgets import QMainWindow
 
 
def button_clicked_event():
    global mainwindow_ui
    name = mainwindow_ui.name_lineEdit.text()
    pwd = mainwindow_ui.password_lineEdit.text()
    msg_value = name + " " + pwd
    print(msg_value)
    mainwindow_ui.msg_plainTextEdit.setPlainText(str(msg_value))
 
 
#################################################
if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainwindow_ui = mainwindow.Ui_MainWindow()
    qMainWindow = QMainWindow()
    mainwindow_ui.setupUi(qMainWindow)
    mainwindow_ui.login_btn.clicked.connect(button_clicked_event)
    qMainWindow.show()
    
    sys.exit(app.exec_())
 