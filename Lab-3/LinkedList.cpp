#include <iostream>

using namespace std;

struct Node 
{
    int data;
    Node* next;
};

class LinkedList 
{
    Node* head;
    Node* tail;

    public:
    LinkedList() 
    {
        this->head = NULL;
        this->tail = NULL;
    }

    ~LinkedList()
    {
        cout << "[OPERATION] destroying list to free up memory" << endl;
        this->destroyList();
    }

    void insertAtBeggining(int value) 
    {
        // Dynamically allocate memory for a new node
        Node* newNode = new Node();
        newNode->data = value;      // Use the passed value
        newNode->next = this->head; // Make its next value point to the old head
        this->head = newNode;       // Update the head to the new node we just added
    }

    void insertAtEnd(int value) 
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;       // There is no node after this, adding to end

        if (this->head == NULL)     // If the List is empty
        {
            this->head = newNode;   // Just make the head this Node
        } 
        else 
        {
            Node* temp = this->head;
            while (temp->next != NULL)  // Traverse to the last node
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void insertAtPosition(int value, int position)
    {
        Node* newNode = new Node();
        newNode->data = value;
        
        if (position == 1)      // Add Node at head
        {
            newNode->next = this->head;
            this->head = newNode;
            return;
        }

        Node* temp = this->head;
        for (int i = 1; i < position - 1 && temp != NULL; i++)
        {           // Traverse to next Node till at location just behind position
            temp = temp->next;
        }

        if (temp == NULL)       // Invalid position handling
        {
            cout << "[ERROR] position out of bounds for insertion" << endl;
        }
        else 
        {
            newNode->next = temp->next;     // Link the new node to the next node
            temp->next = newNode;           // Link previous node to the new one
        }
    }

    void deleteFromBeggining()
    {
        if (this->head == NULL)
        {
            cout << "[ERROR] cannot delete from beginning, list is empty" << endl;
            return;
        }
        Node* temp = this->head;      // Save the current head
        this->head = this->head->next;      // Point head to the next node
        delete temp;            // Free memory
    }

    void deleteFromEnd()
    {
        if (this->head == NULL)
        {
            cout << "[ERROR] cannot delete from end, list is empty" << endl;
            return;
        }
        if (this->head->next == NULL)     // If only one node is left
        {
            delete this->head;
            this->head = NULL;
            return;
        }
        Node* temp = this->head;
        while (temp->next->next != NULL)
        {       // Traverse to the second last node
            temp = temp->next;
        }
        delete temp->next;      // Free up last node memory
        temp->next = NULL;      // Update it to point to NULL
    }

    void deleteFromPosition(int position)
    {
        if (this->head == NULL)
        {
            cout << "[ERROR] cannot delete from Position " << position << ", list is empty" << endl;
            return;
        }
        if (position == 1)      // Delete from first position
        {
            Node* temp = this->head;
            this->head = this->head->next;
            delete temp;
            return;
        }
        Node* temp = this->head;
        for (int i = 1; i < position - 1 && temp != NULL; i++)
        {
            temp = temp->next;  // Traverse to the node before the one to be deleted
        }
        if (temp == NULL || temp->next == NULL)
        {
            cout << "[ERROR] cannot delete from position " << position << ", out of bounds" << endl;
            return;
        }
        Node* nodeToDelete = temp->next;    // Store the node to free memory later
        temp->next = temp->next->next;      // Update the link to remove the node
        delete nodeToDelete;                // Free up memory
    }

    void displayList()
    {
        if (this->head == NULL)
        {
            cout << "[ERROR] cannot display, list is empty" << endl;
            return;
        }

        Node* temp = this->head;
        while (temp != NULL) 
        {
            cout << temp->data << " -> ";
            temp = temp->next;      // Move to the next node
        }
        cout << "NULL" << endl;     // Show the end of the list
    }

    int numberOfNodes()
    {
        int count = 0;
        Node* temp = this->head;
        while (temp != NULL) 
        {
            count++;
            temp = temp->next;      // Move to the next node
        }
        return count;
    }

    void destroyList() 
    {
        Node* temp;
        while (this->head != NULL)
        {
            temp = this->head;            // Store the head to delete later
            this->head = this->head->next;      // Move forward
            delete temp;            // Delete the stored head
        }
        cout << "[SUCCESS] list destroyed" << endl;
    }

    void insertAtPosition3(int value) 
    {
        Node* newNode = new Node();
        newNode->data = value;

        Node* temp = this->head;
        for (int i = 1; i < 2 && temp != NULL; i++)
        {           // Traverse to next Node till at location just behind position 3
            temp = temp->next;
        }
        newNode->next = temp->next;     // Link the new node to the next node
        temp->next = newNode;           // Link previous node to the new one
    }
};

// Always subject to change: DO NOT make any contributions in the main function
int main()      // Test driver for list class
{
    // Create a linked list
    LinkedList* list1 = new LinkedList();

    // Insert Nodes at head
    list1->insertAtBeggining(7);
    list1->insertAtBeggining(4);
    list1->insertAtBeggining(12);
    list1->insertAtBeggining(8);
    cout << endl;

    bool keepRunning = true;
    while (keepRunning) 
    {
        string userChoiceStr;
        cout << "____ Linked-List Operations Menu ____" << endl;
        cout << "[1] Insert Nodes at the Head" << endl;
        cout << "[2] Insert Node at 3rd position" << endl;
        cout << "[3] Display list" << endl;
        cout << "[4] Delete from a position" << endl;
        cout << "[5] Count number of Nodes in the list" << endl;
        cout << "[6] Exit" << endl;
        cout << "\nChoice: ";

        cin >> userChoiceStr;

        // Check if the input is a number
        bool invalidInput = false;
        for (int i = 0; i < userChoiceStr.length(); i++) 
        {
            if (!isdigit(userChoiceStr[i])) 
            {
                cout << "Invalid input. Please enter a number." << endl;
                invalidInput = true;
                break;
            }
        }
        if (invalidInput) 
        {
            continue;
        }
        int userChoice = stoi(userChoiceStr);

        switch (userChoice) 
        {
            case 1:
                cout << "Enter value to insert: ";
                
                // Check if the input is a number
                invalidInput = false;
                userChoiceStr = "";
                cin >> userChoiceStr;
                for (int i = 0; i < userChoiceStr.length(); i++) 
                {
                    if (!isdigit(userChoiceStr[i])) 
                    {
                        cout << "Invalid input. Please enter a number." << endl;
                        invalidInput = true;
                        break;
                    }
                }
                if (invalidInput) 
                {
                    break;
                }
                userChoice = stoi(userChoiceStr);
                list1->insertAtBeggining(userChoice);
                cout << "Value " << userChoice << " inserted at head." << endl;
                break;
            case 2:
                cout << "Enter value of Node to insert at 3rd position: ";
                cin >> userChoice;
                list1->insertAtPosition3(userChoice);
                cout << "Value " << userChoice << " inserted at position 3." << endl;
                break;
            case 3:
                list1->displayList();
                break;
            case 4:
                cout << "Enter position of node to be deleted: ";
                cin >> userChoice;
                list1->deleteFromPosition(userChoice);
                cout << "Position " << userChoice << " deleted from list" << endl;
                break;
            case 5:
                cout << "The number of nodes in the list is: " << list1->numberOfNodes() << endl;
                break;
            case 6:
                cout << "exiting..." << endl;
                keepRunning = false;
                break;
            default:
                cout << "Invalid Input." << endl;
        }
        cout << endl;
    }
}
