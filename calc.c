//
//  calc.c
//  jikken1-obj1
//  計算機
//  Created by Yuhei Akamine on 2018/05/10.
//  Copyright (c) 2014年 Yuhei Akamine. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <ncurses.h>

//入力値
static int inputValue;
//計算値
static int computation;
//演算子
static int operation;
//入力値の保存
static int memory_input;
//記号の保存
static char memory_operate;
//イコールの連続入力を保存
static int cnt_equal;

//計算機の初期化
void initialize()
{
    inputValue = 0;
    computation = 0;
    operation = 0;
    memory_input = 0;
    cnt_equal = 0;
}

//階乗を行う関数(演習4)
int fact(int n)
    {
        if(n == 0)
            return 1;
        return n*fact(n-1);
}

//素数を判定する関数(オプション課題2)
int isPrime(int n)
{
    int i, max;
    max = (int)sqrt(n) + 1;
    if (n < 2) {
        return 0;
    }
    for (i = 2; i < max; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

//イコールが二回押された時に使う関数(オプション課題1)
void calculate_hurumai()
{
    switch (memory_operate) {
        case '+':
            computation += memory_input;
            break;
            
        case '-':
            computation -= memory_input;
            break;
            
        case '*':
            computation *= memory_input;
            break;
            
        case '/':
            if(memory_input != 0){ //分母に0がきてないかを判定
            computation /= memory_input;
            break;
        }
        
        default:
        break;
        }
    }

void calculate()
{
    // ユーザが'+'を指定した時，operation には，'+'(+という文字のアスキーコド)が代入されている
    // 同様に，'-'，'*', '/'もそれぞれアスキーコードが入っているのでcaseで場合分けして，演算
    // するコードを書く．
    // 例えば, 加算('+')の場合，computation += inputValueとなる

    switch (operation) {
        case 0:
            computation = inputValue;
            break;
            
        case '+': 
            computation += inputValue;
            break;
            
        case '-':
            computation -= inputValue;
            break;
            
        case '*':
            computation *= inputValue;
            break;
            
        case '/':
            if(inputValue != 0){ //分母に0がきてないかを判定
            computation /= inputValue;
            break;
            }
            
        case '!': //演習4
            computation = fact(computation);
            break;
        
        case'p': //オプション課題2
            computation = isPrime(computation);
            break;
        
        default:
        break;
    }
        memory_operate = operation; //前回の演算子の保存
        memory_input = inputValue; //前回の数字の保存
        inputValue = 0;
}

void inputNumber(char key){
    //keyはASCII codeなので，整数に変換する
    int digit = key - '0';

    inputValue = digit + inputValue*10 ; //演習1
    
    //演習１はここに追加
    //inputValueの値を決めるコードを書く
}
void judge_equalCnt(int n){ //オプション課題1
    if (cnt_equal > 1){ //イコールが連続で押されたかを判定
        calculate_hurumai();
    }
}

void inputOperator(char key)
{
    calculate();
    if(key != '=') {
        operation = key;
        cnt_equal = 0; //イコールカウンタのリセット
    }else if(key == '='){ //オプション課題1
        cnt_equal++; //イコールカウンタ
        judge_equalCnt(cnt_equal);
    }
}

void input(char key)
{
    //keyは数字か？
    if(isdigit(key)) {
        inputNumber(key);
    }else if(key == 'c'){ //演習3
         initialize(); //初期化
    }else{
        inputOperator(key);
    }
}

//テストコード
void test()
{
    initialize();
    
    input('1'); //1キーを押した
    input('2'); //2キーを押した
    input('3'); //3キーを押した
    
    assert(inputValue == 123); //入力値は123になっているべき
    
    printf("1st Test Passed!\n");
    
    input('+'); //'+'キーを押した.
    
    assert(computation == 123); //計算値に代入されている
    assert(inputValue == 0); //入力値はクリアされているはず
    
    input('3');
    input('4');
    
    assert(inputValue == 34); //入力値は34のはず
    
    input( '-'); //'-'キーを押した．ここで前回押した+演算が実行される
                               //実際の計算機の挙動を確認せよ
    
    assert(computation == 157); //123+10の結果がはいっているはず
    
    input('5');
    input('6');
    
    input('*'); //前回入力した-演算が実行されるはず
    
    assert(computation == 101);
    
    input('7');
    input('8');
    input('9');
    
    input('/');
        
    assert(computation == 79689);
    
    input('7');
    input('8');
    input('9');
    input('=');
    
    assert(computation == 101);
    
    printf("2nd Test Passed!\n");
    
    input('c'); //演習3
    assert(computation == 0);
    assert(inputValue == 0);
    assert(operation == 0);
    
    printf("3rd Test Passed!!!\n");
    
    input('5'); //演習4
    input('!');
    input('=');
    
    assert(computation == 120);
    
    printf("4th Test Passed!!!!\n");
    
    input('c');
    assert(computation == 0);
    assert(inputValue == 0);
    assert(operation == 0);
    
    input('1'); //オプション課題2
    input('1');
    input('p');
    input('=');
    
    assert(computation == 1);
    
    input('4');
    input('p');
    input('=');    
    assert(computation == 0);
    
    printf("2nd option Test Passed\n");
    
    input('c');
    assert(computation == 0);
    assert(inputValue == 0);
    assert(operation == 0);
    
    input('8'); //オプション課題1
    input('1');
    input('/');
    input('3');
    input('=');
    assert(computation = 27);
    input('=');
    assert(computation = 9);
 
    input('c');
    assert(computation == 0);
    assert(inputValue == 0);
    assert(operation == 0);
    
    printf("1st option Test Passed\n");
        
    printf("All Tests passed.\n");
}

int main()
{
    test();
    initialize();

    /*
    initscr();
    //echo();
    
    char key=0;
    while(key != 'q')
    {
        key = getch();
        input(key);
        
        move(0,0);

        if(inputValue != 0) {
            printw("in %d\n", inputValue);
        }else {
            printw("co %d\n", computation);
        }
        refresh();
    }
    
    endwin();
    */
}