#include "menu.h"

TreeNode tree[MAX_NODES];                  //Static declaration of the working menu array
int nextNodeIndex = 0;                     //First free index
int childIndices[MAX_NODES][MAX_CHILDREN]; //Array used for child indexes
int selectedMenuIndex = 0;                 //The Selected Menu

void InitMenu()
{
	int root = addNode("Root", -1, (int[]){1, 2, 3, 4, 5, 6, 7}, 7);  //Creating the root of the menu
	int Option1 = addNode("Option 1", root, (int[]){8, 9, 10}, 3);    //Adding nodes and leaves to the menu
	int Option2 = addNode("Option 2", root, (int[]){11, 12}, 2);      //Indexation should be calculated manually for non leaf nodes
	addLeaf("Option 3", root, exampleFunction);
	addLeaf("Option 4", root, exampleFunction);
	addLeaf("Option 5", root, exampleFunction);
	addLeaf("Option 6", root, exampleFunction);
	addLeaf("Option 7", root, exampleFunction);

	addLeaf("Option 1.1", Option1, exampleFunction); //Adding sub menu to Option 1
	addLeaf("Option 1.2", Option1, exampleFunction);
	addLeaf("Option 1.3", Option1, exampleFunction);

	addLeaf("Option 2.1", Option2, exampleFunction); //Adding sub menu to Option 2
	addLeaf("Option 2.2", Option2, exampleFunction);
}

void printChildren(int index) { // Prints all the children of index node

	// Gets the array of the children and their quantity
	int* children = getChildren(index);
	int total_children = tree[index].numChildren;

	// Ensure rotary counter stays within valid range
	rotary_encoder_counter = (rotary_encoder_counter < 0) ? 0 :
							(rotary_encoder_counter >= total_children) ? total_children - 1 :
							rotary_encoder_counter;

	// Calculate scroll offset
	int max_offset = (total_children > 4) ? (total_children - 4) : 0;
	int offset = rotary_encoder_counter - 3;
	offset = (offset < 0) ? 0 : (offset > max_offset) ? max_offset : offset;

	// Display visible items
	for (int row = 0; row < 4; row++) {
		int item_idx = offset + row;
		lcd_put_cur(row, 0);
		if (item_idx >= total_children) continue;

		// Draw cursor
		lcd_put_cur(row, 0);
		lcd_send_string((item_idx == rotary_encoder_counter) ? ">" : " ");

		// Draw menu label
		lcd_send_string(tree[children[item_idx]].label);
	}
}

void addLeaf(const char* label, int parentIndex, LeafFunc func) {
    if (nextNodeIndex >= MAX_NODES) return; //-1; // Array full

    TreeNode* node = &tree[nextNodeIndex];
    snprintf(node->label, 20, "%s", label);
    node->numChildren = 0;
    node->parentIndex = parentIndex;
    node->funcOrChildren = (void*)func; // Store function pointer
    nextNodeIndex++;
    //return nextNodeIndex++;
}

int addNode(const char* label, int parentIndex, int children[], int numChildren) {
    if (nextNodeIndex >= MAX_NODES || numChildren > MAX_CHILDREN) return -1;

    TreeNode* node = &tree[nextNodeIndex];
    snprintf(node->label, 20, "%s", label);
    node->numChildren = numChildren;
    node->parentIndex = parentIndex;

    // Store child indices in global array
    for (int i = 0; i < numChildren; i++) {
        childIndices[nextNodeIndex][i] = children[i];
    }
    node->funcOrChildren = &childIndices[nextNodeIndex]; // Points to child indices

    return nextNodeIndex++;
}

int* getChildren(int nodeIndex) {
    if (tree[nodeIndex].numChildren == 0) return NULL;
    return (int*)tree[nodeIndex].funcOrChildren;
}
void PrintMenu()
{
	printChildren(selectedMenuIndex);
	if(buttonState==1)
	{
		OpenMenu();
	}
	if(buttonState==2)
	{
		CloseMenu();
	}
	buttonState = 0;
}
void OpenMenu()  //Opens the selected option from the rotary encoder input
{
	lcd_clear();
	int* children = getChildren(selectedMenuIndex);
	if(isLeaf(children[rotary_encoder_counter]))
	{
		executeLeafFunction(children[rotary_encoder_counter]);
        rotary_encoder_counter = 0;
	}
	else{
		selectedMenuIndex = children[rotary_encoder_counter];
		rotary_encoder_counter = 0;
	}
}
void CloseMenu() //Goes back to the parent of the selected node
{
	//Checks if the node isn't the root node
	if((tree[selectedMenuIndex].parentIndex) != -1){
		lcd_clear();
		selectedMenuIndex = tree[selectedMenuIndex].parentIndex;
	}
}
void executeLeafFunction(int nodeIndex) {
    if(tree[nodeIndex].funcOrChildren) {
        ((LeafFunc)tree[nodeIndex].funcOrChildren)();
    }
}
void exampleFunction()
{
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Function executed!");
	HAL_Delay(1000);
	lcd_clear();
}
uint8_t isLeaf(int selectedIndex)
{
	if(tree[selectedIndex].numChildren == 0)
	{
		return 1;
	}
	else{
		return 0;
	}
}
