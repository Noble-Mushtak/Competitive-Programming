import java.io.*;
import java.util.*;

public class RockPaperScissors {
    private static final String[] choices = {"rock", "paper", "scissors"};
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        boolean completedTestCaseBefore = false;
        
        while (true) {
            int numPlayers = in.nextInt();
            //If the number of players is 0, then we've reached the end of the file, so exit
            if (numPlayers == 0) break;
            int numGamesPerPair = in.nextInt();
            
            int[] wins = new int[numPlayers];
            int[] losses = new int[numPlayers];

            int numGames = numGamesPerPair*numPlayers*(numPlayers-1)/2;
            //Repeat the following code numGames times:
            while (numGames-- > 0) {
                //Subtract by 1 to go from 1-based indexing -> 0-based indexing
                int firstPlayerIndex = in.nextInt()-1;
                //By finding the index of the string in an array, we have effectively converted the strings "rock"/"paper"/"scissors" into the numbers 0/1/2, respectively
                //This is good, because numbers are easier to work with than strings
                int firstPlayerChoice = Arrays.asList(choices).indexOf(in.next());
                int secondPlayerIndex = in.nextInt()-1;
                int secondPlayerChoice = Arrays.asList(choices).indexOf(in.next());
                
                //If either of the choice ints are -1, then the strings we read in was not "rock"/"paper"/"scissors"
                //Hopefully, it will never come to this.
                if ((firstPlayerChoice == -1) || (secondPlayerChoice == -1)) {
                    System.err.println("Bad input");
                    System.exit(1);
                }

                //Find the difference in the player's choices mod 3.
                int choiceDiffs = secondPlayerChoice-firstPlayerChoice;
                if (choiceDiffs < 0) choiceDiffs += 3;

                //If choiceDiffs is 1, then either:
                // * Second player chose paper (1), first player chose rock (0)
                // * Second player chose scissors (2), first player chose paper
                // * Second player chose rock (0), first player chose scissors (2)
                //Notice that in all three of these scenarios, the second player wins and the first player loses.
                if (choiceDiffs == 1) {
                    wins[secondPlayerIndex]++;
                    losses[firstPlayerIndex]++;
                }
                //If choiceDiffs is 2, then you can do a similar analysis to that above and find that, in all three scenarios, the first player wins and the second player loses.
                else if (choiceDiffs == 2) {
                    wins[firstPlayerIndex]++;
                    losses[secondPlayerIndex]++;
                }
                //Otherwise, if choiceDiffs is 0, then both players picked the same thing, so do nothing
            }

            //If we've done a test case before, then we need to output a blank line:
            if (completedTestCaseBefore) {
                System.out.println("");
            }
            
            for (int playerIndex = 0; playerIndex < numPlayers; playerIndex++) {
                if (wins[playerIndex]+losses[playerIndex] == 0) {
                    System.out.println("-");
                } else {
                    double winAverage = ((double)wins[playerIndex])/(wins[playerIndex]+losses[playerIndex]);
                    System.out.printf("%.3f\n", winAverage);
                }
            }
            //We completed at least one test case at this point!
            completedTestCaseBefore = true;
        }
    }
}