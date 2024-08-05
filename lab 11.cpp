#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student
{
	friend class StudentBST;
private:
	int id; 
	string name; 
	float fee; 
	Student* left; 
	Student* right; 

public:
	Student(int id, const string& name, float fee) 
	{
		this->id = id;
		this->name = name;
		this->fee = fee;
		this->left = nullptr;
		this->right = nullptr;
	}

};

class StudentBST
{
private:
	Student* root;

public:
	StudentBST():root(nullptr) {}

	~StudentBST()
	{
		destroy(root);
	}

	bool insert(int id, string name, float fee)
	{
		return insertHelper(root, id,name,fee);
	}

	void search(int id) 
	{
		searchHelper(root, id);
	}

	void inOrder() 
	{
		inOrderHelper(root);
	}

	void preOrder() 
	{
		preOrderHelper(root);
	}

	void postOrder() 
	{
		postOrderHelper(root);
	}

	void deleteNode(int id) 
	{
		root = deleteHelper(root, id);
	}

private:

	bool insertHelper(Student*& node, int id, const string& name, float fee)
	{
		if (!node)
		{
			node = new Student(id, name, fee);
			return true;
		}
		if (id < node->id)
		{
			return insertHelper(node->left, id, name, fee);
		}
		else if(id>node->id)
		{
			return insertHelper(node->right, id, name, fee);
		}
		else {
			return false;
		}
	}


	void searchHelper(Student* node, int id) 
	{
		if (!node) 
		{
			cout << "Student not found..." << endl;
			return;
		}
		if (id == node->id)
		{
			cout << "Student found..." << endl;
			cout << "Id: " << node->id << endl << "Name: " << node->name << endl << "Fee: " << node->fee << endl;
		}
		else if (id < node->id)
		{//chooti hai to left pe dhoondo
			searchHelper(node->left, id);
		}
		else
		{//bari hai to right pe dhoondo
			searchHelper(node->right, id);
		}
	}

	void inOrderHelper(Student* node) 
	{
		if (node) 
		{
			inOrderHelper(node->left);
			cout << "Id: " << node->id << endl << "Name: " << node->name << endl << "Fee: " << node->fee << endl;			inOrderHelper(node->left);
			inOrderHelper(node->right);
		}
	}

	void preOrderHelper(Student* node) 
	{
		if (node)
		{
			cout << "Id: " << node->id << endl << "Name: " << node->name << endl << "Fee: " << node->fee << endl;			inOrderHelper(node->left);
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	void postOrderHelper(Student* node)
	{
		if (node)
		{
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout << "Id: " << node->id << endl << "Name: " << node->name << endl << "Fee: " << node->fee << endl;			inOrderHelper(node->left);
		}
	}

	void destroy(Student* node) 
	{
		if (node) 
		{
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}

	Student* deleteHelper(Student* node, int id)
	{
		if (!node)
		{

			cout << "Student not found..." << endl;
			return nullptr;
		}
		//Degree zero
		if (id < node->id) 
		{
			node->left = deleteHelper(node->left, id);
		}
		else if (id > node->id) 
		{
			node->right = deleteHelper(node->right, id);
		}
		else
		{
			if (!node->left && !node->right) 
			{
				delete node;
				return nullptr;
			}
			//Degree 1
			else if (!node->left)  
			{
				Student* temp = node->right;
				delete node;
				return temp;
			}
			else if (!node->right)
			{
				Student* temp = node->left;
				delete node;
				return temp;
			} 
			else  //Degree 2
			{
				Student* temp = findMin(node->right);
				node->id = temp->id;
				node->name = temp->name;
				node->fee = temp->fee;
				node->right = deleteHelper(node->right, temp->id);
			}
		}
		return node;
	}

	Student* findMin(Student* node)
	{
		while (node->left) 
		{
			node = node->left;
		}
		return node;
	}
};



int main()
{
	StudentBST studentTree;

	ifstream inputFile("input.txt");

	if (!inputFile) 
	{
		cout << "File not found" << endl;
		return 1;
	}

	int id;
	string name;
	float fee;

	while (inputFile >> id >> name >> fee) 
	{
		if (studentTree.insert(id, name, fee))
		{
			cout << "Student inserted: ID=" << id << ", Name=" << name << ", Fee=" << fee << endl;
		}
		else 
		{
			cout << "Student not inserted." << endl;
		}
	}

	inputFile.close();

	cout << "\nIn-order:" << endl;
	studentTree.inOrder();

	cout << "\nPre-order:" << endl;
	studentTree.preOrder();

	cout << "\nPost-order:" << endl;
	studentTree.postOrder();

	int searchId = 2;
	cout << "\nSearching ID: " << searchId << endl;
	studentTree.search(searchId);

	int deleteId = 4;
	cout << "\nDeleting ID: " << deleteId << endl;
	studentTree.deleteNode(deleteId);

	cout << "\nAfter deletion:" << endl;
	studentTree.inOrder();

	return 0;
}