//Maximum number of characters in one line:
const int64_t MAX_LINE = 100000;
char name[MAX_LINE], inputLine[MAX_LINE];

//The below example is from jmaze in BOSPRE 2019
//Note that, because this is just a demonstration, the below example is half-pseudocode, so some of the variables are not declared

int main() {
    /**
     * The following line makes std::cin go much faster,
     * but it also means that you CAN NOT use any of the <cstdio>
     * functions, like scanf, printf, fgets, etc.
     * if you are using std::cin and std::cout for I/O
    */
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {
        /**
         * Many BOSPRE problems require you to read in all of the test cases in the file
         * and the first line of a test case is usually a name line,
         * like the following:
         * -- TEST CASE 1 --
         * You are required to output this line again when you output your answer,
         * which is why we store this line in the "testCaseName" variable for later.
        */
        std::cin.getline(testCaseName, MAX_LINE);
        //Once we hit EOF, we know we've gone through all the test cases.
        if (std::cin.eof()) break;

        /**
         * Notice how I am using getline() first, and then making an input stream in order to read the integers.
         * I could be more direct, like this:
         *   std::cin >> numRows >> numColumns;
         * However, this would cause the next call to getline()
         * to return an empty line,
         * because reading the integers directly from std::cin
         * means that any newline after
         * 
         * In general, if you are using std::cin.getline() anywhere in your program repeatedly,
         * then it is best if you read in the whole input using only getline().
        */
        std::cin.getline(inputLine, MAX_LINE);
        std::istringstream firstLineStream(inputLine);
        firstLineStream >> numRows >> numColumns;

        while (numRows--) {
            std::cin.getline(inputLine, MAX_LINE);
            std::istringstream curLineStream(inputLine);
            
            /**
             * The operation "curLineStream >> curToken" reads in a single token
             * from the current line, and stores it in the "curToken" variable.
             * Here, a "token" is a list of non-whitespace characters.
             * For example, "3", "X", "abc345sd", and "345:1234:dfg" are all tokens.
             * This operation will fail once we have read all of the tokens from this line.
             * so the while loop will end once there are no more tokens.
            */
            std::string curToken;
            while (curLineStream >> curToken) {
                //If the current string starts with G...
                if (curToken[0] == 'G') { /* Do stuff */ }
                //If the current string starts with X...
                else if (curToken[0] == 'X') { /* Do stuff */ }
                //If the current string has a ':' character...
                else if (curToken.find(':') != std::string::npos) {
                    //Parse the two numbers, i.e. parse "32:234" as the coordinates (32, 234)
                    int64_t coordX, coordY;

                    curTokenStream >> coordX;
                    //Ignore one character (i.e. the colon)
                    curTokenStream.ignore(1);
                    curTokenStream >> coordY;
                    //Do stuff...
                }
                //Otherwise...
                else {
                    //Parse the number
                    int64_t distance;
                    curTokenStream >> distance;
                    //Do stuff...
                }
            }
        }

        //Calculate answer...

        std::cout << testCaseName << "\n";
        while (curVertex != goalVertex) {
            std::cout << curVertex.x << ":" << curVertex.y << " ";
            curVertex = pred[curVertex.x][curVertex.y];
        }
        std::cout << curVertex.x << ":" << curVertex.y << "\n";
    }
}