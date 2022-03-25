#include <iostream>
#include <set>
#include <locale>
#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

int numberOfNodes;

struct Node
{
    int info;
    Node* right;
    Node* left;
};

Node* root;
Node* detectedNode;
bool contToSearch = true;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

bool isEmpty()
{
    if (root == nullptr)
    {
        return true;
    }
    return false;
}

void Search(Node* pNode, int intToFind)
{
    if (contToSearch && pNode != nullptr)
    {
        if (pNode->info == intToFind)
        {
            detectedNode = pNode;
            contToSearch = false;
        }
        Search(pNode->left, intToFind); Search(pNode->right, intToFind);
    }
}

void AddNodes()
{
    root = new Node();
    cout << "Введите информационную часть корня дерева: "; root->info = CheckedInput();
    root->left = nullptr; root->right = nullptr;
}

void AddNodes(Node* pCurr) // рекурсивная процедура добавления вершины
{
    int intToAdd;
    Node* pTemp;
    
    if (pCurr->left != nullptr && pCurr->right != nullptr)
    {
        cout << "Данная вершина уже имеет обоих потомков.\n";
    }

    else if (pCurr->left == nullptr && pCurr->right != nullptr )
    {
        cout << "У данной вершины свободна левая ветвь, какой элемент хотите добавить?: "; intToAdd = CheckedInput();
        pTemp = new Node(); pTemp->left = nullptr; pTemp->right = nullptr; pTemp->info = intToAdd;
        pCurr->left = pTemp;
    }
    
    else if (pCurr->left != nullptr && pCurr->right == nullptr)
    {
        cout << "У данной вершины свободна правая ветвь, какой элемент хотите добавить?: "; intToAdd = CheckedInput();
        pTemp = new Node(); pTemp->left = nullptr; pTemp->right = nullptr; pTemp->info = intToAdd;
        pCurr->right = pTemp;
    }

    else
    {
        int whereToAdd;
        cout << "Обе ветви свободны, в какую хотите добавить новую вершину?\n1 - Влево\n2 - Вправо\nВыбор: "; whereToAdd = CheckedInput(1,2);
        cout << "Введите информационную часть нового элемента: "; intToAdd = CheckedInput();
        pTemp = new Node(); pTemp->left = nullptr; pTemp->right = nullptr; pTemp->info = intToAdd;
        if (whereToAdd == 1)
        {
            pCurr->left = pTemp;
        }
        else
        {
            pCurr->right = pTemp;
        }
    }
    
}

void PrintNode(int info, int lvl) // вывод в консоль текущей вершины
{
    for (int i = 0; i < lvl * 5; i++)
    {
        cout << " ";
    }
    cout << info << "\n";
}

void PrintBack(Node* pCurr, int lvl) // обратно-симметрический проход
{
    if (pCurr != NULL)
    {
        PrintBack(pCurr->right, ++lvl); --lvl;
        PrintNode(pCurr->info, lvl);
        PrintBack(pCurr->left, ++lvl); --lvl;
    }
}

void Delete(Node* pTemp) // рекурсивная функция освобождения памяти
{
    if (pTemp != NULL)
    {
        Delete(pTemp->left);
        Delete(pTemp->right);
        delete pTemp;
    }
}

void CallMenu()
{
    
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Поиск заданного элемента\n2 - Добавления потомка вершины\n3 - Вывод дерева\n";
        cout << "4 - Удаление дерева\n5 - Завершение программы\n";
        cout << "Действие: "; choice = CheckedInput(1, 5);
        switch (choice)
        {
        case 1:
            detectedNode = nullptr;
            contToSearch = true;
            
            if (isEmpty())
            {
                cout << "Дерево пустое. Искать нечего.\n\n"; break;
            }
            cout << "Введите информационную часть вершины для поиска: "; Search(root, CheckedInput());
            if (detectedNode != nullptr)
            {
                cout << "Вершиина найдена";
            }
            else
            {
                cout << "Вершина не найдена";
            }
            cout << "\n\n";
            break;
        case 2:
            detectedNode = nullptr;
            contToSearch = true;
            
            if (isEmpty())
            {
                cout << "Дерево пустое\n"; AddNodes();  
                cout << "Дерево: \n";
                PrintBack(root, 0);
                cout << "\n\n";
                break;
            }
            cout << "Введите информационную часть вершины, которой следует добавить потомка: "; Search(root, CheckedInput());

            if (detectedNode == nullptr)
            {
                cout << "Такой вершины не существует\n";
            }
            
            else
            {
                AddNodes(detectedNode);
            }
            
            cout << "Дерево: \n";
            PrintBack(root, 0);
            cout << "\n\n";
            break;
        
        case 3:
            if (isEmpty())
            {
                cout << "Дерево пустое.\n\n"; break;
            }

            cout << "Дерево: \n";
            PrintBack(root,0);
            cout << "\n\n";
            break;
        
        case 4:
            Delete(root);
            root = nullptr;
            cout << "\n\n";
            break;
        
        case 5:
            Delete(root);
            work = false;
            cout << "\n\n";
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));
    CallMenu();
    _CrtDumpMemoryLeaks();
}
