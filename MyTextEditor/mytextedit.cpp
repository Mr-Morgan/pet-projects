#include "mytextedit.h"

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{
    m = new QMenu (this);
    my_action = createStandardContextMenu()->actions();

    QAction *actionUndo = new QAction (QIcon(":/icons/icons/undo.png"), "&Undo");
    QAction *actionRedo = new QAction (QIcon(":/icons/icons/redo.png"), "&Redo");

    my_action[0] = actionUndo;
    my_action[1] = actionRedo;

    connect(my_action[0], SIGNAL(triggered()), this, SLOT(on_actionUndo_triggered()));
    connect(my_action[1], SIGNAL(triggered()), this, SLOT(on_actionRedo_triggered()));
    connect(this,SIGNAL(textChanged()),SLOT(on_textEdit_textChanged()));
}//MyTextEdit()

void MyTextEdit::pushChanges(QStack<Changes> &st, Changes ch)
{
    if (st.count() == STACK_MAX_SIZE) st.pop_front();
    st.push(ch);
}//void pushChanges(QStack<Changes> &st, Changes &ch)

void MyTextEdit::saveTextFormat()
{
    f = textCursor().charFormat();
}//void saveTextFormat()

void MyTextEdit::setFormatNeedsInserted(bool needs)
{
    fni = needs;
}//void setFormatNeedsInserted(bool needs)

void MyTextEdit::setTextFormat(QTextCharFormat f)
{
    textCursor().setCharFormat(f);
}//void setTextFormat(QTextCharFormat f)

QTextCharFormat MyTextEdit::getTextFormat()
{
    return textCursor().charFormat();
}//QTextCharFormat getTextFormat()

bool MyTextEdit::getFNI()
{
    return fni;
}//bool getFNI()

void MyTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
    m->exec(my_action, e->globalPos());
}//void contextMenuEvent(QContextMenuEvent *e)

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Backspace)
        key = BDKey::Backspace;
    else if (e->key() == Qt::Key_Delete)
        key = BDKey::Delete;
}//void keyReleaseEvent(QKeyEvent *event)

void MyTextEdit::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::MouseButton::LeftButton && fni) {
        textCursor().setCharFormat(f);
        fni = false;
        emit charFormatChanged(false);
    }//if (e->button() == Qt::MouseButton::LeftButton && fni)
}//void mouseReleaseEvent(QMouseEvent *e)

#define CUR_POS textCursor().position()
#define LIO(ch) text.lastIndexOf(ch, CUR_POS-1)
#define TLEN text.length()
#define TWCL twc.length()
#define UTOP undo.top()
#define RTOP redo.top()

void MyTextEdit::on_textEdit_textChanged()
{
    QString text = toPlainText();
    if (undoRedoFlag) {
        undoRedoFlag = false;
    } else {
        if (TLEN != TWCL) {
            if (undo.count()) {
                int32_t space = (LIO(' ') > LIO('\n'))? LIO(' ') : LIO('\n');
                if (TLEN > TWCL) {
                    if (space == -1 || space != (CUR_POS - 1))
                        UTOP.data += text.mid(CUR_POS - (TLEN - TWCL), TLEN - TWCL);
                    else pushChanges(undo, Changes(space, text.mid(space, TLEN - TWCL))); //
                } else if (TLEN < TWCL ) {
                    if (twc[CUR_POS] == ' ' || twc[CUR_POS] == '\n' || !UTOP.del)
                        pushChanges(undo, Changes(CUR_POS, twc.mid(CUR_POS, TWCL - TLEN), true));
                    else {
                        if (key == BDKey::Backspace) {
                            UTOP.data.prepend(twc.mid(CUR_POS, TWCL - TLEN));
                            UTOP.pos = CUR_POS;
                        } else if (key == BDKey::Delete)
                            UTOP.data += twc.mid(CUR_POS, TWCL - TLEN);
                    }//if (twc[CUR_POS] == ' ' || twc[CUR_POS] == '\n' || !UTOP.del)
                }//if (TLEN < TWCL)
            } else pushChanges(undo, Changes(0, text));
        }//if (TLEN != TWCL)
    }//if (undoRedoFlag)
    twc = text;
}//on_textEdit_textChanged()

void MyTextEdit::on_actionUndo_triggered()
{
    if (undo.count()) {
        undoRedoFlag = true;

        QTextCursor cursor = textCursor();
        QString text = toPlainText();

        if (UTOP.del) {
            // если "слово" было удалено
            text.insert(UTOP.pos, UTOP.data);
            pushChanges(redo, undo.pop());
            setPlainText(text);
            cursor.setPosition(RTOP.pos + RTOP.data.length());
        } else {
            // если "слово" было дописано
            QString r_text = text.right(TLEN - UTOP.pos - UTOP.data.length());
            text.truncate(UTOP.pos);
            pushChanges(redo, undo.pop());
            setPlainText(text + r_text);
            cursor.setPosition(RTOP.pos);
        }//if (UTOP.del)
        setTextCursor(cursor);
    }//if (count.size())
}//on_actionUndo_triggered()

void MyTextEdit::on_actionRedo_triggered()
{
    if (redo.count()) {
        undoRedoFlag = true;

        QTextCursor cursor = textCursor();
        QString text = toPlainText();

        if (RTOP.del) {
            // если "слово" было удалено
            QString r_text = text.right(TLEN - RTOP.pos - RTOP.data.length());
            text.truncate(RTOP.pos);
            pushChanges(undo, redo.pop());
            setPlainText(text + r_text);
            cursor.setPosition(UTOP.pos);
        } else {
            // если "слово" было дописано
            text.insert(RTOP.pos, RTOP.data);
            pushChanges(undo, redo.pop());
            setPlainText(text);
            cursor.setPosition(UTOP.pos + UTOP.data.length());
        }//if (RTOP.del)
        setTextCursor(cursor);
    }//if (count.size())
}//on_actionRedo_triggered()
