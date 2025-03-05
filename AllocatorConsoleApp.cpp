#include <iostream>
#include "Allocator.h"
#include "DataTypes.h"


class MyClass
{
private:
    DECLARE_ALLOCATOR
    int* arr = nullptr;
    size_t size = 0;

public:


    MyClass(const size_t size_)
    {
        std::cout << "Вызов конструктора" << std::endl;
        size = size_;
        arr = (int*)operator new[](size * sizeof(int));
    }

    int* GetIndex(const size_t idx)
    {
        return arr + idx;
    }


    ~MyClass()
    {
        std::cout << "Вызов деструктора " << std::endl;
        operator delete[](arr);
    }

};


IMPLEMENT_ALLOCATOR(MyClass, 0, 0)

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

    Allocator allocatorHeapBloks(40); //в будущем хочу использовать память для создания массива из 10 элементов типа int


    int* numbers = (int*)allocatorHeapBloks.Allocate(10 * sizeof(int)); //если будет 11 то будет ошибка
    if (numbers)
    {
        for (int i = 0; i < 10; i++)
        {
            numbers[i] = i + 1;
            std::cout << "numbers[ " << i << " ] = " << numbers[i] << std::endl;
        }
    }
    else
    {
        std::cerr << "Ошибка выделения памяти";
    }

    //в случае с режимом блоков кучи с неограниченными блоками можем много раз выделять блоки такого размены
    //который указан в алокаторе
    int* numbersTry = (int*)allocatorHeapBloks.Allocate(10 * sizeof(int)); //если будет 11 то будет ошибка
    if (numbersTry)
    {
        for (int i = 0; i < 10; i++)
        {
            numbersTry[i] = i + 1;
            std::cout << "numbersTry[ " << i << " ] = " << numbersTry[i] << std::endl;
        }
    }
    else
    {
        std::cerr << "Ошибка выделения памяти";
    }


    allocatorHeapBloks.Deallocate(numbers);
   std::cout << std::endl;


    //в случае с режимом пула кучи мы выделяем кол-во блоков (2 сейчас) с нужным количеством байт (20 сейчас)
    Allocator allocatorHeapPool(40, 2); 
    int* numbers1 = (int*)allocatorHeapPool.Allocate(10 * sizeof(int)); //если будет 11 то будет ошибка
    if (numbers1)
    {
        for (int i = 0; i < 10; i++)
        {
            numbers1[i] = i + 1;
            std::cout << "numbers1[ " << i << " ] = " << numbers1[i] << std::endl;
        }
    }
    else
    {
        std::cerr << "Ошибка выделения памяти";
    }

    std::cout << std::endl;

    //если будет 11 то будет ошибка + если используем больше блоков чем разрешено (сейчас 2) то будет ошибка
    int* numbers2 = (int*)allocatorHeapPool.Allocate(10 * sizeof(int)); 
    if (numbers2)
    {
        for (int i = 0; i < 10; i++)
        {
            numbers2[i] = i + 1;
            std::cout << "numbers2[ " << i << " ] = " << numbers2[i] << std::endl;
        }
    }
    else
    {
        std::cerr << "Ошибка выделения памяти";
    }

    //если попытаться использовать 3 блок памяти из пула которого нет то будет ошибка
    //int* numbers3 = (int*)allocatorHeapPool.Allocate(10 * sizeof(int));
    //if (numbers3)
    //{
    //    for (int i = 0; i < 10; i++)
    //    {
    //        numbers3[i] = i + 1;
    //        std::cout << "numbers3[ " << i << " ] = " << numbers3[i] << std::endl;
    //    }
    //}
    //else
    //{
    //    std::cerr << "Ошибка выделения памяти";
    //}

    // Режим статического пула с 2, 40 байтовыми блоками (быстрее всех)
    char staticMemoryPool[40 * 2];
    Allocator allocatorStaticPool(40, 2, staticMemoryPool);

    int* numbersFromStatic = (int*)allocatorStaticPool.Allocate(10 * sizeof(int));
    if (numbersFromStatic)
    {
        for (int i = 0; i < 10; i++)
        {
            numbersFromStatic[i] = i + 1;
            std::cout << "numbersFromStatic[ " << i << " ] = " << numbersFromStatic[i] << std::endl;
        }
    }
    else
    {
        std::cerr << "Ошибка выделения памяти";
    }


    size_t sizeOfArrInClass = 10000;
    MyClass* obj1 = new MyClass(sizeOfArrInClass);

    std::cout << "vvedite " << sizeOfArrInClass << " elementov massiva" << std::endl;
    for (int i = 0, number = 0; i < sizeOfArrInClass; i++)
    {
        //std::cin >> number;
        *(obj1->GetIndex(i)) = 0 + rand() % 11;
    }

    for (int i = 0; i < sizeOfArrInClass; i++)
    {
        //std::cout << "ArrInClass[" << i << "] = " << *(obj1->GetIndex(i)) << std::endl;
    }
        
     delete obj1;

     std::cout << "Нажмите  клавишу enter чтобы завершить программу";
     std::cin.get();
    return 0;
}