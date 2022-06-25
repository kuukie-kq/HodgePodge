//
// Created by end-cookie on 2020-10-19.
//

#ifndef ENTRANCE_CUSTOMMESSAGE_H
#define ENTRANCE_CUSTOMMESSAGE_H

#pragma once

class CustomMessage {
    //内容信息
private:
    int row;
    int list;
    char* message;
    bool rowFirst;
    bool rowLast;
public:
    CustomMessage* next;

    CustomMessage() {
        row = 1;
        list = 1;
        message = "";
        next = nullptr;
        rowFirst = true;
        rowLast = true;
    }

    void setRow( int ir ) {
        row = ir;
    }

    void setList( int il ) {
        list = il;
    }

    void setMessage( char* im ) {
        message = im;
    }

    void setRowFirst( bool  irf ) {
        rowFirst = irf;
    }

    void setRowLast( bool irl ) {
        rowLast = irl;
    }

    int getRow() const {
        return row;
    }

    int getList() const {
        return list;
    }

    char* getMessage() {
        return message;
    }

    bool getRowFirst() const {
        return rowFirst;
    }

    bool getRowLast() const {
        return rowLast;
    }
};

#endif //ENTRANCE_CUSTOMMESSAGE_H
