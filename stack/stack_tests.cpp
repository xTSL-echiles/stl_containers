#include <vector>
#include "../vector/vector.hpp"
#include <stack>
#include "stack.hpp"
void stack_constructor_check()
{
    std::cout << "||-------------------------------------------CONSTRUCTOR-------------------------------------------||" << std::endl;

    std::vector<int> myvector (2,200);
    std::stack<int> first;
    std::stack<int,std::vector<int> > third;
    std::stack<int,std::vector<int> > fourth (myvector);
    std::stack<int,std::vector<int> > fif (fourth);


    std::cout << "size of first: " << first.size() << '\n';
    std::cout << "size of third: " << third.size() << '\n';
    std::cout << "size of fourth: " << fourth.size() << '\n';

    ft::vector<int> myvector_ft (2,200);
    ft::stack<int> first_ft;
    ft::stack<int,ft::vector<int> > third_ft;
    ft::stack<int,ft::vector<int> > fourth_ft (myvector_ft);
    ft::stack<int,ft::vector<int> > fif_ft (fourth_ft);


    std::cout << "size of first_ft: " << first_ft.size() << '\n';
    std::cout << "size of third_ft: " << third_ft.size() << '\n';
    std::cout << "size of fourth_ft: " << fourth_ft.size() << '\n';
}   

void stack_empty_check()
{
    std::cout << "||-------------------------------------------EMPTY|TOP|POP-------------------------------------------||" << std::endl;

    std::stack<int, std::vector<int> > mystack;
    int sum (0);

    for (int i=1;i<=10;i++) mystack.push(i);

    while (!mystack.empty())
    {
       sum += mystack.top();
       mystack.pop();
    }
    std::cout << "total STD: " << sum << '\n' << std::endl;

    ft::stack<int, ft::vector<int> > mystack_ft;
    sum = 0;

    for (int i=1;i<=10;i++) mystack_ft.push(i);

    while (!mystack_ft.empty())
    {
       sum += mystack_ft.top();
       mystack_ft.pop();
    }
    std::cout << "total FT:  " << sum << '\n';
}

void stack_push_check()
{
    std::cout << "||-------------------------------------------PUSH-------------------------------------------||" << std::endl;

    std::stack<int> mystack;

    for (int i=0; i<5; ++i) mystack.push(i);

    std::cout << "STD Popping out elements...";
    while (!mystack.empty())
    {
       std::cout << ' ' << mystack.top();
       mystack.pop();
    }
    std::cout << '\n' << std::endl;

    ft::stack<int> mystack_ft;

    for (int i=0; i<5; ++i) mystack_ft.push(i);

    std::cout << "FT  Popping out elements...";
    while (!mystack_ft.empty())
    {
       std::cout << ' ' << mystack_ft.top();
       mystack_ft.pop();
    }
    std::cout << '\n';
}
void    stack_operators_check()
{
    std::cout << "||-------------------------------------------operators-------------------------------------------||" << std::endl;

    std::stack<int> mystack;
    for (int i=0; i<5; ++i) mystack.push(i);
    std::stack<int> mystack_2;
    for (int i=0; i<7; ++i) mystack.push(i);
    ft::stack<int> mystack_ft;
    for (int i=0; i<5; ++i) mystack_ft.push(i);
    ft::stack<int> mystack_ft_2;
    for (int i=0; i<7; ++i) mystack_ft.push(i);

    std::cout << "STD " << (mystack < mystack_2) << " FT " << (mystack_ft < mystack_ft_2) <<  std::endl;
    std::cout << "STD " << (mystack <= mystack_2) << " FT " << (mystack_ft <= mystack_ft_2) <<  std::endl;
    std::cout << "STD " << (mystack > mystack_2) << " FT " << (mystack_ft > mystack_ft_2) <<  std::endl;
    std::cout << "STD " << (mystack >= mystack_2) << " FT " << (mystack_ft >= mystack_ft_2) <<  std::endl;
    std::cout << "STD " << (mystack != mystack_2) << " FT " << (mystack_ft != mystack_ft_2) <<  std::endl;
    std::cout << "STD " << (mystack == mystack_2) << " FT " << (mystack_ft == mystack_ft_2) <<  std::endl;

}
int main()
{
    stack_constructor_check();
    stack_empty_check();
    stack_push_check();
    stack_operators_check();
}