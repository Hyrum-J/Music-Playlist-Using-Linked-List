#include <iostream>
#include <string>

using namespace std;

struct song
{
	int Id;
	string name;
	string artistName;
	song* nextSong = NULL;
	song* prevSong = NULL;
};

song* head = NULL;
song* current = NULL;
song* nextSong = NULL;
song* previous = NULL;
int listLength = 0;

string initialSongs[20] =
{
	"Religiously", "Stan", "Mean", "Spinnin", "Nancy Mulligan", "Payphone", "Replay", "Mr. Brightside", "Toxic", "Beggin'", "Pompeii", "Viva La Vida", "SNAP", "Smooth Criminal", "Secrets", "me & ur ghost", "Numb Little Bug", "This Side of a Dust Cloud", "Waves", "865"
};

string initialArtist[20] =
{
	"Bailey Zimmerman", "Eminem", "Taylor Swift", "Connor Price", "Ed Sheeran", "Maroon 5", "Iyaz", "The Killers", "BoyWithUke", "Maneskin", "Bastille", "Coldplay", "Rosa Linn", "Micheal Jackson", "One Republic", "blackbear", "Em Beihold", "Morgan Wallen", "Dean Lewis", "Morgan Wallen"
};

void insert(string songName, int id, string artist)
{
	struct song* newSong = new song;
	newSong->Id = id;
	newSong->name = songName;
	newSong->prevSong = current;
	newSong->artistName = artist;
	previous = current;
	listLength = newSong->Id;
	current = newSong;

	if (head == NULL)
	{
		head = newSong;
		current->nextSong = NULL;
		current->prevSong = NULL;
	}
	else
	{

		previous->nextSong = current;
		newSong->nextSong = head;
		head->prevSong = current;
	}
}

void deleteItem(int id)
{
	song* elementWasOn;
	if (current->Id == id)
	{
		elementWasOn = current->nextSong;
	}
	else
	{
		elementWasOn = current;
	}
	song* lastSong = head->prevSong;
	current = head;
	for (int i = 0; i < listLength; i++)
	{
		if (current->Id == id)
		{
			if (current->Id == head->Id)
			{
				head = head->nextSong;
			}
			int deletedId = current->Id;
			song* deletedSong = current;
			while (current->Id >= deletedId)
			{
				current->Id--;
				current = current->nextSong;
			}
			current = deletedSong;
			previous = current->prevSong;
			previous->nextSong = current->nextSong;
			nextSong = current->nextSong;
			nextSong->prevSong = previous;
			listLength = lastSong->Id;
			i = listLength;
			current = elementWasOn;

		}
		else
		{
			current = current->nextSong;
		}
	}
}

void find(string name, int song)
{
	bool found = false;
	current = head;
	for (int i = 0; i < listLength; i++)
	{
		if (current->name == name)
		{
			cout << "Song name: " << name << " found at location " << current << endl;
			found = true;
			i = listLength;
		}
		else
		{
			current = current->nextSong;
		}
	}

	if (!found)
	{
		cout << "Song could not be found" << endl;
	}
}

void find(int Id)
{
	bool found = false;
	current = head;
	for (int i = 0; i < listLength; i++)
	{
		if (current->Id == Id)
		{
			cout << "Song Id: " << Id << " found at location " << current << endl;
			found = true;
			i = listLength;
		}
		else
		{
			current = current->nextSong;
		}
	}

	if (!found)
	{
		cout << " Song could not be found " << endl;
	}
}

void find(string artist)
{
	bool found = false;
	current = head->prevSong;
	for (int i = 0; i < listLength; i++)
	{
		current = current->nextSong;
		if (current->artistName == artist)
		{
			cout << "Song artist: " << artist << " found at location " << current << endl;
			found = true;
		}
	}

	if (!found)
	{
		cout << "Song could not be found" << endl;
	}
}

bool choice() 
{
	char userChoice;
	cout << "Commands: " << endl;
	cout << "N for next song, P for previous song, F for find song" << endl;
	cout << "D for delete song, A for add song, E for exit" << endl;
	cin >> userChoice;
	userChoice = toupper(userChoice);
	if (userChoice == 'N')
	{
		current = current->nextSong;
	}
	else if (userChoice == 'P')
	{
		current = current->prevSong;
	}
	else if (userChoice == 'F')
	{
		cin.ignore();
		char inputChoice;
		string userInputString;
		int userInputInt;
		cout << "How would you like to search for the song? " << endl;
		cout << "S for song title, I for Id num, A for Artist: ";
		cin >> inputChoice;
		inputChoice = toupper(inputChoice);
		if (inputChoice == 'S')
		{
			cin.ignore();
			cout << "Please type the name of the song: ";
			getline(cin, userInputString);
			find(userInputString, 1);
		}
		else if (inputChoice == 'I')
		{
			cout << "Please type the Id of the song: ";
			cin >> userInputInt;
			find(userInputInt);
		}
		else if (inputChoice == 'A')
		{
			cin.ignore();
			cout << "Please type the name of the Artist: ";
			getline(cin, userInputString);
			find(userInputString);
		}
		else
		{
			cout << "Please type a valid letter" << endl;
			choice();
		}

	}
	else if (userChoice == 'D')
	{
		int userInput;
		cout << "Please type the Id you would like deleted: ";
		cin >> userInput;
		deleteItem(userInput);
		cout << "Instance Deleted" << endl;
	}
	else if (userChoice == 'A')
	{
		cin.ignore();
		string songName;
		int songId;
		string artistName;
		cout << "Please type the name of the song: ";
		getline(cin, songName);
		songId = listLength + 1;
		cout << "Please type the name of the artist: ";
		getline(cin, artistName);
		current = head->prevSong;
		insert(songName, songId, artistName);
	}
	else if (userChoice == 'E')
	{
		return false;
	}
	return true;
}

void print()
{	
	cout << current->Id << endl;
	cout << "Current Song: " << current->name << endl;
	cout << "Played By: " << current->artistName << endl;
}

int main()
{
	bool playing = true;
	for (int i = 1; i <= 20; i++)
	{
		insert(initialSongs[i - 1], i, initialArtist[i - 1]);
	}
	current = head;
	print();

	while (playing)
	{
		playing = choice();
		print();
	}

	return 0;
}