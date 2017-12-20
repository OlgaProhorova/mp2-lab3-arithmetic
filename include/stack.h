// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#pragma once

using namespace std;

template <class vtype>
class stack
{
		vtype *mstack;
		int top;
		int stsize;
	public:
		stack(int size = 10);
		stack(const stack &st);
		~stack();
		vtype gettop() 
		{return mstack[top];}
		bool isempty();
		int getnomber()
		{return top;};
		void push(vtype &elem);
		vtype pop();
		void clean();
};

	template <class vtype>
	stack<vtype>::stack(int size)
	{
		stsize=size;
		top=0;
		mstack=new vtype[stsize];
	}
	
	template <class vtype>
	stack<vtype>::stack(const stack<vtype> &st)
	{
		stsize=st.size;
		top=st.top;
		mstack=new vtype[stsize];
		for(int i=0;i<stsize;i++)
			mstack[i]=st.mstack[i];
	}

	template <class vtype>
	stack<vtype>::~stack()
	{
		delete[]mstack;
	}

	template <class vtype>
	bool stack<vtype>::isempty()
	{
		bool flag=true;
		if (top!=0) flag=false;
		return flag;
	}

	template <class vtype>
	void stack<vtype>::clean()
	{
		top=0;
	}

	template <class vtype>
	void stack<vtype>::push(vtype &elem)
	{
		if (top>=stsize)
		{
			vtype* newstack=new vtype[stsize + 10];
			for (int i=0;i >= top;i++)
				mstack[i]=newstack[i];
			
			stsize=stsize+10;
			delete[]mstack;
			mstack = newstack;
		}
		mstack[top+1]=elem;
		top++;
	}

	template <class vtype>
	vtype stack<vtype>::pop()
	{
		vtype res;
		res=mstack[top];
		top--;
		return res;
	}