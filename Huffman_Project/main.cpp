#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

map<char,string> HuffmanCode;

void generateCode(Node* root,string str){
    if(!root) return;

    if(!root->left && !root->right){
        HuffmanCode[root->ch] = str;
    }
    generateCode(root->left,str + "0");
    generateCode(root->right,str + "1");
}

void compressedFile(string inputFile,string outputFile, map<char,string>& codes){
    ifstream input(inputFile);

    ofstream output(outputFile,ios::binary);

    if(!input || !output){
        cout<<"Error opening Files !!"<<endl;
        return;
    }

    char ch;
    unsigned char buffer = 0;
    int count = 0;

    while (input.get(ch)){
        string code = codes[ch];
        for(char bit :code){
            buffer = buffer <<1;
            if(bit =='1'){
                buffer = buffer | 1;
            }

            count++;

            if(count == 8){
                output.put(buffer);
                buffer = 0;
                count = 0;
            }
        }
    }
    if(count > 0){
        buffer = buffer << (8-count);
        output.put(buffer);
    }
    input.close();
    output.close();
    cout<<"Compressed file written successfully... "<<endl;
}

void decompressedFile(string inputFile,Node* root){
    ifstream input(inputFile,ios::binary);

    if(!input){
        cout<<"Error opening compressed File!!"<<endl;
        return;
    }

    Node* current = root;
    char byte;
    int totalChars = root->freq;

    cout<<"\n --Decomressing File ---"<<endl;

    while(input.get(byte)){
        for(int i = 7; i>=0; i--){
            int bit = (byte>>i) & 1;

            if(bit == 0){
                current = current->left;

            } else {
                current = current->right;
            }

            if(!current->left && !current -> right){
                cout<<current->ch;
                current = root;

                totalChars--;
                if(totalChars == 0) break;
            }
        }
        if(totalChars == 0) break;

    }
    input.close();
    cout<<"\n---Decompressed Complete --"<<endl;
}

int main()
{
    ifstream inputfile("input.txt");

    if (!inputfile)
    {
        cout << "Error : File not Found !!" << endl;
        return 1;
    }

    map<char, int> freqMap;
    char ch;
    while (inputfile.get(ch))
    {
        freqMap[ch]++;
    }
    inputfile.close();

    priority_queue<Node *, vector<Node *>, Compare> minHeap;

    for (auto pair : freqMap)
    {
        Node *newNode = new Node(pair.first, pair.second);
        minHeap.push(newNode);
    }
    cout << "Total Unique Characters : " << freqMap.size() << endl;

    if (!minHeap.empty())
    {
        Node *top = minHeap.top();
        cout << "Smallest frequency character : '" << top->ch << "' (Count: " << top->freq << ")" << endl;
    }

    while (minHeap.size() >1)
    {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* parent = new Node('$',left->freq + right -> freq);

        parent -> left = left;
        parent -> right = right;

        minHeap.push(parent);
    }
    Node* root  = minHeap.top();

    cout<<"Huffman Tree Built !!"<< endl;

    
    cout<<"Root Frequency (Total Characters) : "<< root-> freq << endl;


    generateCode(root,"");

    cout<<"Huffman Codes: "<<endl;

    for(auto pair :HuffmanCode){
        cout<<pair.first << ": "<<pair.second<<endl;
    }
     string encoded = "";

     cout<<"\nOrignal String\n";

     ifstream readAgain("input.txt");

     while (readAgain.get(ch))  
     {  
        cout << ch;
        encoded += HuffmanCode[ch];

     }
     readAgain.close();

     cout<<"\nEncoded String :\n"<<encoded<<endl;

     int total = root->freq;

     int orignalBits = total *8;
     int compressed = encoded.length();

     cout<<"Orignal : " <<orignalBits<<endl;
     cout<<"Compressed : " <<compressed<<endl;

     cout<<"\n Compressing file to 'output.huff' ..."<<endl;
     compressedFile("input.txt","output.huff",HuffmanCode);
    
     decompressedFile("output.huff",root);
    
    return 0;
}
