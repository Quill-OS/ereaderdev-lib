#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class smallkeyboard;
}

class smallkeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit smallkeyboard(QWidget *parent = nullptr);
    ~smallkeyboard();

    // Line edit mode is without touch support, everything manually, big cursor
    QLineEdit* lineEdit;
    bool isLineEdit = false;

    // touch support, a bit better
    QTextEdit* textEdit;
    bool isTextEdit = false;

    void start(QObject* textEditorToAdd);

    QString mainString;
    QString editedString;
    QChar cursorCharacter = '|';

    void dontExit();
    bool dontExitBool = false;

signals:
    void closeButton();

private slots:
    void updateString(QString new_string);
    void lowerCaseButtons();
    void upperCaseButtons();
    void on_Button_Caps_clicked();
    void on_Button_space_clicked();
    void on_Button_backspace_clicked();
    void on_Button_Special_clicked();
    void on_Button_Cancel_clicked();
    void on_Button_Confirm_clicked();

    void on_Button_q_clicked();
    void on_Button_w_clicked();
    void on_Button_e_clicked();
    void on_Button_r_clicked();
    void on_Button_t_clicked();
    void on_Button_y_clicked();
    void on_Button_u_clicked();
    void on_Button_i_clicked();
    void on_Button_o_clicked();
    void on_Button_p_clicked();

    void on_Button_a_clicked();
    void on_Button_s_clicked();
    void on_Button_d_clicked();
    void on_Button_f_clicked();
    void on_Button_g_clicked();
    void on_Button_h_clicked();
    void on_Button_j_clicked();
    void on_Button_k_clicked();
    void on_Button_l_clicked();

    void on_Button_z_clicked();
    void on_Button_x_clicked();
    void on_Button_c_clicked();
    void on_Button_v_clicked();
    void on_Button_b_clicked();
    void on_Button_n_clicked();
    void on_Button_m_clicked();

    void on_Button_dot_clicked();

private:
    Ui::smallkeyboard *ui;
    bool lowerCase = true;
    bool special = false;
};

#endif // KEYBOARD_H
