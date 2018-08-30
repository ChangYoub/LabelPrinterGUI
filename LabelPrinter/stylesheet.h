#ifndef STYLESHEET_H
#define STYLESHEET_H

#define DEFAULT_QSS \
"QWidget {"\
    "background: transparent;"\
"}"

#define SYSTEM_MENU_QSS \
"QWidget {"\
    "background-color: #0747a6;"\
    "border: none;"\
    "border-left: 1px solid #5c7790;"\
    "border-right: 1px solid #5c7790;"\
    "border-top: 1px solid #5c7790;"\
    "border-bottom: 1px solid transparent;"\
"}"

#define LABEL_LOGO_TEXT_QSS   \
"QLabel{"\
    "border: none;"\
    "color: white;"\
    "font-weight: bold;"\
    "font-style: italic;"\
    "font-size: 9pt;"\
    "font-family: Arial;"\
"}"

#define LABEL_TITLE_TEXT_QSS   \
"QLabel{"\
    "border: none;"\
    "color: white;"\
    "font-size: 12px;"\
    "font-family: Arial;"\
"}"

#define SYSTEM_MENU_BAR_QSS \
"QWidget {"\
    "background-color: #0747a6;"\
    "border: none;"\
    "border-left: 1px solid #5c7790;"\
    "border-right: 1px solid #5c7790;"\
"}"

#define SYSTEM_MENU_BTN_QSS \
"QPushButton {"\
    "border: none;"\
    "background-color: #0747a6;"\
"}"\
"QPushButton:hover {"\
    "background-color: #0078d7;"\
"}"

#define SYSTEM_MENU_QUIT_BTN_QSS    \
"QPushButton {"\
    "border: none;" \
    "background-color: #0747a6;"\
"}"\
"QPushButton:hover {"\
    "background-color: #e81123;"\
"}"

#define LABEL_LOGO_ICON_QSS \
"QLabel{"\
    "image: url(\":/Resources/Icon/program_icon.png\");"\
    "border: none;"\
"}"

#define STACK_WIDGET_QSS    \
"QStackedWidget {"\
    "border-bottom: 1px solid #5c7790;"\
    "border-left: 1px solid #5c7790;"\
    "border-right: 1px solid #5c7790;"\
    "background-color: white;"\
"}"

#define BTN_AREA_WIDGET_QSS \
"QWidget {"\
    "background-color: #f4f5f7;"\
    "border-bottom: 1px solid #CCCCCC;"\
    "border-left: 1px solid #5c7790;"\
    "border-right: 1px solid #5c7790;"\
"}"

#define PRINTER_BTN_ICON_QSS    \
"QPushButton{"\
    "image: url(\":/Resources/Icon/printer_icon.png\");"\
    "padding-bottom: 5px;"\
    "border: none;"\
    "border-bottom: 2px solid #f4f5f7;"\
    "background: transparent;"\
    "text-align: bottom;"\
    "color: #707070;"\
    "font-size: 8pt;"\
"}" \
"QPushButton:hover {"\
    "background-color: #dbdbdb;"\
    "border-bottom: 2px solid #dbdbdb;"\
"}"\
"QPushButton:pressed {"\
    "image: url(\":/Resources/Icon/printer_hover_icon.png\");"\
    "border-bottom: 2px solid #0747a6;"\
    "color: #268ffb;"\
"}"

#define TABLE_QSS   \
"QTableWidget {"\
    "background-color: white;"\
    "border: none;"\
    "border-top: 1px solid #CCCCCC;"\
    "border-right: 1px solid #CCCCCC;"\
"}"\
"QTableView::item {"\
    "selection-background-color: white;"\
    "color: #707070;"\
    "border: none;"\
    "border-bottom: 1px solid #CCCCCC;"\
    "border-left: 1px solid #CCCCCC;"\
"}"\
"QTableView::item:hover {"\
    "background-color: #BEE6FD;"\
    "color: white;"\
"}"\
"QLineEdit {"\
    "border: none;"\
    "background-color: white;"\
    "selection-background-color: #75b9ff;"\
    "selection-color: white;"\
    "qproperty-alignment: AlignCenter"\
"}"

#define MENU_BAR_QSS    \
"QMenuBar{"\
    "font-size: 13px;"\
    "border: none;"\
    "color: white;"\
"}"\
"QMenuBar::item:selected {"\
    "border: 1px solid #26A0DA;"\
    "background-color: #0E5CB2;"\
"}"

#define MENU_ITEM_QSS   \
"QMenu {"\
    "border: 1px solid #999999;"\
    "background-color: #F0F0F0;"\
    "padding: 2px 2px 2px 2px;"\
"}"\
"QMenu::item {"\
    "background-color: #F0F0F0;"\
    "color: black;"\
    "padding: 2px 20px 2px 20px;"\
"}"\
"QMenu::item:selected {"\
    "border: 1px solid #26A0DA;"\
    "background-color: #C0DDE8;"\
"}"

#define TIP_LABEL_TEXT_QSS  \
"QLabel {"\
    "font-family: Arial;"\
    "color: #707070;"\
"}"

#define CORRECT_DIALOG_QSS  \
"QDialog {"\
    "background-color: white;"\
"}"

#define CORRECT_DIALOG_WIDGET_QSS   \
"QWidget {"\
    "border: 1px solid #5c7790;"\
    " border-top: none;"\
"}"

#define CORRECT_DIALOG_LABEL_QSS    \
"QLabel{"\
    "background: transparent;"\
    "color: #707070;"\
    "font-size: 12px;"\
    "font-family: Arial;"\
"}"

#define POS_SPIN_BOX_QSS  \
"QSpinBox {"\
    "background-color: white;"\
    "border: 1px solid #d0d1d4;"\
    "border-radius: 2px;"\
    "padding-left: 14px;"\
    "font-size: 12px;"\
    "color: #707070;"\
    "selection-background-color: #C0DDE8;"\
    "selection-color: #707070;"\
"}"\
"QSpinBox::down-button {"\
    "border: none;"\
"}"\
"QSpinBox::down-arrow{"\
    "image: url(\":/Resources/Icon/down_arrow_icon.png\");"\
    "width: 10px;"\
    "height: 10px;"\
"}"\
"QSpinBox::down-arrow:hover {"\
    "image: url(\":/Resources/Icon/down_arrow_hover_icon.png\");"\
"}"\
    "QSpinBox::up-button{"\
    "border: none;"\
"}"\
"QSpinBox::up-arrow{"\
    "image: url(\":/Resources/Icon/up_arrow_icon.png\");"\
    "width: 10px;"\
    "height: 10px;"\
"}"\
"QSpinBox::up-arrow:hover{"\
    "image: url(\":/Resources/Icon/up_arrow_hover_icon.png\");"\
"}"

#define DIALOG_SAVE_BTN_QSS \
"QPushButton {"\
    "font-weight: bold;"\
    "border:1px solid #707070;"\
    "background-color: #dddddd;"\
"}"\
"QPushButton:hover {"\
    "background-color: #BEE6FD;"\
    "border:1px solid #3C7FB1;"\
"}"

#endif // STYLESHEET_H
