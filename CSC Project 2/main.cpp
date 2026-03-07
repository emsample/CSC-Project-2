#include <iostream>
#include <random>
using namespace std;
int gameTime(char* player, const char* CPU);
const char* randomCPU();
void choiceMaker(char* select);
bool inputVal(char* check);
bool charCompare(char* input, const char* options);
int main()
{
	char choice[15];
	cout << "Hello, I'm the rock paper scissors champion, challenge me or die.\n" << endl;
	choiceMaker(choice);
	if (charCompare(choice, "quit"))
	{
		cout << "\nSore loser, or just scared to take me on?";													//might add more messages based on how many games you played but maybe over the top
		return 0;
	}
}
void choiceMaker(char* select)
{
	cout << "Enter:\n\nRock\n\nPaper\n\nScissors\n\nQuit\n\n";
	cin >> select;
	while (!inputVal(select))
	{
		cout << "\nInvalid input, don't be a baby and play >:(\n" << endl;
		cout << "Enter:\n\nRock\n\nPaper\n\nScissors\n\nQuit\n\n";
		cin >> select;
	}
}
bool inputVal(char* check)																			//when i took egr125 i did not understand boolean stuff at all, but now having taken a different class about it, its pretty useful might change this to int though
{
	const char* valid[4] = { "rock", "paper", "scissors", "quit" };
	for (const char* comp : valid)
	{
		if (charCompare(check, comp)) 
		{
			return true;
		}
	}
	return false; 
}
bool charCompare(char* input, const char* options)																//i considered using strcmp but that felt out of the spirit of the assignment
{
	while (*input != '\0' && *options != '\0')
	{
		if (tolower(*input) != *options)
			return false;
		input++;
		options++;
	}
	return *input == '\0' && *options == '\0';
}
const char* randomCPU()
{
	static std::default_random_engine roll;
	static std::uniform_int_distribution<int> RPS(0, 2);
	const char* random[3] = { "rock", "paper", "scissors" };
	int i = RPS(roll);
	return random[i];

}
int gameTime(char* player, const char* CPU)
{
	const char* compare[3] = { "rock", "paper", "scissors" };
	const char* contrast[3] = { "paper", "scissors", "rock" };
	if (charCompare(player, CPU))
		return 0;
	for (const char* look : compare)
	{
		for (const char* see : contrast)
		{
			if (charCompare(player, look) && charCompare((char*)CPU,)
		}
	}
																								//need to compare the CPU to what beats the player, if it matches the CPU wins
}