// Question 4. Write a program to implement the Bellman-Ford algorithm to find the shortest paths 
from a given source node to all other nodes in a graph.   


#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int data;
    int weight;
    Node* next;
    Node(int ele, int Weight) {
        data = ele;
        weight = Weight;
        next = NULL;
    }
};

class LinkedList {
    Node* head;
public:
    LinkedList() { head = NULL; }
    void addToHead(int ele, int weight);
    Node* search(int ele);
    void display();
    bool isEmpty() { return head == NULL; }
    Node* getHeadNode() { return head; }
};

void LinkedList::addToHead(int ele, int weight) {
    Node* n = new Node(ele, weight);
    if (isEmpty()) {
        head = n;
    } else {
        n->next = head;
        head = n;
    }
}

Node* LinkedList::search(int ele) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == ele)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void LinkedList::display() {
    cout << "[ ";
    Node* temp = head;
    while (temp != NULL) {
        cout << "{v:" << temp->data << ",w:" << temp->weight << "} ,";
        temp = temp->next;
    }
    cout << "\b ]\n";
}

class DirectedGraph {
    int vertex;
    LinkedList* adjList;
public:
    DirectedGraph(int n) {
        vertex = n;
        adjList = new LinkedList[vertex];
    }
    ~DirectedGraph() { delete[] adjList; }
    void addEdge(int u, int v, int weight);
    int bellmanFord(int source, int destination);
    void display();
};

void DirectedGraph::addEdge(int u, int v, int weight) {
    if (adjList[u].search(v) == NULL)
        adjList[u].addToHead(v, weight);
}

int DirectedGraph::bellmanFord(int source, int destination) {
    // Distance array to store shortest distances
    int* dist = new int[vertex];
    
    // Initialize distances
    for (int i = 0; i < vertex; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    // Relaxation step: Iterate vertex-1 times
    for (int k = 0; k < vertex - 1; k++) {
        bool updated = false;
        
        // Check all vertices and their adjacent edges
        for (int u = 0; u < vertex; u++) {
            Node* current = adjList[u].getHeadNode();
            
            while (current != NULL) {
                int v = current->data;
                int weight = current->weight;
                
                // Relaxation condition
                if (dist[u] != INT_MAX && 
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    updated = true;
                }
                
                current = current->next;
            }
        }
        
        // If no updates in an iteration, we can break early
        if (!updated) break;
    }

    // Check for negative weight cycles
    for (int u = 0; u < vertex; u++) {
        Node* current = adjList[u].getHeadNode();
        
        while (current != NULL) {
            int v = current->data;
            int weight = current->weight;
            
            if (dist[u] != INT_MAX && 
                dist[u] + weight < dist[v]) {
                // Negative weight cycle detected
                delete[] dist;
                return -1;
            }
            
            current = current->next;
        }
    }

    // Get the shortest path to destination
    int result = dist[destination];
    
    // Clean up
    delete[] dist;

    // Return result or -1 if no path exists
    return (result == INT_MAX ? -1 : result);
}

void DirectedGraph::display() {
    for (int i = 0; i < vertex; i++) {
        cout << "Adjacency List of vertex " << i << ": ";
        adjList[i].display();
    }
}

int main() {
    int n;
    cout << "Enter Number of vertices in the Graph: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of vertices!" << endl;
        return 0;
    }

    DirectedGraph A(n);
    int ch = 0;
    while (ch != 4) {
        int u, v, weight;
        cout << "\nMenu:\n"
             << "1. Add Edge\n"
             << "2. Display Graph\n"
             << "3. Run Bellman-Ford\n"
             << "4. Exit\n"
             << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Enter edge (u, v) and its weight: ";
                cin >> u >> v >> weight;
                if ((u < n && u >= 0) && (v < n && v >= 0)) {
                    A.addEdge(u, v, weight);
                } else {
                    cout << "Invalid vertices!" << endl;
                }
                break;
            case 2:
                A.display();
                break;
            case 3:
                cout << "Enter source and destination vertices: ";
                cin >> u >> v;
                if ((u < n && u >= 0) && (v < n && v >= 0)) {
                    int result = A.bellmanFord(u, v);
                    if (result == -1) {
                        cout << "No path exists or negative weight cycle detected from vertex " << u << " to vertex " << v << endl;
                    } else {
                        cout << "Shortest Path from vertex " << u << " to vertex " << v << " : " << result << endl;
                    }
                } else {
                    cout << "Invalid vertices!" << endl;
                }
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
