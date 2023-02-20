#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;
//----------------------------------------------------------------------------------------------
//Node for The Contacts BST
class node{
public:
string name;

long unsigned int mob;
node *right;
node *left;
};
//----------------------------------------------------------------------------------------------
//Class for the search tree and Operations performed on it. Encapsulating Contacts as a data type
class Contacts{
public:
node *root;
void create_node();
void insert_node(node*, node*,string);
void display(node *);
node * search(string);
node * del(node * root, string key);
node * min(node *);
Contacts(){
root = NULL;
}
}c;
//-----------------------------------------------------------------------------------------------
//function to create contact and insert it
void Contacts::create_node(){
node *check;
node *temp = new node;
cout << "Enter Name:" << endl;
cin >> temp->name;
cout << "Enter Mobile Number: " << endl;
cin >> temp->mob;
temp->left = NULL;
temp->right = NULL;
if(root == NULL){
root = temp;
}
else{
check = search(temp->name);
if(check != NULL){
cout << "Contact with the Same Name Exists!" << endl;
cout << "Contact couldn't be inserted!" << endl;
return;  
}
//string to store name in lowercase for comparison
string s = temp->name;
transform(s.begin(),s.end(),s.begin(),::tolower);
insert_node(root, temp, s);
}
cout << "Record Inserted Successfully" << endl;
}
//------------------------------------------------------------------------------------------------
//function to insert contact into the tree
void Contacts::insert_node(node *root, node *temp,string name){
//string to get root name in lowercase for comparison
string t = root->name;
transform(t.begin(),t.end(),t.begin(),::tolower);
//comparing using lowercase string to avoid Ambiguity
if(name.compare(t) < 0){
if(root->left == NULL)
root->left = temp;
else
insert_node(root->left,temp,name);
}
else{
if(root->right == NULL)
root->right = temp;
else
insert_node(root->right,temp,name);
}
}
//-------------------------------------------------------------------------------------------------
//function to display all contacts in ascending order
void Contacts::display(node *temp){
if(temp->left!=NULL)
display(temp->left);
cout << "Name: " << temp->name << endl;
cout << "Mobile No.: " << temp->mob << endl;
cout << setfill('-') << setw(50) << "-" << endl;
if(temp->right!=NULL)
display(temp->right);
}
//--------------------------------------------------------------------------------------------------
//function to search and delete a contact
node * Contacts::del(node * root, string key){
node * temp;
if(root == NULL){
cout << "Contact " << key << " Does not exist" << endl;
return root;
}
if(key.compare(root->name) < 0){
root->left = del(root->left,key);
return root;
}
if(key.compare(root->name) > 0){
root->right = del(root->right,key);
return root;
}
//if node is leaf node
if(root->right == NULL && root->left == NULL){
temp = root;
delete temp;
return root;
}
//if node has only left child
if(root->right == NULL){
temp = root;
root = root->left;
delete temp;
return root;
}
//if node has only right child
else if(root->left == NULL){
temp = root;
root = root->right;
return root;
}
//if node has both child
temp = min(root->right);
temp->name = root->name;
root->right = del(root->right, temp->name);
return root;
}
//------------------------------------------------------------------------------------------------------
//function to find smallest node in the tree (used in delete)
node * Contacts::min(node * root){
while(root->left!=NULL){
root = root->left;
}
return root;
}
//------------------------------------------------------------------------------------------------------
//function to search for a contact and return its node
node * Contacts::search(string key){
node *temp = root;
int c;
while(temp!=NULL){
c = key.compare(temp->name);
if(c == 0){
return temp;
}
else if(c < 0){
temp = temp->left;
}
else{
temp = temp->right;
}
}
return NULL;
}
//-------------------------------------------------------------------------------------------------------
//function to display User Menu and get return entered by user
int startscreen(){
int choice;
cout  << "\n___________phonebook___________\n";
cout << "\n1.Add a Contact" << endl;
cout << "2.Search" << endl;
cout << "3.Display All" << endl;
cout << "4.Delete" << endl;
cout << "5.Update" << endl;
cout << "6.exit" << endl;
cout << "_________________________________\n";
cin >> choice;
return choice;
}
//-------------------------------------------------------------------------------------------------------
//function to check user choice and perform the requested operation
void operation(){
string key;
node * temp;
while(1){
switch(startscreen()){
case 1:
c.create_node();
break;
case 2:
cout << "Enter Search Key: " << endl;
cin >> key;
temp = c.search(key);
if(temp == NULL)
cout << "Not Found!" << endl;
else{
cout << setfill(' ') <<setw(11) << left << "Name: " << temp->name << endl;;
cout << "Mobile No.: " << temp->mob << endl;
}
break;
case 3:
cout << "All Contacts:" << endl;
c.display(c.root);
break;
case 4:
cout << "Enter the name of contact to be deleted: " << endl;
cin >> key;
c.root = c.del(c.root, key);
cout << "Deleted Successfully" << endl;
break;
case 5:
cout << "Enter the name of the contact you want to update: " << endl;
cin >> key;
temp = c.search(key);
if(temp !=NULL){
cout << setfill(' ') << setw(22) << left << "Current Name: " << temp->name << endl;
cout << setw(22) << left << "Current Mobile No.: " << temp->mob << endl;
cout << setw(22) << left << "Enter New Name: ";
cin >> temp->name;
cout << "Enter New Mobile No. :";
cin >> temp->mob;
cout << "Updated Successfully" << endl;
}
else{
cout << "Contact " << key << " does not exist!" << endl;
}
break;
case 6:
return;
default:
cout << "Enter Appropriate Choice!" << endl;
}
}
}
//-------------------------------------------------------------------------------------------
int main(){
operation();
return 0;
}

