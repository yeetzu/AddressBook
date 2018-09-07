#include <stdafx.h>
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <fstream>
#include <istream>
#define Submit_Button 1
using namespace std ;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

class Node
{
	friend class Trie;
private:
    char letter; //the character for the trie
    string number ; //phone number
    Node** next;
public:
    Node();
    Node(char letter, Node** next, string number);
    Node(Node& tmp);
    ~Node();
    void setNumber(string number);
    void setNext(char letter, Node* next);
    Node* getNext(char letter); //return char next
    Node** getNext();
    string getNumber();
    char getLetter();
    void setLetter(char x);
};
Node::Node()
{
    letter = 0;
    number = "";
    next = new Node*[26];
    for(int i = 0; i < 26; i++)
        next[i] = nullptr;
}
Node::Node(char letter, Node** next, string number)
{
    this->next = next;
    this->letter = letter;
    this->number = number ;
}
Node::Node(Node& tmp)
{
    this->letter = tmp.letter;
    this->next = tmp.next;
}
Node::~Node()
{
    delete [] next;
}
string Node::getNumber()
{
    return number;
}
void Node::setLetter(char x)
{
	this->letter = x;
}
void Node::setNext(char letter, Node* next)
{
    this->next[letter - 97] = next;
}
void Node::setNumber(string number)
{
    this->number = number ;
}
Node* Node::getNext(char letter)
{
    return next[letter-97] ;
}
Node** Node::getNext()
{
	return next;
}
class Trie
{
private:
    Node* root ;
public:
    Trie();
    Trie(Node* root);
    void add(string name, string number);
    ~Trie();
    Node* getRoot();
    Node* search(string name);
    void traverse(string& basicStr, Node& trieNode);
    void remove(string name);
    void print(Node* x);
    void record(Node* x);
    void read(Trie& Trie);
};
Trie::Trie()
{
    root = new Node() ;
}
Trie::Trie(Node* root)
{
    this->root = root ;
}
void Trie::print(Node* x)
{
	if(x == nullptr)
		return;
    int i;
    for(i = 0; i < 26; i++)
        if(x->getNext()[i] != nullptr)
        {
            break;
        }
   // cout << i << ' ';
    if(i < 26)
    {
        print(x->getNext()[i]);
    //	cout << x->getNumber() << "\n";
	}
    else
    {
        cout << x->getNumber();
    }
}
char Node::getLetter(){
	return letter;
}
Node* Trie::getRoot()
{
    return root;
}
Node* Trie::search(string name)
{
    //search from this node
    Node* checkNode = this->getRoot();
    //check from first character in string
    for (int i = 0; i < name.length(); i++)
    {
        int index = name[i] - 'a';
        if (checkNode->next[index] == nullptr)
            return nullptr;
            //404 not found
        checkNode = checkNode->next[index];
    }
    //if the node exist and it has a phone number
    if(checkNode != nullptr && checkNode->number != "")
        return checkNode;
}
/*void traverse(string& basicStr, Node& trieNode)
{
    //if the node have a phone number
    //or the node is a leaf
    if(trieNode.number != "" || trieNode.getNext == nullptr){
        //do the function what you want
        //do the function what you want
        //do the function what you want
    }

    for(char backChar = 'a'; backChar <= 'z'; backChar++){
        Node* nextTrieNode = trieNode.next[static_cast<int>(backChar - 'a')];
        //if the letter "basicStr + back" exist
        //which means nextTrieNode is not nullptr
        if(nextTrieNode != nullptr){
            basicStr.push_back(backChar);
            traverse(basicStr, *nextTrieNode);
            basicStr.pop_back;
        }
    }
}*/
void Trie::add(string name, string number)
{
    char* l = &name[0];
    Node* current = root;
    while(current != nullptr)
    {
        if(current->getNext(*l) == nullptr)
        {
            Node* tmp = new Node;
            tmp->setLetter(*l);
            current->setNext(*l,tmp);
        }
        current = current->getNext(*l);
        l++;
        if(l - &name[0] >= name.length())
        {
			current->setNumber(number);
        	break;
        }

    }
}
void Trie::remove(string name)
{
	char* l = &name[0];
    Node* current = root;
    Node* del = root;
    char d = *l;
    int count = 0;
    while(current != nullptr)
    {
    	for(int i = 0; i < 26; i++)
    	{
    		if(current->getNext()[i] != nullptr)
    			count++;
		}
		if(count > 1)
		{
			del = current;
			d = *l;

		}
		if(current->getNumber() != "")
		{
			del = current;
			d = *l;
		}
		count = 0;
		current = current->getNext(*l);
		l++;
		if(l-&name[0] >= name.length())
			break;
    }
    del->setNext(d,nullptr);
}
Trie::~Trie()
{
    delete root ;
}
void Trie::record(Node* x)
{
	if(x == nullptr)
		return;
    int i;
    for(i = 0; i < 26; i++)
        if(x->getNext()[i] != nullptr)
        {
            break;
        }
   // cout << i << ' ';
    if(i < 26)
    {
    	ofstream phoneBook;
    	phoneBook.open("phoneBook.txt",ios::app);
		phoneBook << static_cast<char>(i + 'a');
    	phoneBook.close();
    	record(x->getNext()[i]);
	}
    else
    {
    	ofstream phoneBook;
		phoneBook.open("phoneBook.txt",ios::app);
        phoneBook << " " << x->getNumber() << "\n";
        phoneBook.close();
    }
}

void read(Trie& Trie)
{
	ifstream phoneBook("phoneBook.txt");
	if(phoneBook)	//check file exist or not
	{
		string name;
		string numbers;
		while(phoneBook >> name >> numbers)
		{
			Trie.add(name,numbers);
		}
	}
	phoneBook.close();
}

struct recentp
{
    char name[50]= {0};
    char number[50] = {0};
};

template<class ItemType>
class QNode
{
private:
	ItemType item;
	QNode<ItemType>* next;
public:
	QNode();
	QNode(const ItemType& anItem);
	QNode(const ItemType& anItem, QNode<ItemType>* nextNodePtr);
	~QNode();
	void setItem(const ItemType&anItem);
	void setNext(QNode<ItemType>* nextNodePtr);
	ItemType getItem() const;
	QNode<ItemType>* getNext()const;
};
template <typename ItemType>
QNode<ItemType>::QNode() : next(nullptr) {};
template <typename ItemType>
QNode<ItemType>::QNode(const ItemType& anItem) : item(anItem), next(nullptr) {};
template <typename ItemType>
QNode<ItemType>::QNode(const ItemType& anItem, QNode<ItemType>* nextNodePtr) : item(anItem), next(nextNodePtr) {};
template <typename ItemType>
void QNode<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
};
template <typename ItemType>
void QNode<ItemType>::setNext(QNode<ItemType>* nextNodePtr)
{
	 next = nextNodePtr;
};
template <typename ItemType>
ItemType QNode<ItemType>::getItem() const
{
	return item;
};
template <typename ItemType>
QNode<ItemType>* QNode<ItemType>::getNext()const
{
	return next;
};

template <typename ItemType>
QNode<ItemType>::~QNode()
{
	delete next;
};


template<class ItemType>
class QueueInterface
{
public:
virtual bool isEmpty() const= 0;
virtual void enqueue(const ItemType& newEntry) = 0;
virtual bool dequeue() = 0;
virtual ItemType peekFront() const= 0;
};

template<class ItemType>
class LinkedQueue: public QueueInterface<ItemType>
{
private:
	QNode<ItemType>* backPtr;
	QNode<ItemType>* frontPtr;
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& copy);
	~LinkedQueue();
	void enqueue(const ItemType& newEntry);
	bool dequeue() ;
	bool isEmpty() const;
	ItemType peekFront() const;
};

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : backPtr(nullptr), frontPtr(nullptr) {};

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& copy)
{
	QNode<ItemType>* index = copy.frontPtr;
	while(index != nullptr)
	{
		this->enqueue(index.getItem());
		index = index.getNext();
	}
}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	if(backPtr == frontPtr)
		delete this->backPtr;
	else
	{
		while(this->frontPtr != nullptr)
		{
			QNode<ItemType>* temp = this->frontPtr;
			this->frontPtr = this->frontPtr->getNext();
			delete temp;
		}

	}

}


template<class ItemType>
void LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	QNode<ItemType>* newNodePtr = new QNode<ItemType>(newEntry);
	newNodePtr->setNext(nullptr);
	if(this->isEmpty())//insertion into emptyqueue
	{
		backPtr = newNodePtr;
		frontPtr = newNodePtr;
	}
	else // insertion into nonemptyqueue
	{
		backPtr->setNext(newNodePtr);
		backPtr = newNodePtr;
	}
	return;
}

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;
	if(!isEmpty())
	{
		QNode<ItemType>* nodeToDeletePtr = frontPtr;
		if(frontPtr == backPtr)// A queue of one item?
		{
			frontPtr= nullptr;
			backPtr= nullptr;
			delete nodeToDeletePtr;
		}
		else
		{
			frontPtr = frontPtr->getNext();
			nodeToDeletePtr->setNext(nullptr);
			delete nodeToDeletePtr;
			nodeToDeletePtr = nullptr;
			result = true;
		}
	} // end if(!isEmpty())
		return result;
}

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const
{
	if(this->frontPtr == nullptr and this->backPtr == nullptr)
		return true;
	else
		return false;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront()	const
{
	if(!this->isEmpty())
		return this->frontPtr->getItem();
}

LinkedQueue<recentp> recent ;
LinkedQueue<recentp> recent_saver;
int p_count = 0 ;
HWND textfield;
HWND textfield2;
HWND inputname;
HWND inputnumber;
HWND button;
HWND recentMenu;
HWND recentZero;
HWND menuItem1;
HWND menuItem2;
HWND menuItem3;
HWND menuItem4;
HWND menuItem5;
HWND numItem1;
HWND numItem2;
HWND numItem3;
HWND numItem4;
HWND numItem5;
char textsaved[20] ;
char textsaved2[20];
int mode = 0;
Trie book;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    read(book);
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Awesome Phone Book"),       /* Title Text */
           WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           370,                 /* The programs width */
           300,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
char name_savef[5][50];
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
          /*  textfield = CreateWindow("STATIC",
                                    "Name :",
                                    WS_CHILD | WS_VISIBLE,
                                    130, 23, 50, 20,
                                    hwnd, NULL, NULL, NULL) ;*/

          /*  input = CreateWindow("EDIT", "",
                                 WS_BORDER | WS_VISIBLE | WS_CHILD,
                                 20, 50, 250, 20,
                                 hwnd, NULL, NULL, NULL) ;*/

            button = CreateWindow("BUTTON",
                                "Submit",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                280, 23, 50, 20,
                                hwnd, (HMENU) Submit_Button, NULL, NULL) ;
            HWND droplist = CreateWindow("COMBOBOX", TEXT(""),
                            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED |WS_VISIBLE,
                            20, 20, 100, 100, hwnd, NULL, NULL, NULL) ;
            TCHAR Actions[5][10] = //this is for the droplist
            {
                TEXT("SELECT"), TEXT("Add"), TEXT("Remove"), TEXT("Search"), TEXT("Recent")
            } ;
            for (int k = 0 ; k < 5 ; k++)
            {
                SendMessage(droplist, (UINT) CB_ADDSTRING, (WPARAM) 0, (LPARAM) Actions[k]);
            }
            SendMessage(droplist, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 5) ;

            break;
        }
        case WM_COMMAND:
            if(HIWORD(wParam) == CBN_SELCHANGE)
            {
				PostMessage(inputname, WM_CLOSE, 0, 0);
				PostMessage(inputnumber, WM_CLOSE, 0, 0);
				PostMessage(textfield, WM_CLOSE, 0, 0);
				PostMessage(textfield2, WM_CLOSE, 0, 0);
				PostMessage(recentZero, WM_CLOSE, 0 ,0);
				PostMessage(recentMenu, WM_CLOSE,0,0);
				PostMessage(menuItem1, WM_CLOSE,0,0);
				PostMessage(menuItem2, WM_CLOSE,0,0);
				PostMessage(menuItem3, WM_CLOSE,0,0);
				PostMessage(menuItem4, WM_CLOSE,0,0);
				PostMessage(menuItem5, WM_CLOSE,0,0);
				PostMessage(numItem1, WM_CLOSE,0,0);
				PostMessage(numItem2, WM_CLOSE,0,0);
				PostMessage(numItem3, WM_CLOSE,0,0);
				PostMessage(numItem4, WM_CLOSE,0,0);
				PostMessage(numItem5, WM_CLOSE,0,0);

                int ItemIndex = SendMessage((HWND)lParam, (UINT) CB_GETCURSEL,
                                            (WPARAM) 0, (LPARAM) 0); //you will get the index here
                mode = ItemIndex;
                if(mode == 1)
                {
                	textfield = CreateWindow("STATIC",
                                    "Name :",
                                    WS_CHILD | WS_VISIBLE,
                                    20, 50, 50, 20,
                                    hwnd, NULL, NULL, NULL) ;
                    textfield2 = CreateWindow("STATIC",
                                    "Number:",
                                    WS_CHILD | WS_VISIBLE,
                                    20, 70, 56, 20,
                                    hwnd, NULL, NULL, NULL) ;
                	inputname = CreateWindow("EDIT", "",
                            	WS_BORDER | WS_VISIBLE | WS_CHILD,
                          	 	80, 50, 250, 20,
                        		hwnd, NULL, NULL, NULL) ;
                	inputnumber = CreateWindow("EDIT", "",
                            	WS_BORDER | WS_VISIBLE | WS_CHILD,
                          	 	80, 70, 250, 20,
                        		hwnd, NULL, NULL, NULL) ;
				}
				else if(mode == 2)
				{
					textfield = CreateWindow("STATIC",
                                    "Name :",
                                    WS_CHILD | WS_VISIBLE,
                                    20, 50, 50, 20,
                                    hwnd, NULL, NULL, NULL) ;
					inputname = CreateWindow("EDIT", "",
                            	WS_BORDER | WS_VISIBLE | WS_CHILD,
                          	 	80, 50, 250, 20,
                        		hwnd, NULL, NULL, NULL) ;
				}
				else if(mode == 3)
				{
					textfield = CreateWindow("STATIC",
                                    "Name :",
                                    WS_CHILD | WS_VISIBLE,
                                    20, 50, 50, 20,
                                    hwnd, NULL, NULL, NULL) ;
					inputname = CreateWindow("EDIT", "",
                            	WS_BORDER | WS_VISIBLE | WS_CHILD,
                          	 	80, 50, 250, 20,
                        		hwnd, NULL, NULL, NULL) ;
				}else if(mode == 4){
                    if (p_count > 0)
                    {
                        recentMenu = CreateWindow("STATIC", TEXT("Recent Searches"),
                                    CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                    20, 50, 110, 20, hwnd, NULL, NULL, NULL) ;
                        string n;
                        Node* p;
                        switch (p_count)
                        {
                            case 5:
                            {
                                menuItem5 = CreateWindow("STATIC", TEXT(name_savef[4]),
                                                         CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                         20, 200, 100, 20, hwnd, NULL, NULL, NULL) ;
                                n = name_savef[4];
                                p = book.search(n);
                                char q[20] = {0};
                                if(p != nullptr)
                                {
                                    for(int i = 0; i < p->getNumber().length(); i++)
                                        q[i] = p->getNumber()[i];
                                }
                                numItem5 = CreateWindow("STATIC", TEXT(q),
                                                        CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                        140, 200, 110, 20, hwnd, NULL, NULL, NULL) ;
                            }
                            case 4:
                            {
                                menuItem4 = CreateWindow("STATIC", TEXT(name_savef[3]),
                                                         CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                         20, 170, 100, 20, hwnd, NULL, NULL, NULL) ;
                                n = name_savef[3];
                                p = book.search(n);
                                char q[20] = {0};
                                if(p != nullptr)
                                {
                                    for(int i = 0; i < p->getNumber().length(); i++)
                                        q[i] = p->getNumber()[i];
                                }
                                numItem4 = CreateWindow("STATIC", TEXT(q),
                                                        CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                        140, 170, 110, 20, hwnd, NULL, NULL, NULL) ;
                            }
                            case 3:
                            {
                                menuItem3 = CreateWindow("STATIC", TEXT(name_savef[2]),
                                                         CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                         20, 140, 100, 20, hwnd, NULL, NULL, NULL) ;
                                n = name_savef[2];
                                p = book.search(n);
                                char q[20] = {0};
                                if(p != nullptr)
                                {
                                    for(int i = 0; i < p->getNumber().length(); i++)
                                        q[i] = p->getNumber()[i];
                                }
                                numItem3 = CreateWindow("STATIC", TEXT(q),
                                                        CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                        140, 140, 110, 20, hwnd, NULL, NULL, NULL) ;
                            }
                            case 2:
                            {
                                menuItem2 = CreateWindow("STATIC", TEXT(name_savef[1]),
                                                         CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                         20, 110, 100, 20, hwnd, NULL, NULL, NULL) ;
                                n = name_savef[1];
                                p = book.search(n);
                                char q[20] = {0};
                                if(p != nullptr)
                                {
                                    for(int i = 0; i < p->getNumber().length(); i++)
                                        q[i] = p->getNumber()[i];
                                }
                                numItem2 = CreateWindow("STATIC", TEXT(q),
                                                        CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                        140, 110, 110, 20, hwnd, NULL, NULL, NULL) ;
                            }
                            case 1:
                            {
                                menuItem1 = CreateWindow("STATIC", TEXT(name_savef[0]),
                                                         CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                         20, 80, 100, 20, hwnd, NULL, NULL, NULL) ;
                                n = name_savef[0];
                                p = book.search(n);
                                char q[20] = {0};
                                if(p != nullptr)
                                {
                                    for(int i = 0; i < p->getNumber().length(); i++)
                                        q[i] = p->getNumber()[i];
                                }
                                numItem1 = CreateWindow("STATIC", TEXT(q),
                                                        CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
                                                        140, 80, 110, 20, hwnd, NULL, NULL, NULL) ;
                            }
                        }
                    }else{
                        recentZero = CreateWindow("STATIC",
                                    "No recent results",
                                    WS_CHILD | WS_VISIBLE,
                                    20, 50, 100, 20,
                                    hwnd, NULL, NULL, NULL) ;
                    }
				}
            }
            switch (LOWORD(wParam))
            {
                case Submit_Button: //button gets hit
                    int gwtstat = 0;
					char name[50]={0};
					char number[50]={0};
                    gwtstat = GetWindowText(inputname, &textsaved[0], 50) ;
                    if(mode == 1 && gwtstat != 0)
                    	gwtstat = GetWindowText(inputnumber, &textsaved2[0],50);
                    if (gwtstat == 0)
                    {
                        ::MessageBox(hwnd, "Please Input All Data", "Alert", MB_OK) ;
                    }else{

                        GetWindowText(inputname, name, 50);
                        if(mode == 1)
                       		GetWindowText(inputnumber,number,50);
                    }
                    if(mode == 1) //add
					{
						string n = name;
						string p = number;
						book.add(n,number);
					}
					else if(mode == 2) //remove
					{
						string n = name;
						book.remove(name);
					}
					else if(mode == 3) //search
					{
						string n = name;
						Node* p = book.search(n);
						if(p != nullptr)
						{
							char q[20] = {0};
							for(int i = 0; i < p->getNumber().length(); i++)
								q[i] = p->getNumber()[i];
							::MessageBox(hwnd, q, "Number", MB_OK) ;
							if (p_count == 5)
                            {
                                recent.dequeue();
                                p_count--;
                            }
                            recentp temp;
                            for (int i = 0 ; i < 50 ; i++)
                            {
                                temp.name[i] = name[i];
                                temp.number[i] = q[i];
                            }
                            recent.enqueue(temp);
                            p_count++ ;
                            recent_saver = recent ;
                            for (int i = 0 ; i < p_count ; i++)
                            {
                                for (int j = 0 ; j < 50 ;j++)
                                    name_savef[i][j] = recent.peekFront().name[j];
                                recent.dequeue();
                            }
                            recent = recent_saver ;
						}
						else
							::MessageBox(hwnd, "Not Found", "Alert", MB_OK) ;
					}
                    break ;
            }
            break ;
        case WM_DESTROY:
            book.record(book.getRoot());
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

