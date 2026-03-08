#include <iostream>
#include <cctype>
#include <random>
using namespace std;
void winnerAnnounced(int, double, double, int, int, int);
void scoreTracked(int, int&, double&, double&, int&, int&, int&);
int gameTime(char*, const char*);
const char* randomCPU();
void choiceMaker(char* );
bool inputVal(char* );
bool charCompare(char*, const char*);
int main()
{
	char choice[15];
	int games=0, wins=0, loss=0, tie=0;
	double human=0;
	double robo=0;
	cout << "Hello, I'm the rock paper scissors champion, challenge me or die.\n" << endl;
	while (true)
	{
		choiceMaker(choice);
		if (charCompare(choice, "quit"))														//ends the loop that will go forever otherwise
		{
			winnerAnnounced(games, human, robo, wins, loss, tie);
			return 0;																								//might add more messages based on how many games you played 
		}
		scoreTracked(gameTime(choice, randomCPU()), games, human, robo, wins, loss, tie);			//so clean here
	}
}
void choiceMaker(char* choice)
{
	cout << "1 point for a win : 0 points for a loss : 0.5 points for a draw\n" << endl;
	cout << "Enter:\n\nRock\n\nPaper\n\nScissors\n\nQuit\n\n" << endl;
	cin.width(15);
	cin >> choice;													//got some protection against big inputs but its not perfect
	cin.ignore(1000, '\n');
	while (!inputVal(choice))																//when the imput val fails we try again
	{
		cout << "\nInvalid input, don't be a baby and play >:(\n" << endl;
		cout << "Enter:\n\nRock\n\nPaper\n\nScissors\n\nQuit\n\n" << endl;
		cin.width(15); 
		cin >> choice;
		cin.ignore(1000, '\n');
																											//changed to avoid overflow if user inputs more than 14 characters
	}
}
bool inputVal(char* choice)																			//when i took egr125 i did not understand boolean stuff at all, but now having taken a different class about it, its pretty useful might change this to int though
{
	const char* valid[4] = { "rock", "paper", "scissors", "quit" };
	for (const char* comp : valid)								//gonn comnpare the input to each possible option
	{
		if (charCompare(choice, comp))					//send it to our manual char compare function, strcmp seemed out of spirit of the assignment
		{
			return true;									//keeps out input loop going
		}
	}
	return false; 
}
bool charCompare(char* choice, const char* options)																//i considered using strcmp but that felt out of the spirit of the assignment
{
	while (*choice != '\0' && *options != '\0')									//this compares each individual char in the array until both are at the null character
	{
		if (tolower(*choice) != *options)						//change to lowercase so that it doesn't matter
			return false;										//if they are ever different immediately fail the check
		choice++;												//then do it for the next character
		options++;
	}
	return *choice == '\0' && *options == '\0';							//this will prevent things like rockk ffrom being valid inputs
}
const char* randomCPU()
{
	static std::default_random_engine roll;
	static std::uniform_int_distribution<int> RPS(0, 2);					//pretty simply 
	const char* random[3] = { "rock", "paper", "scissors" };
	int i = RPS(roll);
	cout << endl << "I rolled " << random[i] << endl;
	return random[i];

}
int gameTime(char* player, const char* CPU)
{
	const char* compare[3] = { "rock", "paper", "scissors" };
	const char* contrast[3] = { "paper", "scissors", "rock" };
	for (int i=0; i<3; i++)
	{
		if (charCompare(player, compare[i]) && charCompare((char*)CPU, contrast[i]))										//casting the CPU char array because that's what made it work
		{
			cout << "\nAs expected, I am victorious" << endl;
			return -1;																					//using an integer to signify the result, and using our charCompare, this is why we made it seperate from the rest of the input val
		}
		if (charCompare((char*)CPU, compare[i]) && charCompare(player, contrast[i]))
		{
			cout << "\nyou.... won? Is this a joke? You must be cheating, I'm calling the police I want a do-over" << endl;
			return 1;
		}
		
	}
	if (charCompare(player, CPU))
	{
		cout << "\nTie game, you got lucky bub" << endl;
		return 0;
	}	
	else
	{
		cout << "\nSomething has gone terribly wrong..." << endl;
		return 2;
	}																							//need to compare the CPU to what beats the player, if it matches the CPU wins
}
void scoreTracked(int result, int &games, double &human, double &robo, int& w, int& l, int& t)
{
	if (result == 0)												//just check the result and then add to the appropriate totals
	{
		t++;
		games++;
		human += 0.5;
		robo += 0.5;
	}
	if (result == 1)
	{
		w++;
		games++;
		human += 1;
	}
	if (result == -1)
	{
		l++;
		games++;
		robo += 1;
	}
	cout << "\nThe number of games played: " << games << endl << "Your score: " << human << " " << w << "W/" << l << "L/" << t << "T" << endl << "My score: " << robo << " " << l << "W/" << w << "L/" << t << "T" << endl << endl;
}

void winnerAnnounced(int games, double human, double robo, int w, int l, int t)
{
	if (games == 0)
	{
		cout << "\nYou're shaking with fear, I think its best you ran off where you came from buddy" << endl;
		return;
	}
	if (human > robo)
	{
		cout << "\nOf course you would decide to stop now. Over the course of " << games << " games YOU WON?!?! with a score of " << human << " points with a record of " << w << "W/" << l << "L/" << t << "T" << " to my " << robo << " points with a record of " << l << "W/" << w << "L/" << t << "T" << endl;
		cout << "\n.....\n\n.......\n\n.........\n\n This insult will not be forgotten..." << endl;
	}
	if (human < robo)
	{
		cout << "Wow, you're a pretty sore loser huh? Giving up already? As expected I destroyed you with a score of " << robo << " points with a record of " << l << "W/" << w << "L/" << t << "T" << " to your paltry " << human << " points with a record of " << w << "W/" << l << "L/" << t << "T" << " over " << games << "games" << endl;
		cout << "It was an easy victory for me" << endl;
	}
	if (human == robo)
	{
		cout << "Yeah I was getting bored anyway, let's see here the score was- A TIE??!!! THIS CANNOT BE RIGHT I WANT AN APPEAL NO WAY WE HAD A SCORE OF YOUR " << human << " points with a record of " << w << "W/" << l << "L/" << t << "T" << " TO MY " << robo << " points with a record of " << l << "W/" << w << "L/" << t << "T" << " in " << games << "games" << endl;
	}
	return;
}
//I had some fun with the robot personality