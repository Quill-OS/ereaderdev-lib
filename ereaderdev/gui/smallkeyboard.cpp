#include "gui/smallkeyboard.h"
#include "ui_smallkeyboard.h"

#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

smallkeyboard::smallkeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smallkeyboard)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    lowerCaseButtons();
    lowerCase = true;
    special = false;
}

smallkeyboard::~smallkeyboard()
{
    delete ui;
}

// No idea to do it better
void smallkeyboard::start(QObject* textEditorToAdd) {
    qDebug() << "Called start keyboard";
    if (QLineEdit* textEditor = dynamic_cast<QLineEdit*>(textEditorToAdd)) {
        // Handle QLineEdit
        if(textEditor == NULL) {
            qDebug() << "Oh no, keyboard is going to die";
        }
        mainString = textEditor->text();
        textEditor->setSelection(0,0);
        textEditor->setCursorPosition(textEditor->text().length());
        ui->Button_Cancel->setIcon(QIcon(":/icons/close.png"));
        // No idea icons had problems
        ui->Button_Confirm->setIcon(QIcon(":/icons/confirm.svg"));

        lineEdit = textEditor;
        isLineEdit = true;
    }
    else if (QTextEdit* textEditor = dynamic_cast<QTextEdit*>(textEditorToAdd)) {
        // Handle QTextEdit
        if(textEditor == NULL) {
            qDebug() << "Oh no, keyboard is going to die";
        }
        mainString = textEditor->toPlainText();
        textEditor->textCursor().clearSelection();

        textEdit = textEditor;
        isTextEdit = true;

        ui->Button_Confirm->setIcon(QIcon(":/keyboard/send.svg"));
    }
    else {
        // Invalid widget type
        qDebug() << "Invalid widget type";
    }
}

void smallkeyboard::dontExit() {
    dontExitBool = true;
}

void smallkeyboard::updateString(QString new_string)
{
    if(isLineEdit) {
        int cursorPosition = lineEdit->cursorPosition();
        lineEdit->setText(lineEdit->text().replace(cursorCharacter, "")); // This resets the position

        lineEdit->setText(lineEdit->text().insert(cursorPosition, new_string));
        lineEdit->setText(lineEdit->text().insert(cursorPosition + 1, cursorCharacter));
        lineEdit->setCursorPosition(cursorPosition + 1);
    } else if(isTextEdit) {
        textEdit->textCursor().insertText(new_string);
    }
}

void smallkeyboard::lowerCaseButtons()
{
    ui->Button_q->setText("q");
    ui->Button_w->setText("w");
    ui->Button_e->setText("e");
    ui->Button_r->setText("r");
    ui->Button_t->setText("t");
    ui->Button_y->setText("y");
    ui->Button_u->setText("u");
    ui->Button_i->setText("i");
    ui->Button_o->setText("o");
    ui->Button_p->setText("p");

    ui->Button_a->setText("a");
    ui->Button_s->setText("s");
    ui->Button_d->setText("d");
    ui->Button_f->setText("f");
    ui->Button_g->setText("g");
    ui->Button_h->setText("h");
    ui->Button_j->setText("j");
    ui->Button_k->setText("k");
    ui->Button_l->setText("l");

    ui->Button_z->setText("z");
    ui->Button_x->setText("x");
    ui->Button_c->setText("c");
    ui->Button_v->setText("v");
    ui->Button_b->setText("b");
    ui->Button_n->setText("n");
    ui->Button_m->setText("m");
}

void smallkeyboard::upperCaseButtons()
{
    ui->Button_q->setText("Q");
    ui->Button_w->setText("W");
    ui->Button_e->setText("E");
    ui->Button_r->setText("R");
    ui->Button_t->setText("T");
    ui->Button_y->setText("Y");
    ui->Button_u->setText("U");
    ui->Button_i->setText("I");
    ui->Button_o->setText("O");
    ui->Button_p->setText("P");

    ui->Button_a->setText("A");
    ui->Button_s->setText("S");
    ui->Button_d->setText("D");
    ui->Button_f->setText("F");
    ui->Button_g->setText("G");
    ui->Button_h->setText("H");
    ui->Button_j->setText("J");
    ui->Button_k->setText("K");
    ui->Button_l->setText("L");

    ui->Button_z->setText("Z");
    ui->Button_x->setText("X");
    ui->Button_c->setText("C");
    ui->Button_v->setText("V");
    ui->Button_b->setText("B");
    ui->Button_n->setText("N");
    ui->Button_m->setText("M");
}

void smallkeyboard::on_Button_Caps_clicked()
{
    // this can be changed in the future for more characters
    if(special == false)
    {
        if(lowerCase == true)
        {
            lowerCase = false;
            upperCaseButtons();
            ui->Button_Caps->setStyleSheet("font-weight: bold");
        } else {
            lowerCase = true;
            lowerCaseButtons();
            ui->Button_Caps->setStyleSheet("font-weight: normal");
        }
    }
}

void smallkeyboard::on_Button_space_clicked()
{
    updateString(" ");
}

void smallkeyboard::on_Button_backspace_clicked()
{
    if(isLineEdit) {
        int cursorPosition = lineEdit->cursorPosition();
        lineEdit->setText(lineEdit->text().replace(cursorCharacter, ""));

        lineEdit->setText(lineEdit->text().remove(cursorPosition - 1, 1));
        lineEdit->setText(lineEdit->text().insert(cursorPosition - 1, cursorCharacter));
        lineEdit->setCursorPosition(cursorPosition - 1);
    } else if(isTextEdit) {
        int cursorPosition = textEdit->textCursor().position();
        textEdit->setText(textEdit->toPlainText().remove(cursorPosition - 1, 1));
        textEdit->textCursor().setPosition(cursorPosition - 1);
    }

}

void smallkeyboard::on_Button_Special_clicked()
{
    if(special == false)
    {
        special = true;
        ui->Button_Special->setStyleSheet("font-weight: bold");
        ui->Button_q->setText("1");
        ui->Button_w->setText("2");
        ui->Button_e->setText("3");
        ui->Button_r->setText("4");
        ui->Button_t->setText("5");
        ui->Button_y->setText("6");
        ui->Button_u->setText("7");
        ui->Button_i->setText("8");
        ui->Button_o->setText("9");
        ui->Button_p->setText("0");
        if(isLineEdit) {
            ui->Button_Cancel->setIcon(QIcon(":/icons/left.svg"));
            ui->Button_Confirm->setIcon(QIcon(":/icons/right.svg"));
        } else if(isTextEdit) {
            ui->Button_Cancel->setIcon(QIcon(":/icons/close.png"));
            ui->Button_Confirm->setIcon(QIcon(":/keyboard/send.svg"));
        }
        ui->Button_v->setText(":");
        ui->Button_m->setText("/");
    } else {
        special = false;
        ui->Button_Special->setStyleSheet("font-weight: normal");
        if(isLineEdit) {
            ui->Button_Cancel->setIcon(QIcon(":/icons/close.png"));
            ui->Button_Confirm->setIcon(QIcon("://icons/confirm.svg"));
        } else if(isTextEdit) {
            ui->Button_Cancel->setIcon(QIcon(":/icons/close.png"));
            ui->Button_Confirm->setIcon(QIcon(":/keyboard/send.svg"));
        }
        if(lowerCase == true)
        {
            lowerCaseButtons();
        } else {
            upperCaseButtons();
        }
    }
}

void smallkeyboard::on_Button_Cancel_clicked()
{
    if(isTextEdit) {
        emit closeButton();
        return void();
    }
    if(special == true) {
        qDebug() << "Cursor backwards";
        if(isLineEdit) {
            int cursorPosition = lineEdit->cursorPosition() - 1;
            if(cursorPosition < 0) {
                return void();
            }
            lineEdit->setText(lineEdit->text().replace(cursorCharacter, ""));

            lineEdit->setText(lineEdit->text().insert(cursorPosition, cursorCharacter));
            lineEdit->setCursorPosition(cursorPosition);
        }
    } else {
        if(isLineEdit) {
            lineEdit->setText(mainString);
            lineEdit->setText(lineEdit->text().replace(cursorCharacter, ""));
            QString newText = mainString;
            while(newText.endsWith(" ") == true) {
                newText.chop(1);
            }
            lineEdit->setText(newText);
        }
        if(dontExitBool == false) {
            this->close();
        }
    }
}


void smallkeyboard::on_Button_Confirm_clicked()
{
    if(isTextEdit) {
        // Sending enter...
        qDebug() << "Sending enter";
        QKeyEvent* enter = new QKeyEvent (QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier);
        QCoreApplication::postEvent(textEdit, (QEvent *)enter);
        return void();
    }
    if(special == true) {
        if(isLineEdit) {
            int cursorPosition = lineEdit->cursorPosition() + 1;
            if(cursorPosition < 0) {
                return void();
            }
            lineEdit->setText(lineEdit->text().replace(cursorCharacter, ""));


            lineEdit->setText(lineEdit->text().insert(cursorPosition, cursorCharacter));
            lineEdit->setCursorPosition(cursorPosition);
        }
    } else {
        if(isLineEdit) {
            lineEdit->setText(lineEdit->text().replace(cursorCharacter, ""));
            QString newText = lineEdit->text();
            while(newText.endsWith(" ") == true) {
                newText.chop(1);
            }
            lineEdit->setText(newText);
        }
        if(dontExitBool == false) {
            this->close();
        }
    }
}

///

void smallkeyboard::on_Button_q_clicked()
{
    updateString(ui->Button_q->text());
}

void smallkeyboard::on_Button_w_clicked()
{
    updateString(ui->Button_w->text());
}

void smallkeyboard::on_Button_e_clicked()
{
    updateString(ui->Button_e->text());
}

void smallkeyboard::on_Button_r_clicked()
{
    updateString(ui->Button_r->text());
}

void smallkeyboard::on_Button_t_clicked()
{
    updateString(ui->Button_t->text());
}

void smallkeyboard::on_Button_y_clicked()
{
    updateString(ui->Button_y->text());
}

void smallkeyboard::on_Button_u_clicked()
{
    updateString(ui->Button_u->text());
}

void smallkeyboard::on_Button_i_clicked()
{
    updateString(ui->Button_i->text());
}

void smallkeyboard::on_Button_o_clicked()
{
    updateString(ui->Button_o->text());
}

void smallkeyboard::on_Button_p_clicked()
{
    updateString(ui->Button_p->text());
}

///

void smallkeyboard::on_Button_a_clicked()
{
    updateString(ui->Button_a->text());
}

void smallkeyboard::on_Button_s_clicked()
{
    updateString(ui->Button_s->text());
}

void smallkeyboard::on_Button_d_clicked()
{
    updateString(ui->Button_d->text());
}

void smallkeyboard::on_Button_f_clicked()
{
    updateString(ui->Button_f->text());
}

void smallkeyboard::on_Button_g_clicked()
{
    updateString(ui->Button_g->text());
}

void smallkeyboard::on_Button_h_clicked()
{
    updateString(ui->Button_h->text());
}

void smallkeyboard::on_Button_j_clicked()
{
    updateString(ui->Button_j->text());
}

void smallkeyboard::on_Button_k_clicked()
{
    updateString(ui->Button_k->text());
}

void smallkeyboard::on_Button_l_clicked()
{
    updateString(ui->Button_l->text());
}

///

void smallkeyboard::on_Button_z_clicked()
{
    updateString(ui->Button_z->text());
}

void smallkeyboard::on_Button_x_clicked()
{
    updateString(ui->Button_x->text());
}

void smallkeyboard::on_Button_c_clicked()
{
    updateString(ui->Button_c->text());
}

void smallkeyboard::on_Button_v_clicked()
{
    updateString(ui->Button_v->text());
}

void smallkeyboard::on_Button_b_clicked()
{
    updateString(ui->Button_b->text());
}

void smallkeyboard::on_Button_n_clicked()
{
    updateString(ui->Button_n->text());
}

void smallkeyboard::on_Button_m_clicked()
{
    updateString(ui->Button_m->text());
}

void smallkeyboard::on_Button_dot_clicked()
{
    updateString(ui->Button_dot->text());
}

