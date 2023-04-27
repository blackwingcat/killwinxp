// Project1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cassert>
#include <thread>
#include <windows.h>

HINSTANCE hdll;
FARPROC f3;
void task1(const std::string msg) {
    int r, r1;
    char pic[256] = {0};
    char pic2[256] = { 0 };
    char pic3[256] = { 0 };
//    hdll= LoadLibraryA("nt6dlltest.dll");
    FARPROC f1 = GetProcAddress(hdll, "fun");
    FARPROC f2 = GetProcAddress(hdll, "fun2");
    if(f1)
    _asm {
        push 0
        lea eax, byte ptr [pic]
        push eax
        push 0
        push 0
        call f1
        mov r,eax
    }
    else { lstrcpyA(pic, "fail"); }
    if (f2)
    _asm {
        push 0
        lea eax, byte ptr[pic2]
        push eax
        push 0
        push 0
        call f2
        mov r1, eax
    } else  lstrcpyA(pic, "fail2");
    lstrcatA(pic, pic2);
    wsprintfA(pic3, "[%d][%d]", r, r1);
        MessageBoxA(0, pic, pic3, 0);
    //    std::cout << "task1:" << msg << std::endl;
}

void task2(const std::string msg) {
//    std::cout << "task2:" << msg << std::endl;
}
int main()
{
    // ここでxにアクセスするとdata raceにより未定義動作
    hdll = LoadLibraryA("nt6dlltest.dll");
    f3 = GetProcAddress(hdll, "funzero");
    


    if (f3)_asm {
        push 0
        push 0
        push 0
        push 0
        call f3
    }
    std::thread t1(task1, "Hello World!!");
    std::thread t2(task1, "Hello World!!");
    t1.join();
    t2.join();


    std::cout << "Hello World!\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
