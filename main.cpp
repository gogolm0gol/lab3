//Fedchuk Sofiia K-26, variant 14
#include <iostream>
#include <thread>
#include <latch>
#include <syncstream>
#include <chrono>
#include <cstdlib>

using namespace std;

latch a_done(5), b_done(4), c_done(5), d_done(4), e_done(5);
latch g_done(3), h_done(5), i_done(4), j_done(5);

void f(char name, int index) {
    this_thread::sleep_for(chrono::seconds(1));
    osyncstream(cout) << "З набору " << name << " виконано дію " << index << "." << endl;
}

void run(char name, int from, int to) {
    for (int i = from; i <= to; ++i) 
        f(name, i);
}

void thread1() {
    run('a', 1, 2); a_done.count_down();
    a_done.wait();
    run('e', 1, 2); e_done.count_down();
    run('b', 7, 7); b_done.count_down();
    run('c', 6, 6); c_done.count_down();
    b_done.wait(); c_done.wait();
    run('d', 1, 2); d_done.count_down();
    d_done.wait(); g_done.wait();
    run('h', 1, 2); h_done.count_down();
    e_done.wait();
    run('j', 8, 8); j_done.count_down();
    run('i', 3, 3); i_done.count_down();
    j_done.wait(); h_done.wait();
    run('f', 4, 4);
    i_done.wait();
    run('k', 5, 5);
}

void thread2() {
    run('a', 3, 4); a_done.count_down();
    a_done.wait();
    run('e', 3, 4); e_done.count_down();
    run('c', 1, 2); c_done.count_down();
    b_done.wait(); c_done.wait();
    run('d', 3, 4); d_done.count_down();
    d_done.wait(); g_done.wait();
    run('h', 3, 4); h_done.count_down();
    e_done.wait();
    run('j', 9, 9); j_done.count_down();
    run('i', 4, 4); i_done.count_down();
    i_done.wait();
    run('k', 1, 1);
}

void thread3() {
    run('a', 5, 5); a_done.count_down();
    run('b', 1, 1);
    a_done.wait();
    run('e', 5, 5); e_done.count_down();
    run('b', 2, 2); b_done.count_down();
    run('c', 3, 3); c_done.count_down();
    run('g', 1, 1); g_done.count_down();
    b_done.wait(); c_done.wait();
    run('d', 5, 5); d_done.count_down();
    e_done.wait();
    run('j', 1, 1);
    d_done.wait(); g_done.wait();
    run('h', 5, 5); h_done.count_down();
    run('j', 2, 3); j_done.count_down();
    j_done.wait(); h_done.wait();
    run('f', 1, 1);
    i_done.wait();
    run('k', 2, 2);
}

void thread4() {
    run('a', 6, 6); a_done.count_down();
    run('b', 3, 3);
    a_done.wait();
    run('e', 6, 6); e_done.count_down();
    run('b', 4, 4); b_done.count_down();
    run('c', 4, 4); c_done.count_down();
    run('g', 2, 2); g_done.count_down();
    b_done.wait(); c_done.wait();
    run('d', 6, 6); d_done.count_down();
    e_done.wait();
    run('j', 4, 4);
    d_done.wait(); g_done.wait();
    run('h', 6, 6); h_done.count_down();
    run('j', 5, 5); j_done.count_down();
    run('i', 1, 1); i_done.count_down();
    j_done.wait(); h_done.wait();
    run('f', 2, 2);
    i_done.wait();
    run('k', 3, 3);
}

void thread5() {
    run('a', 7, 7); a_done.count_down();
    run('b', 5, 5);
    a_done.wait();
    run('e', 7, 7); e_done.count_down();
    run('b', 6, 6); b_done.count_down();
    run('c', 5, 5); c_done.count_down();
    run('g', 3, 4); g_done.count_down();
    e_done.wait();
    run('j', 6, 6);
    d_done.wait(); g_done.wait();
    run('h', 7, 7); h_done.count_down();
    run('j', 7, 7); j_done.count_down();
    run('i', 2, 2); i_done.count_down();
    j_done.wait(); h_done.wait();
    run('f', 3, 3);
    i_done.wait();
    run('k', 4, 4);
}

int main() {
#ifdef _WIN32
    system("chcp 65001");
#endif
    osyncstream(cout) << "Обчислення розпочато." << endl;
    auto start = chrono::steady_clock::now();
    {
        jthread t1(thread1);
        jthread t2(thread2);
        jthread t3(thread3);
        jthread t4(thread4);
        jthread t5(thread5);
    }

    chrono::duration<double> d = chrono::steady_clock::now() - start;
    osyncstream(cout) << "Обчислення завершено. Тривалість обчислення "
                      << d.count() << " секунд." << endl;
    return 0;
}