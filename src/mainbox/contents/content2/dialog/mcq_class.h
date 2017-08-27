//
// Created by poh on 8/22/17.
//

#ifndef GTK_DIALOG_MCQ_H
#define GTK_DIALOG_MCQ_H


#include "_dialog_qn.h"

class mcq_class : public dialog_qn {
protected:
public:
    mcq_class();
    void save_values() override;

};


#endif //GTK_DIALOG_MCQ_H
