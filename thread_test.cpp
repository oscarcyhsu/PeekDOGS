n#include <iostream>
#include <thread>

using namespace std;
void show()
{
    //下面這兩行迴圈只是延遲用
    for (int i = 1; i <= 10000; i++)
        for (int j = 1; j <= 10000; j++)
            ;

    cout << "World.";
}

int main()
{
    thread t1(show);

    cout << "Hello ";
    t1.join();//等待t1執行完畢才繼續往下執行
    cout << "\n\n\n";//跳三行

    system("pause");
    return 0;
}