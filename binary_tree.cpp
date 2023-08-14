#include <iostream>    

// For the random shuffle
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// For sleep function
#include <unistd.h>

using namespace std;    

struct Node
{
    int data;
    Node* parent;
    Node* left;
    Node* right;
    bool isDefined=false;
    int maxDepth=1;

    bool isPrinted=false;

    Node()
    {
        parent=nullptr;
        left=nullptr;
        right=nullptr;
    }
    ~Node() {}

    void SetData(int val)
    {
        data = val;
        isDefined = true;
    }

    void SetParent(Node* p)
    {
         parent=p;
    }
};

Node* createNode(int val, Node* parent)
{
     Node* newNode = new Node();
     newNode->SetData(val);
     newNode->SetParent(parent);
     return newNode;
}


void AddToTree(Node& root, int num)
{

        if (!root.isDefined)
        {
            root.SetData(num);
            return;
        }
            
        Node* current = &root;
        bool itterating = true;
        int currentDepth = 1;
        while(itterating)
        {
            currentDepth++;
            if (currentDepth > root.maxDepth) {
                root.maxDepth = currentDepth;
            }

            if ( num == current->data)
            {
                break;
                 itterating = false;
            }

            if ( num < current->data )
            {
                if ( current->left == nullptr)
                {
                    current->left = createNode(num, current);
                    break;
                    itterating = false;

                }
                else 
                {
                    current = current->left;
                    continue;
                }
            }

            if ( num > current->data )
            {
                if ( current->right == nullptr)
                {
                    current->right = createNode(num, current);
                    break;
                    itterating = false;
                }
                else 
                {
                    current = current->right;
                    continue;
                }
            }


        }
        return;

}

int GetMaximum(Node &root)
{
    Node* current = &root;
     while (true)
     {
          if (current->right == nullptr)
          {
               return current->data;
          }
          
          current = current->right;
     }
}


void PrintSorted(Node &root, int maxVal)
{
    Node* current = &root;
    while (true)
    {
        if (current->left == nullptr || current->left->isPrinted)
        {
            if (current->isPrinted)
            {
                if (current->right == nullptr || current->right->isPrinted)
                {
                    current = current->parent;
                }
                else
                {
                    current = current->right;
                }
            }
            else
            {
                //cout << "\r" << current->data << flush;    // same line  
                cout << current->data << " " << flush;     
                current->isPrinted=true;
                if (current->data == maxVal)
                {
                    cout << "\nFinished." << endl;
                    break;
                }
            }
        }
        else
        {
             current = current->left;
        }
    }
}

int main(){    

    // given an array 
    //int numbers[]={3,4,2,1,5,6,7};
    //int numbers[]={-1,5,1,2,3,4,6};

    int size; // handles 1 million fine. Just takes a while to print
    cout << "Give me a whole number, I will shuffle the set of integers from 1 to your number. Then I will create a binary tree to sort them again." << endl;
    cout << "Input : ";
    cin >> size;

    

    // Create an array of integers from 1 to size
    vector<int> numbers;
    for (int i = 1; i <= size; ++i) {
        numbers.push_back(i);
    }

    // Seed the random number generator
    unsigned seed = time(0);
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    // Display the scrambled array
    for (int i = 0; i < size; ++i) {
        cout << numbers[i] << " ";
        //if ((i + 1) % 10 == 0) {
            //cout << endl;
        //}
    }

    cout << "\nSorting in 3..." << endl;
    sleep(1);
        cout << "2.." << endl;
    sleep(1);
        cout << "1.." << endl;
    sleep(1);
        cout << "GO!" << endl;


    // create a sorted binary tree
    Node root;
    for (auto &num: numbers)
    {
        AddToTree(root, num);
    }

    cout << "Done!" << endl;

    cout << "Depth: " << root.maxDepth << endl;
    int maxVal = GetMaximum(root);
    cout << "Maximum: " << maxVal << endl;
   
    //sleep(2);
    cout << "Printing: " << endl;

    PrintSorted(root, maxVal);

    return 0;  
}


