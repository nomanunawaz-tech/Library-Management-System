#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;
struct BookIssue
 {
  int isbn;
  int year;
  int month;
  int day;
  int fine;
 };
struct books
 {
  int isbn;
  string title;
  string author;
  string category;
  int price;
  int issuedPersonID;
  BookIssue bookIssue;
  bool available;
 };

struct members
 {
  string userName;
  string password;
  string role;
  BookIssue bookIssue;
  BookIssue issuedBook;
 };
char mainMenu();
void header();
void clearScreen();

void signUp(members member[], int &userCount);
void signIn(members member[], books book[], int &bookCount, int &userCount);
string checkUserRole(string userName, string userPassword, members member[], int userCount);

void librarionInterface(members member[], books book[], int &bookCount, int &userCount);
void bookManagement(members member[], books book[], int &bookCount, int &userCount);
void addBook(books book[], int &bookCount);
void sortBook(books book[], int &bookCount);
void deleteBook(books book[], int &bookCount);

void viewAllBooks(books book[], int &bookCount);
void viewAllAvailableBooks(books book[], int &bookCount);
void notAvailableBooks(members member[], books book[], int &bookCount, int &userCount);
int searchBook(books book[], int &bookCount);
bool isBookMatch(int i, string title, books book[]);
void bookHeader();
void showBook(int idx, books book[]);

void circulationOfBooks(members member[], books book[], int &bookCount, int &userCount);
void issueBook(members member[], books book[], int &bookCount, int &userCount);
void returnBook(members member[], books book[], int &bookCount, int &userCount);

void memberManagement(members member[], books book[], int &bookCount, int &userCount);
void removeMember(members member[], int &userCount);
void viewAllMembers(members member[], int userCount);
void memberHeader();
void showMember(int idx, members member[]);
void personalInformation(members member[], books book[], int bookCount);

void memberInterface(members member[], books book[], int &bookCount, int &userCount);
int searchMember(members member[], int userCount);
bool isMemberMatch(int i, string userName, members member[]);
int currentUserID = -1;


void loadBooks(books book[], int &bookCount);
void loadMembers(members member[], int &userCount);
void saveBooks(books book[], int &bookCount);
void saveMembers(members member[], int &userCount);

int daysBetween(int y1, int m1, int d1, int y2, int m2, int d2);

int main()
 {
  books book[100];
  members member[100];
  int bookCount = 0, userCout = 0;
  loadMembers(member, userCout);
  loadBooks(book, bookCount);

  char choice = ' ';
  do
  {
    clearScreen();
    choice = mainMenu();
    switch (choice)
    {
    case '1':
      signIn(member, book, bookCount, userCout);
      break;
    case '0':
    {
      cout << "\t\tPress any key to exit main menu:";
      getch();
      return 1;
    }
    }
  } while (choice != '0');
 }

void header()
 {
  cout << "\033[1;37;44m";
  cout << "\t\t#################################################################################" << endl;
  cout << "\t\t#################################################################################" << endl;
  cout << "\033[0m\n"
       << endl;
  cout << "                         LLL              MMMM          MMMM              SSSSSSSSS       " << endl;
  cout << "                         LLL             MM  MM        MM  MM            SS       SS      " << endl;
  cout << "                         LLL             MM   MM      MM   MM            SS               " << endl;
  cout << "                         LLL             MM    MM    MM    MM             SSSSSSSSS       " << endl;
  cout << "                         LLL             MM     MM  MM     MM                     SS        " << endl;
  cout << "                         LLL             MM      MMMM      MM            SS       SS      " << endl;
  cout << "                         LLLLLLLLLL      MM       MM       MM             SSSSSSSSS     " << endl
       << endl;
  cout << "\033[1;37;44m";
  cout << "\t\t#################################################################################" << endl;
  cout << "\t\t#################################################################################\n";
  cout << "\033[0m\n"
       << endl;
}
void clearScreen()
{
  system("cls");
  header();
  cout << endl
       << endl
       << endl;
}
char mainMenu()
{
  char choice;
  cout << "\n\n\n\n\n\033[1;37;44m============ MAIN MENU ============\033[0m";
  cout << "\n\n        SELECT ONE";
  cout << "\n\n        1. for Sign In.";
  cout << "        (For test    Username: noman     Password: 1234 )";
  cout << "\n        0. to exit.";
  cout << "\n\n        choice :";
  choice = getch();
  clearScreen();
  return choice;
}
void librarionInterface(members member[], books book[], int &bookCount, int &userCount)
{
  char choice = ' ';
  while (choice != '0')
  {
    clearScreen();
    cout << "\n       \033[1;37;44m======== LIBRARION MENU ========\033[0m";
    cout << "\n\n             1.Book Management";
    cout << "\n             2.Member Management";
    cout << "\n             3.Circulation";
    cout << "\n             4.Personal Information";
    cout << "\n             0.Exit";
    cout << "\n\n             choice :";
    choice = getch();
    switch (choice)
    {
    case '1':
      bookManagement(member, book, bookCount, userCount);
      break;
    case '2':
      memberManagement(member, book, bookCount, userCount);
      break;
    case '3':
      circulationOfBooks(member, book, bookCount, userCount);
      break;
    case '4':
      personalInformation(member, book, bookCount );
      break;
    }
  }
}
void memberInterface(members member[], books book[], int &bookCount, int &userCount)
{
  char choice = ' ';
  while (choice != '0')
  {
    clearScreen();
    cout << "\n\t\t1.View all books:";
    cout << "\n\t\t2.View available books";
    cout << "\n\t\t3.Search a book";
    cout << "\n\t\t4.Personal Information";
    cout << "\n\t\t0Exit.";
    cout << "\n\n\t\tChoice";

    choice = getch();
    switch (choice)
    {
    case '1':
      viewAllBooks(book, bookCount);
      break;
    case '2':
      viewAllAvailableBooks(book, bookCount);
      break;
    case '3':
      searchBook(book, bookCount);
      break;
    case '4':
            personalInformation(member, book, bookCount );
      break;  
    default:
      return;
    }
  }
}
void addBook(books book[], int &bookCount)
{
addBook:
  clearScreen();
  cout << "     =====ADD NEW BOOKS=====" << endl
       << endl;
  cout << "        Enter book ISBN   :";
  cin >> book[bookCount].isbn;
  cout << "        Enter book title  :";
  getline(cin >> ws, book[bookCount].title);
  cout << "        Enter author name :";
  getline(cin >> ws, book[bookCount].author);
  cout << "        Enter book price  :";
  cin >> book[bookCount].price;
  cout << "\n          Select category    :" << endl
       << endl;
  cout << "             1.ISLAMIC"
       << "             2.HISTORY    "
       << "             3.GEOGRAPHY"
       << "             4.SCIENCE"
       << "             5.SOCIAL";
  char choice = getch();
  switch (choice)
  {
  case '1':
    book[bookCount].category = "ISLAMIC";
    break;
  case '2':
    book[bookCount].category = "HISTORY";
    break;
  case '3':
    book[bookCount].category = "GEOGRAPHY";
    break;
  case '4':
    book[bookCount].category = "SCIENCE";
    break;
  case '5':
    book[bookCount].category = "SOCIAL";
    break;
  default:
    book[bookCount].category = "SOCIAL";
  }
  book[bookCount].available = true;
  book[bookCount].issuedPersonID = -1;
  sortBook(book, bookCount);
  bookCount++;
  clearScreen();
  cout << "\n\n\t\t\033[1;32m New book has been successfully added to record.\033[0m";
  cout << "\n\t\t1.Add more books.";
  cout << "\n\t\t0.Exit.\n\t\t";
  choice = getch();
  if (choice == '1')
    goto addBook;
  saveBooks(book, bookCount);
}
void sortBook(books book[], int &bookCount)
{
  int flag = 0;
  books temp;
  temp.title = book[bookCount].title;
  temp.isbn = book[bookCount].isbn;
  temp.price = book[bookCount].price;
  temp.author = book[bookCount].author;
  temp.available = book[bookCount].available;
  temp.category = book[bookCount].category;
  temp.issuedPersonID = book[bookCount].issuedPersonID;

  for (int i = 0; i < bookCount; i++)
  {
    if (book[i].title > book[bookCount].title)
    {
      for (int j = bookCount; j > i; j--)
      {
        book[j].title = book[j - 1].title;
        book[j].isbn = book[j - 1].isbn;
        book[j].price = book[j - 1].price;
        book[j].author = book[j - 1].author;
        book[j].available = book[j - 1].available;
        book[j].category = book[j - 1].category;
        book[j].issuedPersonID = book[j - 1].issuedPersonID;
      }
      book[i].title = temp.title;
      book[i].isbn = temp.isbn;
      book[i].price = temp.price;
      book[i].author = temp.author;
      book[i].available = temp.available;
      book[i].category = temp.category;
      book[i].issuedPersonID = temp.issuedPersonID;

      flag = 1;
    }
    if (flag == 1)
      break;
  }
}
void deleteBook(books book[], int &bookCount)
{
deleteBook:
  char choice;
  clearScreen();
  int idx = searchBook(book, bookCount);
  if (idx < 0)
  {
    cout << "\n\n\t\t\033[1;31mBook does not found.\033[0m";
    cout << "\n\t\tDo you want to search again(y/n)";
    choice = getch();
    if (choice == 'y' || choice == 'Y')
      goto deleteBook;
    else
      clearScreen();
    return;
  }
  bookHeader();
  showBook(idx, book);
  cout << "\n\t\t\033[1;33mDo you want to delete it(y/n):\033[0m";
  choice = getch();
  if (choice == 'n' || choice == 'N')
    return;

  while (idx < bookCount - 1)
  {
    book[idx].title = book[idx + 1].title;
    book[idx].isbn = book[idx + 1].isbn;
    book[idx].price = book[idx + 1].price;
    book[idx].author = book[idx + 1].author;
    book[idx].available = book[idx + 1].available;
    book[idx].category = book[idx + 1].category;
    book[idx].issuedPersonID = book[idx + 1].issuedPersonID;
    idx++;
  }
  bookCount--;
  saveBooks(book, bookCount);
  clearScreen();
  cout << "\n\t\t\033[1;32mBook  has been successfully removed:\033[0m";
  cout << "\n\n\n\t1.Delete more books.";
  cout << "\n\t0.Main menu.";
  choice = getch();
  clearScreen();
  if (choice == '1')
    goto deleteBook;
}

void signUp(members member[], int &userCount)
{
signUp:
  string uN, uP, uS;
  clearScreen();
  cout << "\t\tEnter  user name         :";
  getline(cin >> ws, uN);
  cout << "\t\tEnter user password      :";
  cin >> uP;
  cout << "\n\t\tpress 1 for Librarion:" << endl;
  cout << "\t\tpress 2 for library member:" << endl
       << "\t\t";
  cin >> uS;
  if (uS == "2")
    uS = "Member";
  else if (uS == "1")
    uS = "Librarion";
  else
  {
    cout << "\n\t\t\033[1;31mWrong selection.\033[0m";
    cout << "\n\t\tTry again.";
    cout << "\n\t\tPress any key :";
    getch();
    goto signUp;
  }
  string userRole = checkUserRole(uN, uP, member, userCount);
  if (userRole == "not found")
  {
    member[userCount].userName = uN;
    member[userCount].password = uP;
    member[userCount].role = uS;
    member[userCount].bookIssue.isbn = -1;
    member[userCount].bookIssue.year = 0;
    member[userCount].bookIssue.month = 0;
    member[userCount].bookIssue.day = 0;
    member[userCount].bookIssue.fine = 0;
    userCount++;
    saveMembers(member, userCount);
    clearScreen();
    cout << "\n\n                 \033[1;32mCONGRATULATION..." << endl;
    cout << "                 New user  successfully Registered.\033[0m" << endl;
  }
  else
    cout << "\t\t\033[1;31mSorry user already exist.\033[0m" << endl;
  cout << "\t\tpress any key to continue:";
  getch();
  clearScreen();
}
void signIn(members member[], books book[], int &bookCount, int &userCount)
{
  clearScreen();
  string uN, uP;
  cout << "\n\t\t(For test    Username: noman     Password: 1234 )       :";
  cout << "\n\n\t\tEnter user name       :";
  cin >> uN;
  cout << "\t\tEnter user Password   :";
  cin >> uP;
  string userRole = checkUserRole(uN, uP, member, userCount);
  clearScreen();
  if (userRole == "Member")
  {
    clearScreen();
    cout << "\n\t\t\033[1;32mCONGRATULATION..." << endl;
    cout << "\t\tSigng in successfully.\033[0m" << endl;
    cout << "\n\t\tPress any key to move furthor:";
    getch();
    memberInterface(member, book, bookCount, userCount);
  }
  else if (userRole == "Librarian")
  {
    cout << "\n\t\t\033[1;32mCONGRATULATION..." << endl;
    cout << "\t\tSign in successfully.\033[0m" << endl;
    cout << "\n\t\tPress any key to move furthor:";
    getch();
    librarionInterface(member, book, bookCount, userCount);
  }
  else
    cout << "\t\t\033[1;31mSorry user does not found\033[0m" << endl;
  cout << "\t\tPress any key to go main menu:";
  getch();
}
string checkUserRole(string userName, string userPassword, members member[], int userCount)
{
  for (int i = 0; i < userCount; i++)
  {
    if (member[i].userName == userName && member[i].password == userPassword)
    {
      currentUserID = i;
      return member[i].role;
    }
  }
  return "not found";
}

void bookManagement(members member[], books book[], int &bookCount, int &userCount)
{
  char choice = ' ';
  while (choice != '0')
  {
    clearScreen();
    cout << "\n         \033[1;37;44m======== BOOKS MANAGEMENT ========\033[0m";
    cout << "\n\n           1.Add new books ";
    cout << "\n           2.Delete book.";
    cout << "\n           3.View all books. ";
    cout << "\n           4.Find a specific book.";
    cout << "\n           0.Exit the menu.\n";
    cout << "\n           choice :";
    choice = getch();
    switch (choice)
    {
    case '1':
      addBook(book, bookCount);
      break;
    case '2':
      deleteBook(book, bookCount);
      break;
    case '3':
      viewAllBooks(book, bookCount);
      break;
    case '4':
      searchBook(book, bookCount);
      break;
    case '0':
    {
      cout << "\n\t\tPress any key to exit book management menu:";
      getch();
    }
    }
  }
}
void viewAllBooks(books book[], int &bookCount)
{
  clearScreen();
  bookHeader();
  for (int i = 0; i < bookCount; i++)
  {
    showBook(i, book);
  }
  cout << "\n\n\t\tPress any key to return:";
  getch();
  clearScreen();
}
void viewAllAvailableBooks(books book[], int &bookCount)
{
  clearScreen();
  bookHeader();
  for (int i = 0; i < bookCount; i++)
  {
    if (book[i].issuedPersonID == -1)
      showBook(i, book);
  }
  cout << "\n\n\t\tPress any key to return:";
  getch();
  clearScreen();
}
void notAvailableBooks(books book[], int &bookCount)
{
  clearScreen();
  bookHeader();
  for (int i = 0; i < bookCount; i++)
  {
    if (book[i].issuedPersonID != -1)
      showBook(i, book);
  }
  cout << "\n\n\t\tPress any key to return:";
  getch();
  clearScreen();
}

int searchBook(books book[], int &bookCount)
{
  string title = "";
  char ch;
  while (true)
  {
    int desiredBookIdx = -1;
    clearScreen();
    bookHeader();
    for (int i = 0; i < bookCount; i++)
    {
      bool check = isBookMatch(i, title, book);
      if (check)
      {
        showBook(i, book);
        desiredBookIdx = i;
      }
    }
    cout << "\n\t\tEnter book name:" << title;
    ch = getch();
    if (ch == 13)
    {
      clearScreen();
      return desiredBookIdx;
    }
    else if (ch == 8 && !title.empty())
    {
      title.pop_back();
    }
    else if (ch == 27)
    {
      clearScreen();
      return -1;
    }
    else
    {
      title += ch;
    }
  }
}

bool isBookMatch(int i, string title, books book[])
{
  for (int j = 0; j < title.length(); j++)
    if (title[j] != book[i].title[j])
      return false;
  return true;
}

void showBook(int idx, books book[])
{
  cout << left << setw(15) << " " << setw(10) << book[idx].isbn << setw(40) << book[idx].title << setw(25) << book[idx].author << setw(10) << book[idx].price << setw(10) << book[idx].category;
  if (book[idx].issuedPersonID == -1)
    cout << "     Available    ";
  else
    cout << "     Not available";
  cout << endl;
}
void bookHeader()
{
  cout << "               _________________________________________________________________________________________________________" << endl;
  cout << left << setw(15) << " " << "\033[1;37;44m" << setw(10) << "ISBN" << setw(40) << "TITLE" << setw(25) << "AUTHOR" << setw(10) << "PRICE" << setw(10) << "CATEGORY" << "     STATUS    \033[0m" << endl;
  cout << "               ---------------------------------------------------------------------------------------------------------" << endl;
}

void memberManagement(members member[], books book[], int &bookCount, int &userCount)
{
  char choice = ' ';
  while (choice != 0)
  {
    clearScreen();
    cout << "    \t\t\033[1;37;44m======MEMBER MANAGEMENT======\033[0m\n\n";
    cout << "\t\t1.Show all existing members.";
    cout << "\n\t\t2.Find member.";
    cout << "\n\t\t3.Add new member.";
    cout << "\n\t\t4.Remove existing member.";
    cout << "\n\t\t0.Exit.";
    cout << "\n\n\t\tchoice:";
    choice = getch();
    switch (choice)
    {
    case '1':
      viewAllMembers(member, userCount);
      break;
    case '2':
    {
      clearScreen();
      searchMember(member, userCount);
      break;
    }
    case '3':
      signUp(member, userCount);
      break;
    case '4':
      removeMember(member, userCount);
      break;
    case '0':
    {
      cout << "\n\n\t\tPress any key to exit menu:";
      getch();
      return;
    }
    }
  }
}
void removeMember(members member[], int &userCount)
{
removeMember:
  char choice = 'n';
  clearScreen();
  int idx = searchMember(member, userCount);
  if (idx < 0)
  {
    cout << "\n\t\tUser does't found.";
    cout << "\n\t\tPress any key to go previous menu:";
    getch();
    return;
  }
  memberHeader();
  showMember(idx, member);
  cout << "\n\t\t\033[1;33mDo you want to remove(y/n):\033[0m\n";
  choice = getch();
  if (choice == 'y' || choice == 'Y')
  {
    while (idx < userCount - 1)
    {
      member[idx].userName = member[idx + 1].userName;
      member[idx].password = member[idx + 1].password;
      member[idx].role = member[idx + 1].role;
      member[idx].bookIssue.isbn = member[idx + 1].bookIssue.isbn;
      member[idx].bookIssue.year = member[idx + 1].bookIssue.year;
      member[idx].bookIssue.month = member[idx + 1].bookIssue.month;
      member[idx].bookIssue.day = member[idx + 1].bookIssue.day;
      member[idx].bookIssue.fine = member[idx + 1].bookIssue.fine;
      idx++;
    }
    userCount--;
    cout << "\n\t\t\033[1;32m Member  has been successfully removed from record.\033[0m";
    cout << "\n\t\tDo you want to remove an other member(Y/N)";
    choice = getch();
    if (choice == 'y' || choice == 'Y')
      goto removeMember;
  }
}
void viewAllMembers(members member[], int userCount)
{
  clearScreen();
  memberHeader();
  for (int i = 0; i < userCount; i++)
    showMember(i, member);
  cout << "\n\t\tPress any key to move previous menu:";
  getch();
  clearScreen();
}
void memberHeader()
{
  cout << left << "\n\n\n"
       << setw(15) << " " << "____________________________________________________________________" << endl;
  cout << left << setw(15) << " " << "\033[1;37;44m" << setw(20) << "USER NAME" << setw(18) << "PASSWORD" << setw(15) << "   ROLE" << "BOOK STATUS    \033[0m" << endl;
  cout << setw(15) << " " << "--------------------------------------------------------------------" << endl;
}
void showMember(int idx, members member[])
{
  cout << left << setw(15) << " " << setw(20) << member[idx].userName << setw(18) << member[idx].password << setw(15) << member[idx].role;
  if (member[idx].bookIssue.isbn != -1)
    cout << "     Issued";
  else
    cout << "     Not Issued";
  if (member[idx].bookIssue.fine > 0)
    cout << "     Fine: RS " << member[idx].bookIssue.fine;
  cout << endl;
}
void personalInformation(members member[], books book[], int bookCount)
{
  clearScreen();
   memberHeader();
  showMember(currentUserID, member);
  if (member[currentUserID].bookIssue.isbn != -1)
  {
    cout << "\n\n\t\t======= ISSUED BOOK INFORMATION =======\n";
    for (int i = 0; i < bookCount; i++)
    {
      if (book[i].isbn == member[currentUserID].bookIssue.isbn)
      {
        bookHeader();
        showBook(i, book);
        cout << "\n\n\t\tIssued Date: " << member[currentUserID].bookIssue.day << "/" << member[currentUserID].bookIssue.month << "/" << member[currentUserID].bookIssue.year;
        int days = daysBetween(member[currentUserID].bookIssue.year, member[currentUserID].bookIssue.month, member[currentUserID].bookIssue.day,
                               2026, 01, 01);
        cout << "\n\t\tDays since issued: " << days << " days";
        if (days > 14)
        {
          int fine = (days - 14) * 5;
          cout << "\n\t\tFine accrued: RS " << fine;
        }
        else
          cout << "\n\t\tNo fine accrued.";
        cout<<"\n\t\tPress any key to return:";
        getch();
        clearScreen();
        return;
      }
    }
    
  }
    cout << "\n\n\t\tYou have not issued any book yet.";
        cout<<"\n\t\tPress any key to return:";
  getch();
  clearScreen();
  return;
  
}

int daysBetween(int y1, int m1, int d1, int y2, int m2, int d2)
{

  tm a = {0}, b = {0};
  a.tm_year = y1 - 1900;
  a.tm_mon = m1 - 1;
  a.tm_mday = d1;
  b.tm_year = y2 - 1900;
  b.tm_mon = m2 - 1;
  b.tm_mday = d2;
  time_t ta = mktime(&a);
  time_t tb = mktime(&b);
  if (ta == -1 || tb == -1)
    return 0;
  double diff = difftime(tb, ta);
  int days = (int)(diff / (60 * 60 * 24));
  return days;
}
int searchMember(members member[], int userCount)
{
  string userName = "";
  char ch;
  while (true)
  {
    int desiredMemberIdx = -1;
    clearScreen();
    memberHeader();
    for (int i = 0; i < userCount; i++)
    {
      bool check = isMemberMatch(i, userName, member);
      if (check)
      {
        showMember(i, member);
        desiredMemberIdx = i;
      }
    }
    cout << "\n\t\tEnter user name:" << userName;
    ch = getch();
    if (ch == 13)
    {
      clearScreen();
      return desiredMemberIdx;
    }
    else if (ch == 8 && !userName.empty())
    {
      userName.pop_back();
    }
    else if (ch == 27)
    {
      clearScreen();
      return -1;
    }
    else
    {
      userName += ch;
    }
  }
}
bool isMemberMatch(int i, string userName, members member[])
{
  for (int j = 0; j < userName.length(); j++)
    if (userName[j] != member[i].userName[j])
      return false;
  return true;
}

void circulationOfBooks(members member[], books book[], int &bookCount, int &userCount)
{
  char choice = ' ';
  while (choice != '0')
  {
    clearScreen();
    cout << "\n\n\t\033[1;37;44m======= CIRCULATION =======\033[0m";
    cout << "\n\t\t1.Issue a Book";
    cout << "\n\t\t2.Return a book";
    cout << "\n\t\t3.View Issued Books";
    cout << "\n\t\t4.View available Books";
    cout << "\n\t\t0.Exit Menu";
    cout << "\n\n\t\tchoice :";
    choice = getch();

    switch (choice)
    {
    case '1':
      issueBook(member, book, bookCount, userCount);
      break;
    case '2':
      returnBook(member, book, bookCount, userCount);
      break;
    case '3':
      notAvailableBooks(book, bookCount);
      break;
    case '4':
      viewAllAvailableBooks(book, bookCount);
    }
  }
}
void issueBook(members member[], books book[], int &bookCount, int &userCount)
{
  int bookIdx = searchBook(book, bookCount);
  int memberIdx = searchMember(member, userCount);
  if (bookIdx < 0)
  {
    cout << "\n\t\t\033[1;31mBook does not found.\033[0m";
    cout << "\n\t\tPress any key to exit:";
    getch();
    return;
  }
  if (memberIdx < 0)
  {
    cout << "\n\t\t\033[1;31mMember not found.\033[0m";
    cout << "\n\t\tPress any key to exit:";
    getch();
    return;
  }

  cout << "\n\n\n\t\t\033[1;33mDo you want to issue :" << book[bookIdx].title << "  to  " << member[memberIdx].userName << "  ( y/n):\033[0m";
  char choice = getch();
  if (choice == 'y' || choice == 'Y')
  {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    member[memberIdx].bookIssue.isbn = book[bookIdx].isbn;
    member[memberIdx].bookIssue.year = 1900 + ltm->tm_year;
    member[memberIdx].bookIssue.month = 1 + ltm->tm_mon;
    member[memberIdx].bookIssue.day = ltm->tm_mday;
    member[memberIdx].bookIssue.fine = 0;
    book[bookIdx].available = false;
    book[bookIdx].issuedPersonID = memberIdx;
    book[bookIdx].bookIssue = member[memberIdx].bookIssue;
    saveBooks(book, bookCount);
    saveMembers(member, userCount);
    cout << "\n\n\t\t\033[1;32m" << book[bookIdx].title << " has been successfully issued to " << member[memberIdx].userName << "\033[0m";
    cout << "\n\t\tPress any key to continue:";
    getch();
    return;
  }
}
void returnBook(members member[], books book[], int &bookCount, int &userCount)
{
  int bookIdx = searchBook(book, bookCount);
  if (bookIdx < 0)
  {
    cout << "\n\t\t\033[1;31mBook does not found:\033[0m ";
    cout << "\n\t\tPress any key to exit:";
    getch();
    return;
  }
  int borrowerIdx = book[bookIdx].issuedPersonID;
  if (borrowerIdx < 0)
  {
    cout << "\n\t\t\033[1;31mThis book is not issued to any member.\033[0m";
    cout << "\n\t\tPress any key to exit:";
    getch();
    return;
  }
  if (member[borrowerIdx].bookIssue.isbn == book[bookIdx].isbn)
  {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int curY = 1900 + ltm->tm_year;
    int curM = 1 + ltm->tm_mon;
    int curD = ltm->tm_mday;
    int days = daysBetween(member[borrowerIdx].bookIssue.year, member[borrowerIdx].bookIssue.month, member[borrowerIdx].bookIssue.day, curY, curM, curD);
    int fineDays = 0;
    if (days > 14)
      fineDays = days - 14;
    int fineAmount = fineDays * 10;
    member[borrowerIdx].bookIssue.fine = fineAmount;
    cout << "\n\t\t\033[1;32m" << book[bookIdx].title << " is issued to " << member[borrowerIdx].userName << "\033[0m";
    if (fineAmount > 0)
      cout << "\n\t\t\033[1;33mLate return. Fine: RS " << fineAmount << "\033[0m";

    cout << "\n\t\tPress any key to confirm return:";
    getch();
    member[borrowerIdx].bookIssue.isbn = -1;
    member[borrowerIdx].bookIssue.year = 0;
    member[borrowerIdx].bookIssue.month = 0;
    member[borrowerIdx].bookIssue.day = 0;
    member[borrowerIdx].bookIssue.fine = 0;
    book[bookIdx].available = true;
    book[bookIdx].issuedPersonID = -1;
    saveBooks(book, bookCount);
    saveMembers(member, userCount);
    cout << "\n\t\t\033[1;32mBook has been successfully recovered.\033[0m";
  }
  else
    cout << "\n\t\tThis book is not issued to any member.";
  cout << "\n\t\tPress any key to go previous menu";
  getch();
  clearScreen();
}

void loadBooks(books book[], int &bookCount)
{

  fstream file;
  file.open("books.txt", ios::in);
  while (file >> book[bookCount].isbn)
  {
    file.ignore();
    getline(file, book[bookCount].title, '|');
    getline(file, book[bookCount].author, '|');
    getline(file, book[bookCount].category, '|');
    file >> book[bookCount].price;
    file.ignore();
    file >> book[bookCount].issuedPersonID;
    bookCount++;
  }
  file.close();
}
void saveBooks(books book[], int &bookCount)
{
  fstream file;
  file.open("books.txt", ios::out);
  for (int i = 0; i < bookCount; i++)
  {
    file << book[i].isbn << "|"
         << book[i].title << "|"
         << book[i].author << "|"
         << book[i].category << "|"
         << book[i].price << "|"
         << book[i].issuedPersonID << "\n";
  }
}
void loadMembers(members member[], int &userCount)
{
  fstream file;
  file.open("users.txt", ios::in);
  string line;
  while (getline(file, line))
  {
    if (line.empty())
      continue;
    stringstream ss(line);
    string token;
    getline(ss, member[userCount].userName, '|');
    getline(ss, member[userCount].password, '|');
    getline(ss, member[userCount].role, '|');
    if (getline(ss, token, '|'))
      member[userCount].bookIssue.isbn = stoi(token);
    else
      member[userCount].bookIssue.isbn = -1;
    if (getline(ss, token, '|'))
      member[userCount].bookIssue.year = stoi(token);
    else
      member[userCount].bookIssue.year = 0;
    if (getline(ss, token, '|'))
      member[userCount].bookIssue.month = stoi(token);
    else
      member[userCount].bookIssue.month = 0;
    if (getline(ss, token, '|'))
      member[userCount].bookIssue.day = stoi(token);
    else
      member[userCount].bookIssue.day = 0;
    if (getline(ss, token, '|'))
      member[userCount].bookIssue.fine = stoi(token);
    else
      member[userCount].bookIssue.fine = 0;
    userCount++;
  }
  file.close();
}
void saveMembers(members member[], int &userCount)
{
  fstream file;
  file.open("users.txt", ios::out);
  for (int i = 0; i < userCount; i++)
  {
    file << member[i].userName << "|"
         << member[i].password << "|"
         << member[i].role << "|"
         << member[i].bookIssue.isbn << "|"
         << member[i].bookIssue.year << "|"
         << member[i].bookIssue.month << "|"
         << member[i].bookIssue.day << "|"
         << member[i].bookIssue.fine << "\n";
  }
  file.close();
}
