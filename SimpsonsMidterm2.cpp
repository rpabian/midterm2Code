#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Parent;

void printName(std::string name)
{
	std::cout << name << " " << std::endl;
}


class Human
{
private: 
	std::string m_name;
	int m_age;
	char m_sex;
	Human()
	{
		m_name = "";
		m_age = 0;
		m_sex = 'M';
	}
protected:
	Human(std::string name, int age, char sex)
	{
		m_name = name;
		m_age = age;
		m_sex = sex;
	}
	virtual ~Human() {}
public:
	void setName(std::string name) { m_name = name; }
	void setAge(int age) { m_age = age; }
	void setSex(char sex) { m_sex = sex; }
	std::string getName() { return m_name; }
	int getAge() { return m_age; }
	char getSex() { return m_sex; }
};

class Child : public Human
{
private:
	std::string m_momName, m_dadName;
	int m_allowance;
	Child() : Human("", 0, 'M')
	{
		m_momName = "";
		m_dadName = "";
		m_allowance = 0;
	}
public:
	Child(std::string name, int age, char sex, std::string momName,
		std::string dadName) : Human(name, age, sex)
	{
		m_momName = momName;
		m_dadName = dadName;
		m_allowance = 0;
	}
	int getAllowance() const
	{
		std::cout << "Allowance: " << m_allowance << std::endl;
		return m_allowance;
	}
	void printParent()
	{
		std::cout << "Mom: " << m_momName << "\n"
			<< "Dad: " << m_dadName << std::endl;
	}
	friend Parent;
	//friend void Parent::setChildAllowance(int , Child &);
};


class Parent : public Human
{
private:
	std::vector<std::string> m_children;
	Parent() : Human("", 0, 'M')
	{
		m_children;
	}
public:
	Parent(std::string name, int age, char sex) : Human(name, age, sex)
	{
		m_children;
	}
	void printChild()
	{
		for_each(m_children.begin(), m_children.end(), printName);
	}
	void setChild(Child &child)
	{
		m_children.push_back(child.getName());
	}
	void setChildAllowance(int allowance, Child &child)
	{
		if (std::count(m_children.begin(), m_children.end(), child.getName()))
		{
			child.m_allowance = allowance;
		}
	}
};

void printInfoHuman(Human &human)
{
	std::cout << "Name: " << human.getName() << "\nAge:" << human.getAge()
		<< "\nSex: " << human.getSex() << std::endl;
}

int main()
{
	Parent homer("Homer", 36, 'M');
	Parent march("March", 34, 'F');
	Child bart("Bart", 10, 'M', "March", "Homer");
	Child lisa("Lisa", 12, 'F', "March", "Homer");
	Child maggie("Maggie", 3, 'F', "March", "Homer");

	homer.setChild(lisa);
	homer.setChild(bart);
	homer.setChild(maggie);
	march.setChild(lisa);
	march.setChild(bart);
	march.setChild(maggie);

	std::cout << "Bart's allowance: " << bart.getAllowance() << std::endl;

	homer.setChildAllowance(5, bart);
	std::cout << "Bart's allowance after Homer gives him 5$: " << bart.getAllowance() << std::endl;

	std::cout << "Bart's Parents:" << std::endl;
	bart.printParent();

	printInfoHuman(march);
	printInfoHuman(lisa);
}