#include <iostream>
#include <fstream>
using namespace std;



class Helper
{
public:
	static int StringLenght(char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != 0; i++)
			count++;
		return count;

	}
	static void StringCopy(char* dest, char* src) {
		//Deep Copies src into dest.
		for (int i = 0; src[i - 1] != 0; i++)
			dest[i] = src[i];
	}
	static void StringCopy(char* dest, const char* src) {
		//Deep Copies src into dest.
		for (int i = 0; src[i - 1] != 0; i++)
			dest[i] = src[i];
	}
	static char* GetStringFromBuffer(char str[])
	{

		int count = 0;
		count = StringLenght(str);
		count++;
		char* new_str = new char[count];
		StringCopy(new_str, str);
		return new_str;
	}
	static char* GetStringFromBuffer(const char str[])
	{
		int count = StringLenght(str);
		int count2 = count + 1;
		char* new_str = new char[count2];
		for (int i = 0; i < count2 - 1; i++)
		{
			new_str[i] = str[i];
		}
		new_str[count2 - 1] = '\0'; // Add null character at the end
		return new_str;
	}
	static void DisplayStr(char* str)
	{
		for (int i = 0; str[i] != 0; i++)
			cout << str[i];
	}
	static bool String_Compare(char* str1, char* str2)//Compares String Lengths
	{

		int length1 = StringLenght(str1);
		int length2 = StringLenght(str2);
		if (length1 == length2)
			return 1;
		return 0;
	}
	static int check_substring(char* str1, char* str2, int index1)//finding str2 in str1
	{
		int length = StringLenght(str2), check = 1;
		for (int i = 0; i < length && check == 1; i++, index1++)
		{
			if (str1[index1] != str2[i])
			{
				check = 0;
			}
		}
		return check;
	}
	static bool StringCompare(const char arr[], const char temp[])
	{
		int check = 1;

		for (int i = 0; i < 2 && check == 1; i++)
		{
			if (arr[i] != temp[i])
				check = 0;
		}
		return check;
	}
	static int StringLenght(const char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != 0; i++)
			count++;
		return count;

	}
};

class Object;
class Page;
class User;
class Post;
class Memory;
class Date;
class Comment;
class Activity;
class Facebook;

class Object
{
	char* ID;
public:
	Object();
	~Object();
	virtual void AddPostToTimeline(Post* ptr) = 0;
	virtual void PrintName() = 0;
	virtual void PrintID() = 0;
	virtual bool SearchID(const char*) = 0;
	char* GetID();
	void SetID(char*);
};

class Page : public Object
{
private:

	char* Title;
	Post** Timeline;
	int No_of_Posts;

public:
	Page();

	~Page();

	void ReadDataFromFile(istream& fin);

	void PrintListView();

	bool SearchID(const char temp[]);

	void AddPostToTimeline(Post*);

	void PrintName();

	void PrintSharedPostsByCurrentDate();

	void PrintID();

	void ViewPage();

};

class User :public Object
{
private:
	/*char* ID;*/
	char* FName;
	char* LName;
	int No_of_likedpages;
	int No_of_Friends;
	Page** LikedPages;
	User** Friends;
	Post** Timeline;
	Memory* memory;
	int LikedPageCheck;
	int FriendCheck;
	int No_of_Posts;
	static int OverallComments;

public:
	User();

	~User();

	void ReadDataFromFile(istream& fin);

	void PrintListView();

	void LikePage(Page* ptr);

	bool SearchID(const char temp[]);

	void AddFriend(User* ptr);

	void PrintFriendList();

	void PrintLikedPages();

	void AddPostToTimeline(Post*);

	void ViewHome();

	void PrintName();

	void PrintID();

	void PrintSharedPostbyCurrentdate();

	void ViewTimeline();

	void LikePost(Post*);

	void PostComment(Post*, const char*);

	void SeeYourMemories();

	void ShareMemory(Post*, const char*);

	static int GetTotalComments()
	{
		return OverallComments;
	}

	static void SetTotalComments(int total)
	{
		OverallComments = total;
	}

	char* GetNewCommentID();
	void AddMemoryToTimeline(Post*, const char*);
};

class Date
{
private:
	int day;
	int month;
	int year;

public:
	static Date CurrDate;
	static void SetDate(int d, int m, int y)
	{
		Date::CurrDate.day = d;
		Date::CurrDate.month = m;
		Date::CurrDate.year = y;
	}
	Date(int d = 1, int m = 1, int y = 1960);
	~Date()
	{

	}
	Date(Date&);
	Date& operator=(Date&);
	void Print();
	void ReadDataFromFile(ifstream&);
	bool Compare24Hrs(Date&);
	int CompareDate(Date&);
	static void PrintCurrentDate()
	{
		cout << "(" << Date::CurrDate.day << "/" << Date::CurrDate.month << "/" << Date::CurrDate.year << ")";
	}
};

Date Date::CurrDate(15, 11, 2017);

class Activity {
private:
	int Type;
	char* value;

public:
	Activity();
	~Activity();
	void ReadDataFromFile(ifstream&);
	void Print();
};

class Comment
{
	char* ID;
	char* Text;
	Object* CommentBy;

public:
	Comment();
	~Comment();
	void SetValues(char* id, const char* text, Object* commentby)
	{
		ID = Helper::GetStringFromBuffer(id);
		Text = Helper::GetStringFromBuffer(text);
		CommentBy = commentby;
	}

	void Print();

};

class Post {
private:

	char* ID;
	char* Text;
	int type;
	int TotalComments;
	int TotalLikes;
	static int TotalPosts;
	Date SharedDate;
	Activity* activity;
	Object* SharedBy;
	Object** LikedBy;
	Comment** comments;

public:
	Post();
	virtual ~Post();
	void ReadDataFromFile(ifstream&);
	void SetSharedBy(Object*);
	void SetLikedBy(Object*);
	bool SearchID(const char*);
	void AddComment(Comment*);
	virtual void Print();
	virtual void PrintByCurrentDate();
	void PrintLikes();
	void ViewMemory();
	bool MemoryCheck();
	void PrintSharedMemory(int);
	bool CheckLikedList(char*);//checks if post liked by same user before or not
	char* GetNewPostID();
	void SetValuesForMemory(char* temp, User* shared)//sets sharedby and text for shared memory
	{
		SharedBy = shared;
		Text = temp;
		SharedDate = Date::CurrDate;
		ID = GetNewPostID();
		Post::TotalPosts++;
	}
	char* GetText()
	{
		return Text;
	}
	void PrintSharedName()
	{
		SharedBy->PrintName();
	}
	static void SetTotalPosts(int value)
	{
		TotalPosts = value;
	}
};

class Memory :public Post
{
private:
	Post* OriginalPost;
public:
	Memory()
	{
		OriginalPost = 0;

	}

	~Memory()
	{

	}

	Memory(Post* ptr, const char* temp, User* sharedby)
	{
		OriginalPost = ptr;
		char* temp2 = Helper::GetStringFromBuffer(temp);
		SetValuesForMemory(temp2, sharedby);
	}

	void SetValues(Post* ptr)
	{
		OriginalPost = ptr;
	}

	void Print()
	{
		cout << "~~~ ";
		PrintSharedName();
		cout << " Shared a memory~~~ ...";
		Date::PrintCurrentDate();
		cout << endl;
		cout << "\"" << GetText() << "\"" << endl;
		OriginalPost->PrintSharedMemory(1);
	}

	void PrintByCurrentDate()
	{
		cout << "~~~ ";
		PrintSharedName();
		cout << " Shared a memory~~~ ...";
		cout << endl;
		cout << "\"" << GetText() << "\"" << endl;
		OriginalPost->PrintSharedMemory(0);
	}
};

class Facebook
{
private:
	Page** PageList;
	User** UserList;
	Post** posts;
	Comment** comments;
	static int TotalPages;
	static int TotalUsers;
	static int TotalPosts;

public:

	Facebook()
	{
		PageList = 0;
		UserList = 0;
		posts = 0;
		comments = 0;
	}

	~Facebook();

	Page* SearchPageByID(const char*);

	User* SearchUserByID(const char*);

	Object* SearchObjectByID(char*);

	Post* SearchPostByID(const char*);

	void LoadComments();

	void LoadPages();

	void LoadUsers();

	void LoadPosts();

	void Load();

	void ViewLikedList(const char*);

	void ViewPost(Post*);

	void ViewPage(const char*);

	static void Run();
};

//-----------------------------------------------------------------------------------------

//Comment Functions
Comment::Comment()
{
	ID = 0;
	Text = 0;
	CommentBy = 0;
}

Comment::~Comment()
{
	if (ID != 0)
		delete[] ID;
	if (Text != 0)
		delete[] Text;

}

void Comment::Print()
{

	CommentBy->PrintName();
	cout << " wrote: ";
	cout << "\"" << Text << "\"" << endl;
}

//Object Functions
Object::Object()
{
	ID = 0;
}

Object::~Object()
{
	if (ID != 0)
		delete[] ID;
}

void Object::SetID(char* temp)
{
	ID = temp;
}

char* Object::GetID()
{
	return ID;
}

//Post Functions
Post::Post()
{
	ID = 0;
	Text = 0;
	activity = 0;
	SharedBy = 0;
	LikedBy = 0;
	comments = 0;
	TotalComments = 0;
	TotalLikes = 0;
	type = 0;
}

Post::~Post()
{
	if (ID != 0)
		delete[] ID;
	if (Text != 0)
		delete[] Text;
	if (activity != 0)
		delete activity;

	if (comments != 0)
	{
		for (int i = 0; i < TotalComments; i++)
			delete comments[i];
		delete[] comments;
	}

	if (LikedBy != 0)
		delete[] LikedBy;
}

void Post::ReadDataFromFile(ifstream & fin)
{
	type = 0;
	fin >> type;


	char temp[100];
	fin >> temp;


	ID = Helper::GetStringFromBuffer(temp);
	SharedDate.ReadDataFromFile(fin);


	fin.getline(temp, 100);//to skip space
	fin.getline(temp, 100);

	Text = Helper::GetStringFromBuffer(temp);

	if (type == 2)//checks if post type is an activity
	{
		activity = new Activity;
		activity->ReadDataFromFile(fin);
	}

}

void Post::SetSharedBy(Object * shared)
{
	SharedBy = shared;
}

void Post::SetLikedBy(Object * liked)
{
	if (TotalLikes == 0)
	{
		LikedBy = new Object * [10];
	}

	if (TotalLikes < 10)
	{
		LikedBy[TotalLikes] = liked;
		TotalLikes++;
	}
	else
		cout << "Like Limit Full!!" << endl;

	for (int i = TotalLikes; i < 10; i++)
	{
		LikedBy[TotalLikes] = 0;
	}
}

bool Post::SearchID(const char temp[])
{
	int check = 1, size = Helper::StringLenght(temp);
	if (Helper::StringLenght(ID) == Helper::StringLenght(temp))//only proceed if lengths equal
	{
		for (int i = 0; temp[i] != 0 && check == 1; i++)
		{
			if (ID[i] != temp[i])
			{
				check = 0;
			}
		}
	}
	else
		check = 0;


	if (check == 0)
		return false;

	return true;
}

void Post::AddComment(Comment * comment)
{
	if (TotalComments == 0)
	{
		comments = new Comment * [10];
	}

	if (TotalComments < 10)//check so that comment limit not exceeded
	{
		comments[TotalComments] = comment;
		TotalComments++;
	}
	else
	{
		cout << "Comment limit full" << endl;
	}


	for (int i = TotalComments; i < 10; i++)
	{
		comments[TotalComments] = 0;
	}
}

void Post::Print()
{
	if (this != 0)
	{
		cout << "--";
		SharedBy->PrintName();

		if (type == 2)//checks if post is an activity
		{
			activity->Print();
			cout << "   \"" << Text << "\"" "...";
			SharedDate.Print();

			if (comments != 0)
			{
				for (int i = 0; comments[i] != 0; i++)
				{
					cout << "\t";
					comments[i]->Print();
				}
			}
		}
		else
		{
			cout << " Shared " << "\"" << Text << "\"...";
			SharedDate.Print();
			if (comments != 0)
			{
				for (int i = 0; comments[i] != 0; i++)
				{
					cout << "\t";
					comments[i]->Print();
				}
			}
		}
		cout << endl;
	}
	else
	{
		cout << "Post Not Found" << endl;
	}

}

void Post::PrintByCurrentDate()
{
	if (SharedDate.Compare24Hrs(Date::CurrDate))//check if post shared within 24 of currdate
	{
		cout << "--";
		SharedBy->PrintName();
		if (type == 2)//checks if post type is activity or not
		{
			activity->Print();
			cout << "   " << "\"" << Text << "\"" << endl;
			if (comments != 0)
			{
				for (int i = 0; comments[i] != 0; i++)//prints comments
				{
					cout << "\t";
					comments[i]->Print();
				}
			}
		}
		else
		{
			cout << " Shared " << "\"" << Text << "\"" << endl;
			if (comments != 0)
			{
				for (int i = 0; comments[i] != 0; i++)
				{
					cout << "\t";
					comments[i]->Print();
				}
			}
		}
		cout << endl << endl;
	}

}

void Post::PrintLikes()
{
	cout << "Post Liked By:" << endl;
	if (LikedBy != 0)
	{
		for (int i = 0; LikedBy[i] != 0; i++)
		{
			LikedBy[i]->PrintID();
			cout << "-";
			LikedBy[i]->PrintName();
			cout << endl;
		}
	}
	else
		cout << "Post Liked By Noone!!" << endl;

}

void Post::ViewMemory()//If post made on same day then print
{
	int value = SharedDate.CompareDate(Date::CurrDate);//checks if day matches with current day
	if (value != 0)
	{
		cout << "On this day " << endl;
		cout << value << " years ago" << endl;
		Print();
	}
}

bool Post::MemoryCheck()//checks if post is a memory
{
	int check = 1;
	if (SharedDate.CompareDate(Date::CurrDate) == 0)
		check = 0;

	return check;
}

void Post::PrintSharedMemory(int Value)
{
	int value = SharedDate.CompareDate(Date::CurrDate);//checks if day matches with current day
	if (value != 0)
	{
		cout << "\t(" << value << "" << " years ago)" << endl;
		cout << "--";
		SharedBy->PrintName();

		if (type == 2)
		{
			activity->Print();
			cout << "   \"" << Text << "\"" "...";
			if(Value==1)
				SharedDate.Print();
		}
		else
		{
			cout << " Shared " << "\"" << Text << "\"...." << endl;
			if(Value==1)
				SharedDate.Print();
		}
		cout << endl << endl;
	}
}

bool Post::CheckLikedList(char* temp)//checks if post previously liked by same user
{
	int check = 0;
	for (int i = 0; i < TotalLikes; i++)
	{
		if (LikedBy[i]->SearchID(temp))
			check = 1;
	}
	return check;
}

char* Post::GetNewPostID()//gives new ID of psts when a new post is posted
{
	int total = Post::TotalPosts;
	char temp[7];
	total++;
	char buffer[2];
	int digit = total % 10;
	buffer[1] = digit + '0';
	total /= 10;
	digit = total;
	buffer[0] = digit + '0';

	temp[0] = 'p';
	temp[1] = 'o';
	temp[2] = 's';
	temp[3] = 't';
	temp[4] = buffer[0];
	temp[5] = buffer[1];
	temp[6] = 0;
	char* id = Helper::GetStringFromBuffer(temp);
	
	return id;
}

//Activity Functions
Activity::Activity()
{
	Type = 0;
	value = 0;
}

Activity::~Activity()
{
	if (value != 0)
		delete[] value;
}

void Activity::ReadDataFromFile(ifstream & fin)
{
	fin >> Type;

	char temp[100];
	fin.getline(temp, 100);

	char temp2[100];
	for (int i = 1; temp[i - 1] != 0; i++)
		temp2[i - 1] = temp[i];

	value = Helper::GetStringFromBuffer(temp);
}

void Activity::Print()
{
	if (Type == 1)
		cout << " is feeling ";
	if (Type == 2)
		cout << " is thinking about ";
	if (Type == 3)
		cout << " is Making ";
	if (Type == 4)
		cout << " is celebrating ";

	cout << value << endl;

}

//Date Functions
Date::Date(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

Date::Date(Date & rhs)
{
	day = rhs.day;
	month = rhs.month;
	year = rhs.year;
}

Date& Date::operator=(Date & rhs)
{

	day = rhs.day;
	month = rhs.month;
	year = rhs.year;

	return *this;
}

void Date::Print()
{
	cout << "(" << day << "/" << month << "/" << year << ")" << endl;
}

void Date::ReadDataFromFile(ifstream & fin)
{
	fin >> day;
	fin >> month;
	fin >> year;
}

bool Date::Compare24Hrs(Date & CurrentDate)//compares if two posts posted within 24 hrs
{
	if (year == CurrentDate.year)
	{
		if (month == CurrentDate.month)
		{
			if (day == CurrentDate.day || day == CurrentDate.day - 1)
				return true;
		}
	}
	return false;
}

int Date::CompareDate(Date & CurrentDate)//if post made on same day but different year then return difference of years as well
{
	int difference = 0;
	if (day == CurrentDate.day)
	{
		if (year != CurrentDate.year)
		{
			difference = CurrentDate.year - year;
		}
	}
	return difference;
}


//Pages Functions
Page::Page()
{

	Title = 0;
	Timeline = 0;
	No_of_Posts = 0;
}

Page::~Page()
{

	if (Title != 0)
		delete[] Title;

	if (Timeline != 0)
	{
		for (int i = 0; i < No_of_Posts; i++)
		{
			delete Timeline[i];

		}

		delete[] Timeline;
	}
}

void Page::ReadDataFromFile(istream & fin)
{
	char temp[80];
	fin >> temp;
	int count = Helper::StringLenght(temp);
	count++;
	char* id = 0;
	id = new char[count];
	Helper::StringCopy(id, temp);//Deep Copying ID
	SetID(id);


	fin.getline(temp, 80);

	char temp2[80];
	int check = 0, index = 0;
	count = 0;

	//[i-1] so that null character also copied
	for (int i = 1; temp[i - 1] != 0; i++, index++)//i=1 to skip "\t"
	{
		temp2[index] = temp[i];
		count++;
	}


	Title = Helper::GetStringFromBuffer(temp2);

}

void Page::PrintListView()
{
	cout << GetID() << "-" << Title << endl;
}

bool Page::SearchID(const char temp[])
{
	int check = 1, size = Helper::StringLenght(temp);
	char* id = GetID();
	if (Helper::StringLenght(id) == Helper::StringLenght(temp))//only proceed if lengths equal
	{
		for (int i = 0; temp[i] != 0 && check == 1; i++)
		{
			if (id[i] != temp[i])
			{
				check = 0;
			}
		}
	}
	else
		check = 0;


	if (check == 0)
		return false;

	return true;
}

void Page::AddPostToTimeline(Post * ptr)
{
	if (Timeline == 0)
	{
		Timeline = new Post * [10];
	}

	if (No_of_Posts < 10)//checks if no of posts below limit
	{
		Timeline[No_of_Posts] = ptr;
		No_of_Posts++;
	}
	else
		cout << "Posts limit full" << endl;

	for (int i = No_of_Posts; i < 10; i++)
	{
		Timeline[i] = 0;
	}
}

void Page::PrintName()
{
	cout << Title;
}

void Page::PrintSharedPostsByCurrentDate()
{
	if (Timeline != 0)
	{
		for (int i = 0; Timeline[i] != 0; i++)
		{
			Timeline[i]->PrintByCurrentDate();
		}
	}
}

void Page::PrintID()
{
	cout << GetID();
}

void Page::ViewPage()
{
	cout << Title << endl;
	if (Timeline != 0)
	{
		for (int i = 0; Timeline[i] != 0; i++)
		{
			Timeline[i]->Print();
		}
	}
}


//User Functions
User::User()
{
	/*ID = 0;*/
	FName = 0;
	LName = 0;
	LikedPages = 0;
	Friends = 0;
	No_of_likedpages = 0;
	No_of_Friends = 0;
	LikedPageCheck = 0; // checks for LikedPage allocation
	FriendCheck = 0; // checks for Friends allocation
	Timeline = 0;
	No_of_Posts = 0;
	memory = 0;
}

User::~User()
{

	if (FName != 0)
		delete[] FName;

	if (LName != 0)
		delete[] LName;

	if (memory != 0)
		delete memory;

	if (LikedPages != 0)
		delete[] LikedPages;

	if (Friends != 0)
		delete[] Friends;

	if (Timeline != 0)
	{
		for (int i = 0; i < No_of_Posts; i++)
		{
			delete Timeline[i];

		}
		delete[] Timeline;
	}

}

void User::ReadDataFromFile(istream & fin)
{
	char temp[80];
	fin >> temp;
	char* id = 0;
	id = Helper::GetStringFromBuffer(temp);
	SetID(id);

	fin >> temp;
	FName = Helper::GetStringFromBuffer(temp);

	fin >> temp;
	LName = Helper::GetStringFromBuffer(temp);
}

void User::LikePage(Page * ptr)
{
	if (LikedPageCheck == 0)
	{
		LikedPages = new Page * [10];
		LikedPageCheck = 1;
	}

	if (No_of_likedpages < 10)//like only if likes are below limit
	{
		LikedPages[No_of_likedpages] = ptr;
		No_of_likedpages++;
	}
	else
		cout << "Likes Limit for Page is full!!" << endl;

	for (int i = No_of_likedpages; i < 10; i++)
	{
		LikedPages[No_of_likedpages] = 0;
	}

}

bool User::SearchID(const char temp[])
{
	int check = 1, size = Helper::StringLenght(temp);
	char* id = GetID();
	if (Helper::StringLenght(id) == Helper::StringLenght(temp))//checks if lengths are equal
	{
		for (int i = 0; temp[i] != 0 && check == 1; i++)
		{
			if (id[i] != temp[i])//comparing ids
			{
				check = 0;
			}
		}
	}
	else
		check = 0;


	if (check == 0)
		return false;

	return true;
}

void User::AddFriend(User * ptr)
{
	if (FriendCheck == 0)
	{
		Friends = new User * [10];
		FriendCheck = 1;
	}

	if (No_of_Friends < 10)
	{
		Friends[No_of_Friends] = ptr;
		No_of_Friends++;
	}
	else
		cout << "Friend Limit Full!!" << endl;

	for (int i = No_of_Friends; i < 10; i++)
	{
		Friends[No_of_Friends] = 0;
	}

}

void User::PrintFriendList()
{
	if (this != 0)
	{
		cout << FName << " " << LName << "---Friend List" << endl << endl;
		if (No_of_Friends == 0)
		{
			cout << "No Friends!!" << endl;
		}


		for (int i = 0; i < No_of_Friends; i++)
		{
			cout << Friends[i]->GetID() << "-" << Friends[i]->FName << " " << Friends[i]->LName << endl;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}

}

void User::PrintLikedPages()
{
	if (this != 0)
	{
		cout << FName << " " << LName << "---Liked Pages" << endl << endl;
		if (No_of_likedpages == 0)
			cout << "No Liked Pages!!" << endl;

		for (int i = 0; i < No_of_likedpages; i++)
		{
			LikedPages[i]->PrintListView();
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}

}

void User::AddPostToTimeline(Post * ptr)
{
	if (this != 0)
	{
		if (Timeline == 0)
		{
			Timeline = new Post * [10];
		}

		if (No_of_Posts < 10)
		{
			Timeline[No_of_Posts] = ptr;
			No_of_Posts++;
		}
		else
			cout << "Posts limit full" << endl;

		for (int i = No_of_Posts; i < 10; i++)
		{
			Timeline[i] = 0;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}
}

void User::ViewHome()
{
	if (this != 0)
	{
		cout << FName << " " << LName << "--Home Page" << endl;

		//printing of posts made within 24 hrs of current date
		for (int i = 0; i < No_of_Friends; i++)
		{
			Friends[i]->PrintSharedPostbyCurrentdate();
		}

		for (int i = 0; i < No_of_likedpages; i++)
		{
			LikedPages[i]->PrintSharedPostsByCurrentDate();
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}
}

void User::PrintName()
{
	if (this != 0)
	{
		cout << FName << " " << LName;
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}

}

void User::PrintSharedPostbyCurrentdate()
{
	if (this != 0)
	{
		if (Timeline != 0)
		{
			for (int i = 0; Timeline[i] != 0; i++)
			{
				Timeline[i]->PrintByCurrentDate();//prints posts posted within 24hrs of current date
			}
		}
	}

}

void User::ViewTimeline()
{
	if (this != 0)
	{
		cout << FName << " " << LName << "--Timeline" << endl;

		if (Timeline != 0)
		{
			for (int i = 0; Timeline[i] != 0; i++)
			{
				Timeline[i]->Print();
			}
		}
		else
		{
			cout << "No Posts Shared" << endl;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}

}

void User::PrintID()
{
	if (this != 0)
	{
		cout << GetID();
	}

}

void User::LikePost(Post * Postptr)
{
	int check = 1;
	if (this != 0)
	{
		char* id = GetID();

		if (Postptr != 0)
		{
			if (Postptr->CheckLikedList(id) == 1)//checks if post previously liked by the user
				check = 0;
		}

		if (Postptr != 0 && check == 1)
		{
			Postptr->SetLikedBy(this);
		}
		else if (Postptr == 0)
		{
			cout << "Post Not Found so cannot be Liked!!" << endl;
		}
		else
		{
			cout << "Post Already liked by you!!" << endl;
		}
	}
	else
	{
		cout << "User not Found!!" << endl;
	}
}

char* User::GetNewCommentID()//gives new ID of comments when a new comment is posted
{
	int total = User::GetTotalComments();
	char temp[4];
	total++;
	char buffer[2];
	int digit = total % 10;
	buffer[1] = digit + '0';
	total /= 10;
	digit = total;
	buffer[0] = digit + '0';

	temp[0] = 'c';
	temp[1] = buffer[0];
	temp[2] = buffer[1];
	temp[3] = 0;
	char* id = Helper::GetStringFromBuffer(temp);
	User::SetTotalComments(total);

	return id;
}

void User::PostComment(Post * Postptr, const char* temp)//Posts a comment from a specific user on a specific post
{
	if (this != 0)
	{
		if (Postptr != 0)
		{
			Comment* comment = new Comment;
			char* id = GetNewCommentID();
			comment->SetValues(id, temp, this);
			Postptr->AddComment(comment);
		}
		else
		{
			cout << "Post Not Found so cannot Post Comment!!!" << endl;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}
}

void User::SeeYourMemories()//see posts made on same day but different year
{
	if (this != 0)
	{
		if (Timeline != 0)
		{
			for (int i = 0; Timeline[i] != 0; i++)
			{
				Timeline[i]->ViewMemory();
			}
		}
		else
		{
			cout << "User has no Posts!!" << endl;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}


}

void User::AddMemoryToTimeline(Post * ptr, const char* temp)
{
	if (this != 0)
	{
		if (Timeline == 0)
		{
			Timeline = new Post * [10];
		}

		if (No_of_Posts < 10)
		{

			Timeline[No_of_Posts] = new Memory(ptr, temp, this);
			No_of_Posts++;
		}

		for (int i = No_of_Posts; i < 10; i++)
		{
			Timeline[i] = 0;
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}
}

void User::ShareMemory(Post * ptr, const char* Text)
{
	if (this != 0)
	{
		if (Timeline != 0)
		{
			int check = 0;//For checking if post is of user and posted on same date

			for (int i = 0; Timeline[i] != 0; i++)//check if post is of user
			{
				if (Timeline[i] == ptr)
				{
					check = 1;
				}
			}

			if (check == 1)
			{
				check = ptr->MemoryCheck();
				if (check == 1)
				{
					AddMemoryToTimeline(ptr, Text);
				}

			}
		}
	}
	else
	{
		cout << "User Not Found!!" << endl;
	}

}

//Facebook Functions
Facebook::~Facebook()
{
	if (TotalPages != 0)
	{
		for (int i = 0; i < TotalPages; i++)
		{
			delete PageList[i];
		}
		delete[] PageList;
	}


	if (UserList != 0)
	{
		for (int i = 0; i < TotalUsers; i++)
		{
			delete UserList[i];
		}
		delete[] UserList;
	}


	if (posts != 0)
	{
		delete[] posts;
	}

	if (comments != 0)
		delete[] comments;
}

Page* Facebook::SearchPageByID(const char temp[])
{
	Page* ptr = 0;
	int check = 0;
	for (int i = 0; i < Facebook::TotalPages && check == 0; i++)
	{
		if (PageList[i]->SearchID(temp) == 1)//checks if page[i] id is equal to given id or not
		{
			ptr = PageList[i];
			check = 1;
		}
	}
	return ptr;
}

User* Facebook::SearchUserByID(const char temp[])
{
	User* ptr = 0;
	int check = 0;
	for (int i = 0; i < Facebook::TotalUsers && check == 0; i++)
	{
		if (UserList[i]->SearchID(temp) == 1)
		{
			ptr = UserList[i];
			check = 1;
		}
	}
	return ptr;
}

Object* Facebook::SearchObjectByID(char temp[])
{
	Object* newobj;

	const char alphabet = temp[0];
	if (alphabet == 'p')//check if id is of page or user
	{
		newobj = SearchPageByID(temp);
	}
	else
	{
		newobj = SearchUserByID(temp);
	}

	return newobj;
}

Post* Facebook::SearchPostByID(const char temp[])
{
	Post* ptr = 0;
	int check = 0;
	for (int i = 0; i < 12 && check == 0; i++)
	{
		if (posts[i]->SearchID(temp) == 1)
		{
			ptr = posts[i];
			check = 1;
		}
	}
	return ptr;
}

void Facebook::LoadUsers()
{
	ifstream fin;
	fin.open("SocialNetworkUsers.txt");

	Page* pageptr = 0;
	char* temp = 0, arr[10];
	int totalusers = 0, j = 0, check = 0;
	fin >> totalusers;
	int totalusers2 = totalusers + 1;
	char*** FriendIDs = new char** [totalusers2];
	UserList = new User * [totalusers];
	TotalUsers = totalusers;

	for (int i = 0; i < totalusers; i++)
	{
		j = 0;
		UserList[i] = new User;
		UserList[i]->ReadDataFromFile(fin);//Reads IDs,Fname and Lname

		fin >> arr;
		if (Helper::StringCompare(arr, "-1"))//Updating FriendIDs
		{
			FriendIDs[i] = 0;
		}
		else
		{
			FriendIDs[i] = new char* [10];
			while (!Helper::StringCompare(arr, "-1"))
			{
				temp = Helper::GetStringFromBuffer(arr);
				FriendIDs[i][j] = temp;
				j++;
				temp = 0;
				fin >> arr;

				if (Helper::StringCompare(arr, "-1"))//making rest of the space null
				{
					for (int index = j; index < 10; index++)
					{
						FriendIDs[i][index] = 0;
					}
					FriendIDs[totalusers] = 0;
				}
			}
		}

		fin >> arr;//updating liked pages
		while (!Helper::StringCompare(arr, "-1"))
		{
			pageptr = SearchPageByID(arr);
			UserList[i]->LikePage(pageptr);
			fin >> arr;
			pageptr = 0;

		}

		delete[] temp;
		delete[] pageptr;
	}

	User* userptr = 0;
	for (int i = 0; i < totalusers; i++)
	{
		j = 0;
		if (FriendIDs[i] != 0)
		{
			while (FriendIDs[i][j] != 0)
			{
				userptr = SearchUserByID(FriendIDs[i][j]);
				UserList[i]->AddFriend(userptr);
				j++;
			}
		}
		userptr = 0;
	}

	for (int i = 0; FriendIDs[i] != 0; i++) //Deallocations
	{
		for (int j = 0; FriendIDs[i][j] != 0; j++)
		{
			delete[] FriendIDs[i][j];
			FriendIDs[i][j] = 0;
		}
		delete[] FriendIDs[i];
		/*FriendIDs[i] = 0;*/
	}
	delete[] FriendIDs;
	FriendIDs = 0;

	delete userptr;
	fin.close();
}

void Facebook::LoadPages()
{
	ifstream fin;
	fin.open("SocialNetworkPages.txt");
	int totalpages = 0;
	fin >> totalpages;
	PageList = new Page * [totalpages];
	TotalPages = totalpages;

	for (int i = 0; i < totalpages; i++)
	{
		PageList[i] = new Page;
		PageList[i]->ReadDataFromFile(fin);
	}

	fin.close();

}

void Facebook::LoadPosts()
{
	ifstream fin;
	fin.open("SocialNetworkPosts.txt");
	int totalposts = 0;

	fin >> totalposts;
	Post::SetTotalPosts(totalposts);//required in order to generate new post id when sharing a new memory
	posts = new Post * [totalposts];
	TotalPosts = totalposts;


	for (int i = 0; i < totalposts; i++)
	{
		posts[i] = new Post;
		posts[i]->ReadDataFromFile(fin);

		char temp[80];
		fin >> temp;
		Object* SharedBy;
		SharedBy = SearchObjectByID(temp);
		posts[i]->SetSharedBy(SharedBy);
		SharedBy->AddPostToTimeline(posts[i]);


		fin >> temp;
		int index = 0;
		if ((!Helper::StringCompare(temp, "-1")))//checks if "-1" present in array
		{
			while ((!Helper::StringCompare(temp, "-1")))
			{
				Object* LikedBy;
				LikedBy = SearchObjectByID(temp);
				/*index++;*/
				posts[i]->SetLikedBy(LikedBy);
				fin >> temp;
			}

			/*for(int j = index;j<10;j++)
			{
				LikedBy[j] = 0;
			}*/

		}
	}

	fin.close();
}

void Facebook::LoadComments()
{
	ifstream fin;
	fin.open("SocialNetworkComments.txt");
	int totalcomments = 0;

	fin >> totalcomments;
	comments = new Comment * [totalcomments];
	User::SetTotalComments(totalcomments);

	char ID[10];
	char text[80];
	char postid[30];
	char commentby[10];
	char temp[80];
	for (int i = 0; i < totalcomments; i++)
	{
		comments[i] = new Comment;
		fin >> ID;

		fin >> postid;
		Post* postptr = SearchPostByID(postid);

		fin >> commentby;
		Object* CommentBy = SearchObjectByID(commentby);

		fin.getline(temp, 80);
		for (int j = 1; temp[j - 1] != 0; j++)//j = 1 so " " is skipped at start
		{
			text[j - 1] = temp[j];
		}
		comments[i]->SetValues(ID, text, CommentBy);

		postptr->AddComment(comments[i]);
	}
	fin.close();
}

void Facebook::Load()
{
	LoadPages();
	LoadUsers();
	LoadPosts();
	LoadComments();
}

void Facebook::ViewLikedList(const char* PostID)
{
	Post* ptr = SearchPostByID(PostID);
	if (ptr != 0)
	{
		ptr->PrintLikes();
	}
	else
	{
		cout << "Page not found" << endl;
	}

}

void Facebook::ViewPost(Post * Postptr)
{
	if (Postptr != 0)
	{
		Postptr->Print();
	}
	else
	{
		cout << "Post Not Found!!" << endl;
	}

}

void Facebook::ViewPage(const char* temp)
{
	Page* ptr = SearchPageByID(temp);
	if (ptr != 0)
	{
		ptr->ViewPage();
	}
	else
	{
		cout << "Page Not Found so cannot be Viewed!!" << endl;
	}

}

void Facebook::Run()
{
	Facebook fb;
	Date CurrDate(15, 11, 2017);
	int count = 0;
	fb.Load();

	User* CurrUser = fb.SearchUserByID("u7");

	if (CurrUser != 0)
	{
		CurrUser->PrintName();
		cout << " successfully set as current user" << endl;
	}
	cout << "------------------------------------------------" << endl;
	CurrUser->PrintFriendList();
	cout << "\n-------------------------------------------------" << endl;
	CurrUser->PrintLikedPages();

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Home" << endl;
	cout << "------------------------------------------------------" << endl;
	CurrUser->ViewHome();

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Timeline" << endl;
	cout << "------------------------------------------------------" << endl;
	CurrUser->ViewTimeline();

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Liked List" << endl;
	cout << "------------------------------------------------------" << endl;
	fb.ViewLikedList("post5");

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Like Post" << endl;
	cout << "Command:      View Liked Post" << endl;
	cout << "------------------------------------------------------" << endl;
	Post* ptr = fb.SearchPostByID("post5");
	CurrUser->LikePost(ptr);
	fb.ViewLikedList("post5");

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      Post Comment" << endl;
	cout << "Command:      View Post" << endl;
	cout << "------------------------------------------------------" << endl;
	ptr = fb.SearchPostByID("post4");
	CurrUser->PostComment(ptr, "Good Luck for your Result");
	if (ptr != 0)
	{
		ptr->Print();
	}
	else
		cout << "Page Not Found!!" << endl;

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      Post Comment" << endl;
	cout << "Command:      View Post" << endl;
	cout << "------------------------------------------------------" << endl;
	ptr = fb.SearchPostByID("post8");
	CurrUser->PostComment(ptr, "Thanks for the Wishes");
	if (ptr != 0)
	{
		ptr->Print();
	}
	else
		cout << "Page Not Found!!" << endl;


	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:       SeeYourMemories()" << endl;
	cout << "------------------------------------------------------" << endl;
	CurrUser->SeeYourMemories();

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:       ViewPage()" << endl;
	cout << "------------------------------------------------------" << endl;
	fb.ViewPage("p1");

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:       ShareMemory()" << endl;
	cout << "Command:      ViewTimeline()" << endl;
	cout << "------------------------------------------------------" << endl;
	ptr = fb.SearchPostByID("post10");
	CurrUser->ShareMemory(ptr, "Never thought I will be specialist in this field...");
	CurrUser->ViewTimeline();	

	User* CurrUser2 = fb.SearchUserByID("u11");
	if (CurrUser2 != 0)
	{
		cout << "------------------------------------------" << endl;
		CurrUser2->PrintName();
		cout << " successfully set as current user" << endl;
	}
	cout << "------------------------------------------------" << endl;
	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Home" << endl;
	cout << "------------------------------------------------------" << endl;
	CurrUser2->ViewHome();

	cout << endl << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "Command:      View Timeline" << endl;
	cout << "------------------------------------------------------" << endl;
	CurrUser2->ViewTimeline();
}

//static variables
int Facebook::TotalUsers = 0;
int Facebook::TotalPages = 0;
int Facebook::TotalPosts = 0;
int User::OverallComments = 0;
int Post::TotalPosts = 0;

int main()
{
	Facebook::Run();

	return 0;
}

