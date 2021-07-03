//
// Created by End-Cookie on 2020-10-16.
//

#ifndef ENTRANCE_CUSTOMBLOCK_H
#define ENTRANCE_CUSTOMBLOCK_H

#pragma once
#include <iostream>
#include <cstring>
#include "CustomMessage.h"

class CustomBlock {
    //start定位边框开始的位置
    //size控制中间可加信息的大小length的数值实际有效的是1~length-1，height的数值有效为1~height
    /*
     * 使用说明
     * 类名：自定义图块
     * 可用函数setMessage设置图块内要显示的信息
     * 可用函数show显示这个图块到终端
     * 注意事项
     * 不支持嵌套，图块内不能有图块。
     * */
private:
    int startRow;   //开始纵坐标
    int startList;  //开始横坐标
    int sizeLength; //长度
    int sizeHeight; //高度
    CustomMessage first;//message链表的头部，本身无意义，作为链表的查找输出相应的设定好的信息
    CustomMessage* f;//message链表指针，用于操作。
    int listNumber;//记录一行内所使用的字节

    void availability() const {
        //判断数值是否可用
        bool flag = true;
        if( startRow < 0 )
            flag = false;
        if( startList < 0 )
            flag = false;
        if( sizeLength < 0 )
            flag = false;
        if( sizeHeight < 0 )
            flag = false;
        if( !flag ) {
            char* SECB="** code : 2-0001-1";
            throw SECB;
        }
    }

    void listAvailability() {
        //判断一行内是否能够全部显示
        bool flag;
        int flagNumber;
        for( f = first.next ;; f = f->next ) {
            if(f->getRowFirst()) {
                flagNumber = 0;
                flagNumber = flagNumber + f->getList() + strlen(f->getMessage());
            } else {
                flagNumber = flagNumber + f->getList() + strlen(f->getMessage());
            }
            if(f->getRowLast()) {
                flag = flagNumber < ( sizeLength - 1 );
                if(!flag) {
                    char* SECL="** code : 2-0001-3";
                    throw SECL;
                }
            }
            if( f->next == nullptr )
                break;
        }
    }

    void rowAvailability() {
        //判断是否能显示全部行
        //注*超过的行想要显示也没有问题，最后一个Message显示完后默认为最后一行，但与设计冲突，视情况而定
        bool flag;
        int flagNumber = 0;
        for( f = first.next ;; f = f->next ) {
            flagNumber = flagNumber + f->getRow();
            flag = flagNumber <= sizeHeight;
            if(!flag) {
                char* SECR="** code : 2-0001-4";
                throw SECR;
            }
            if( f->next == nullptr )
                break;
        }
    }

    void displayRow( int row ) const {
        int i;
        for( i = 0 ; i < row ; i++ ) {
            if ( i == 0 ) {
                std::cout << "\n";
            } else {
                //边框（中间行，没有东西的）/+/
                for( int j = 0 ; j < startList + sizeLength ; j++ ) {
                    if( j == startList || j == startList + sizeLength - 1 ) {
                        std::cout << "+";
                    } else {
                        std::cout << " ";
                    }
                }
                //边框（中间行，没有东西的）/-/
                std::cout << "\n";
            }

        }
        for( int j = 0 ; j < startList ; j++ ) {
            std::cout << " ";
        }
        std::cout << "+";
    }

    static int displayList( int list ) {
        for( int j = 0 ; j < list ; j++ ) {
            std::cout << " ";
        }
        return list;
    }

    static int displayMessage( char* message ) {
        std::cout << message;
        return strlen(message);
    }

    int displayLine( int row , int list , char* message , bool rowFirst , bool rowLast ) {
        if(rowFirst) {
            displayRow(row);
            listNumber = listNumber + displayList(list);
            listNumber = listNumber + displayMessage(message);
        } else {
            listNumber = listNumber + displayList(list);
            listNumber = listNumber + displayMessage(message);
        }
        if(rowLast) {
            for( int j = startList + listNumber + 1 ; j < startList + sizeLength ; j++ ) {
                if( j == startList + sizeLength - 1 ) {
                    std::cout << "+";
                } else {
                    std::cout << " ";
                }
            }
            listNumber=0;
        }
        return row;
    }
public:
    CustomBlock() {
        startRow = 0;
        startList = 0;
        sizeLength = 0;
        sizeHeight = 0;
        first.next = new CustomMessage();
        f = first.next;
        listNumber = 0;
    }

    CustomBlock( int row , int list , int length , int height ) {
        startRow = row;
        startList = list;
        sizeLength = length;
        sizeHeight = height;
        first.next = new CustomMessage();
        f = first.next;
        listNumber = 0;
        availability();
    }

    void setMessage( int row , int list , char* message , bool rowFirst , bool  rowLast , bool last ) {
        if( row < 0 || list < 0) {
            char* SECS="** code : 2-0001-2";
            throw SECS;
        }
        f->setRow(row);
        f->setList(list);
        f->setMessage(message);
        f->setRowFirst(rowFirst);
        f->setRowLast(rowLast);
        if( !last ) {
            f->next = new CustomMessage();
            f = f->next;
        }
    }

    void show() {
        listAvailability();
        rowAvailability();

        for( int i = 0 ; i < startRow ; i++ )
            std::cout << "\n";
        //边框（最上面一行）/+/
        for( int j = 0 ; j < startList ; j++ )
            std::cout << " ";
        for( int j = 0 ; j < sizeLength ; j++ )
            std::cout << "-";
        //边框（最上面一行）/-/
        bool flag = true;

        for( int i = 0 ; i < sizeHeight ; ) {
            if( flag ) {
                for( f = first.next ;; f = f->next ) {
                    i=i+displayLine(f->getRow(),f->getList(),f->getMessage(),f->getRowFirst(),f->getRowLast());
                    if( f->next == nullptr )
                        break;
                }
                flag = false;
            } else {
                std::cout << "\n";
                //边框（中间行，没有东西的）/+/
                for( int j = 0 ; j < startList + sizeLength ; j++ ) {
                    if( j == startList || j == startList + sizeLength - 1 ) {
                        std::cout << "+";
                    } else {
                        std::cout << " ";
                    }
                }
                //边框（中间行，没有东西的）/-/
                i++;
            }
        }

        //边框（最下面一行）/+/
        std::cout << "\n";
        for( int j = 0 ; j < startList ; j++ )
            std::cout << " ";
        for( int j = 0 ; j < sizeLength ; j++ )
            std::cout << "-";
        //边框（最下面一行）/-/
        std::cout << "\n";
    }
};


#endif //ENTRANCE_CUSTOMBLOCK_H
