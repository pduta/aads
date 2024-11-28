// Question 3. Write a program to determine the minimum spanning tree of a graph using Kruskal’s algorithm.



#include <iostream>
#include <vector>
using namespace std;

struct UnionNode {
    int data;
    UnionNode* parent;
    int size;

    UnionNode(int ele){
        data = ele;
        parent = this;
        size = 1;
    } 
};

class UnionFind {
    std::vector<UnionNode*> pointersVector;

public:
    void makeUnionFind(int vertices) {
        for (int i = 0; i < vertices; i++) {
            pointersVector.push_back(new UnionNode(i)); 
        }
    }

    int find(int val) {
        UnionNode* node = pointersVector[val];
        if (node->parent != node) {
            node->parent = pointersVector[find(node->parent->data)]; 
        }
        return node->parent->data;
    }

    void Union(int s1, int s2) {
        UnionNode* root1 = pointersVector[find(s1)];
        UnionNode* root2 = pointersVector[find(s2)];

        if (root1 != root2) {
            if (root1->size < root2->size) {
                root1->parent = root2;
                root2->size += root1->size; 
            } else {
                root2->parent = root1; 
                root1->size += root2->size;
            }
        }
    }

    void display() {
        for (int i = 0; i < pointersVector.size(); i++) {
            cout << i << " : " << find(i) << endl; 
        }
    }

    ~UnionFind() {
        for (auto node : pointersVector) {
            delete node; 
        }
    }
};

struct Node{
    int source;
    int destination;
    int weight;
    Node * next;
    Node(int Source,int Destination,int Weight){
        destination= Destination;
        weight = Weight;
        source = Source;
        next=NULL;
    }
};

class LinkedList{
    Node * head;
    public:
    LinkedList(){
        head=NULL;
    }
    Node * getHeadNode(){return head;}
    bool isEmpty(){return head==NULL;}
    void addToHead(int source,int destination,int weight);
    Node * search(int ele);
    void display();
};

void LinkedList::addToHead(int source,int destination,int weight){
    Node * n = new Node(source,destination,weight);    
    if(isEmpty()){
        head = n;
    }
    else{
        n->next=head;
        head = n;
    }
}


Node * LinkedList::search(int ele){
    Node * temp =head;
    while(temp!=NULL){
        if(temp->source==ele)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

void LinkedList::display(){
    cout<<"[";
    Node * temp = head;
    while(temp!=NULL){
        cout<<"{"<<temp->source<<" ,"<<temp->destination<<","<<temp->weight<<"},";
        temp=temp->next;
    }
    cout<<"\b]\n";
}

class Graph{
    int vertex;
    LinkedList * adjList;
    public:
    Graph(int n){
        vertex = n;
        adjList = new LinkedList[vertex];
    }
    void addEdge(int u,int v,int weight);
    void display();
    void kruskal();
};




void Graph::addEdge(int u,int v,int weight){
    if(adjList[u].search(v)==NULL)
        adjList[u].addToHead(u,v,weight);

    if(adjList[v].search(u)==NULL)
        adjList[v].addToHead(v,u,weight);
}

void Graph::display(){
    for (int i = 0; i < vertex; i++)
    {
        cout<<"List of vertex "<<i<<": ";
        adjList[i].display();
    }
}
void Graph::kruskal() {
    std::vector<Node*> edges;

    for (int i = 0; i < vertex; i++) {
        Node* temp = adjList[i].getHeadNode();
        while (temp != NULL) {
            edges.push_back(temp);
            temp = temp->next;
        }
    }

    for (int i = 1; i < edges.size(); i++) {
        Node* key = edges[i];
        int j = i - 1;
        while (j >= 0 && edges[j]->weight > key->weight) {
            edges[j + 1] = edges[j];
            j = j - 1;
        }
        edges[j + 1] = key;
    }

    UnionFind uf;
    uf.makeUnionFind(vertex);

    int mstWeight = 0;
    cout << "MST: [";
    for (auto edge : edges) {
        if (uf.find(edge->source) != uf.find(edge->destination)) {
            mstWeight += edge->weight;
            cout << "\n\t{" << edge->source << "," << edge->destination << "," << edge->weight << "}";
            uf.Union(edge->source, edge->destination);
        }
    }
    cout << "\n]";
    cout << "\nMinimum Cost: " << mstWeight;
}




int main(){
    cout<<"Enter Number of vertex in the Graph:\n";
    int n;
    cin>>n;

    Graph A(n);
    
    while(true){
        int u,v,weight;
        cout<<"\nEnter 1 to addEdge\n"
        <<"Enter 2 to display graph\n"
        <<"Enter 3 to find mst using Kruskal\n"
        <<"Enter 4 to exit\n"
        <<"enter choice:";
        int ch;
        cin>>ch;
        switch (ch)
        {
        case 1:
            cout<<"\nEnter edge u and v and weight : ";
            cin>>u>>v>>weight;
            if((u<n && u>=0) && (v<n && v>=0)){
                A.addEdge(u,v,weight);}
            break;
        case 2:
            A.display();
            break;
        case 3:
            A.kruskal();
            break;
        case 4:
            exit(0);
        default:
            break;
        }
    }
}
