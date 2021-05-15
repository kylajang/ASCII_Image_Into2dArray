#include <iostream>
#include <algorithm>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::transform;
using std::left;
using std::right;
using std::setw;
using std::setprecision;

// Declaring my global variables
const size_t MAX_ALBUMS = 100;
const string ALBUM_TITLE_SENTINEL = "[__END_OF_ALBUMS__]";

// To determine the quantity of total albums
// Prototypes
size_t getAlbumCount(std::string(&titles)[MAX_ALBUMS]);
bool albumExists(int album_number, std::string(&titles)[MAX_ALBUMS]);
bool askAlbumDetails(std::string prompt, std::string& title, int& price, int& quantity);
bool mainMenu(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);
void mainMenuLoop(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);
void createAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);
void deleteAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);
void editAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);
void printAllAlbums(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]);

// the main function
int main(){
  // Declaring my local Variables
  string album_titles[100];
  int album_prices[100];
  int album_quantities[100];

  // parallel arrays
  album_titles[0] = ALBUM_TITLE_SENTINEL;

  // Looping to the main menu
  mainMenuLoop(album_titles, album_prices, album_quantities);

  return 0;
}

// checking the number of albums in the store
size_t getAlbumCount(std::string(&titles)[MAX_ALBUMS])
{
  size_t i;
  for (i = 0; i < MAX_ALBUMS; i++) {
    if(titles[i] == ALBUM_TITLE_SENTINEL){
      break;
    }
  }
  return i;
}

bool albumExists(int album_number, std::string(&titles)[MAX_ALBUMS]){
  // setting conditions for the number of albums
  int count = getAlbumCount(titles);
  if(album_number >= 0 && album_number < count){
    return true;
  }
  // if it doesn't meet the conditions, return false
  else{
    return false;
  }
}

void deleteAllAlbums(std::string(&titles)[MAX_ALBUMS]){
  titles[0] = ALBUM_TITLE_SENTINEL;
}

bool askAlbumDetails(std::string prompt, std::string& title, int& price, int& quantity){
  // Printing the prompt
  cout << prompt << endl;
  cout << "Please enter the album's title, or none to abort. Do not use spaces!" << endl;
  cin >> title;
  if(title == "none"){
      cout << "Album title was " << title << "!" << endl;
      return false;
  }
  // Asking for the price
  cout << "Please enter the album's price: " << endl;
  cin >> price;
  if(price < 1){
    cout << "Album price was invalid!" << endl;
    return false;
  }
  // Asking for the quantity
  cout << "Please enter the quantity of this album that we have in stock: " << endl;
  cin >> quantity;

  return true;
}

// The Main Menu
bool mainMenu(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){

  // Declaring my variables
  string user_input;
  // Creating the main menu
  cout << "*** Music Store Manager Interface - Main Menu ***" << endl;
  cout << endl;
  cout << "There are currently " << getAlbumCount(titles) << " albums in the store."  << endl;
  cout << endl;
  cout << "1. View all albums" << endl;
  cout << "2. Create a new album" << endl;
  cout << "3. Edit an existing album" << endl;
  cout << "4. Delete an album" << endl;
  cout << "Q. Quit this program" << endl;
  cout << endl;
  cout << "Enter your choice: " << endl;
  cin >> user_input;

// Transforms string to lowercase
if(std::isdigit(user_input[0]) == false)
  transform(user_input.begin(), user_input.end(), user_input.begin(), ::tolower);
// User options
if (user_input == "1"){
  printAllAlbums(titles, prices, quantities);
}

else if(user_input == "2"){
  createAlbum(titles, prices, quantities);
}

else if(user_input == "3"){
  editAlbum(titles, prices, quantities);
}
//
else if(user_input == "4"){
  deleteAlbum(titles, prices, quantities);
}

// User selects the option to quit
else if (user_input == "quit" || user_input == "q") {
  cout << "Okay, quitting!" << endl;
  return false;
}
else{
  cout << "Invalid choice!" << endl;
}
return true;
}

// Looping until mainMenu() returns false
void mainMenuLoop(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){

  while (mainMenu(titles, prices, quantities) == true){
  }
}

// Option 1: Viewing all albums
void printAllAlbums(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){
  int size = getAlbumCount(titles);
  for(int i = 0; i < size; i++)
  {
    // Printing the formatted menu
    cout << setw(30) << left << titles[i] << setw(5) << left
    << prices[i] << setw(5) << left << quantities[i] << endl;
  }
}


// Option 2: Creating a new album
void createAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){
  // Declaring my variables
  string prompt, title;
  int price, quantity;
  // Making the argument
  prompt = "Creating a New Album.";
  // calling to the askAlbumDetails function
  bool call = askAlbumDetails(prompt, title, price, quantity);
  // If the function returns false
  if(call == false){
    cout << "Aborting album creation!" << endl;
    return;
  }
  // If the store is already full
  int full = getAlbumCount(titles);
  if(full == MAX_ALBUMS - 1){
    cout << "Sorry! The store is full!" << endl;
    return;
  }
  // setting our array to a new index
  titles[full + 1] = ALBUM_TITLE_SENTINEL;
  titles[full] = title;
  prices[full] = price;
  quantities[full] = quantity;
}

// Option 3: Editing an existing album
void editAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){
  // Declaring my variables for this function
  int user_input;
  string prompt;
  int price, quantity;
  string title;
  // Printing user output for option 3
  cout << "Enter album number to edit: " << endl;
  cin >> user_input;
  // Calling to albumExists() function
  bool call = albumExists(user_input, titles);
  // Checking if the user has a valid input
  if(call == false){
    cout << "Invalid album!" << endl;
    return;
  }
  // Making the argument
  prompt = "Editing an Album.";
  bool second_call = askAlbumDetails(prompt, title, price, quantity);
    if(second_call == false){
    cout << "Aborting edit!" << endl;
    return;
    }
  // setting our array to a new index
  titles[user_input] = title;
  prices[user_input] = price;
  quantities[user_input] = quantity;
  cout << "Edit successfull!" << endl;
}

// Option 4: Deleting Albums
void deleteAlbum(string(&titles)[MAX_ALBUMS], int(&prices)[MAX_ALBUMS],int(&quantities)[MAX_ALBUMS]){
  // Delcaring my variables for this function
  int user_input;

  // Printing the message for option 4
  cout << "Enter the album number to delete: " << endl;
  cin >> user_input;
  // Calling to albumExists() function
  bool call = albumExists(user_input, titles);
  // Checking if the user has a valid input
  if(call == false){
    cout << "Invalid album!" << endl;
    return;
  }

  for(int i = user_input; i < 100 - 1; i++)
  {
    // shifting over data to the left
    titles[i] = titles[i+1];
    prices[i] = prices[i+1];
    quantities[i] = quantities[i+1];
    if(titles[i] == ALBUM_TITLE_SENTINEL)
      break;
  }
  cout << "Delete successfull!" << endl;
}
