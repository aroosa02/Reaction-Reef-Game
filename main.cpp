#include "header.h"

int main(){
        int width = 1200;
        int height = 600;

        int screenW = GetSystemMetrics(SM_CXSCREEN);
        int screenH = GetSystemMetrics(SM_CYSCREEN);

        int x = (screenW - width) / 2;
        int y = (screenH - height) / 2;

        initwindow(width, height, "Reaction Reef", x, y);


    // --- Symbols
    Symbol symbols[]={{'@','A','L',2,"Player1: A | Player2: L"},{'#','S','K',2,"Player1: S | Player2: K"},
                      {'$','D',';',2,"Player1: D | Player2: ; "},{'%','F','\'',2,"Player1: F | Player2: '"},
                      {'&','G','H',1,"Player1: G | Player2: H "},{'*','Q','P',1,"Player1: Q | Player2: P"},
                      {'+','W','O',2,"Player1: W | Player2: O"},{'~','E','I',1,"Player1: E | Player2: I"}};
    int numSymbols=sizeof(symbols)/sizeof(Symbol);

    // --- Animal words for round 2
    const char* animals[]={"Tiger","Lion","Fish","Bear","Crow","Zebra","Rat","Bull"};
    int numAnimals=sizeof(animals)/sizeof(animals[0]);

    bool playAgain=true;
    
    while(playAgain){
        int roundNumber=1;
        int round1_p1 = 0, round1_p2 = 0;
        int round2_p1 = 0, round2_p2 = 0;
        int round3_p1 = 0, round3_p2 = 0;
        bool playedRound3 = false;
        
        while(roundNumber<=3){
            int p1=0,p2=0;
            const char* roundName;
            if(roundNumber==1) roundName="ROUND 1: Symbols & Letters!";
            else if(roundNumber==2) roundName="ROUND 2: Type your Animal!";
            else roundName="ROUND 3: Crazy Shuffle!";

            // Round Start
            setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width);
            showCenteredMessage(roundName,width,height,4,LIGHTCYAN); setvisualpage(page); page=1-page; soundRound(); delay(2000);

            // For Round 3, show choice screen with current scores
            if(roundNumber == 3){
                playedRound3 = showRound3Choice(width, height, round1_p1, round1_p2, round2_p1, round2_p2);
                if(!playedRound3){
                    // Skip Round 3 - show final scoreboard
                    int total_p1 = round1_p1 + round2_p1;
                    int total_p2 = round1_p2 + round2_p2;
                    drawFinalScoreboard(round1_p1, round1_p2, round2_p1, round2_p2, 
                                       round3_p1, round3_p2, total_p1, total_p2, 
                                       width, height, false);
                    break;
                }
                
                // Clear and show round start
                setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width);
                showCenteredMessage("ROUND 3 START!", width, height, 5, RED);
                setvisualpage(page); page=1-page;
                soundRound();
                delay(1500);
            }

            while(p1<10 && p2<10){
                setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width); drawScoreboard(p1,p2,width); setvisualpage(page); page=1-page;
                
                // Different delay based on round
                int delayms;
                if(roundNumber==1) delayms=1000+rand()%2500;
                else if(roundNumber==2) delayms=1000+rand()%2500;
                else delayms=500+rand()%1000; // Faster for Round 3
                
                delay(delayms);

                Symbol sym; string word1, word2; char displayChar1, displayChar2;
                bool useSymbol=false;

                if(roundNumber==1){ 
                    sym=symbols[rand()%numSymbols]; 
                    displayChar1=sym.keyP1; displayChar2=sym.keyP2; useSymbol=true; 
                }
            else if(roundNumber == 2){
    // ===== ROUND 2: SIMULTANEOUS TYPING DUEL =====

    // Pick two DIFFERENT words with different starting letters
    string p1Word, p2Word;
    do {
        p1Word = animals[rand() % numAnimals];
        p2Word = animals[rand() % numAnimals];
    } while(p1Word == p2Word || toupper(p1Word[0]) == toupper(p2Word[0]));

    string typed1 = "";
    string typed2 = "";
    bool done1 = false;
    bool done2 = false;

    const int ROUND2_TIME = 10; // seconds
    unsigned long startTime = GetTickCount();

    clearKeyboardBuffer();

    while(true){
        int elapsed = (GetTickCount() - startTime) / 1000;
        int timeLeft = ROUND2_TIME - elapsed;

        if(timeLeft <= 0) break;
        if(done1 && done2) break;

        // ===== DRAW =====
        setactivepage(page);
        cleardevice();
        drawCosmicBackground(width, height);
        drawHeader(width);
        drawScoreboard(p1, p2, width);

        drawRound2Words(p1Word, p2Word, width, height);
        drawTypingProgress(p1Word, typed1, 1, width, height);
        drawTypingProgress(p2Word, typed2, 2, width, height);
        drawTimer(timeLeft, width, height);

        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(LIGHTGRAY);
        outtextxy(width/2 - 230, height - 80,
                  (char*)"BOTH PLAYERS TYPE AT THE SAME TIME!");

        setvisualpage(page);
        page = 1 - page;

        if(kbhit()){
            int ch = getch();
            if(ch == 0 || ch == 224){
                getch();
                continue;
            }

            char key = toupper((char)ch);

            bool hit = false;

            // Player 1 typing
            if(!done1 && typed1.length() < p1Word.length() &&
               key == toupper(p1Word[typed1.length()])){
                typed1 += key;
                hit = true;
                if(typed1.length() == p1Word.length()) done1 = true;
            }

            // Player 2 typing
            if(!done2 && typed2.length() < p2Word.length() &&
               key == toupper(p2Word[typed2.length()])){
                typed2 += key;
                hit = true;
                if(typed2.length() == p2Word.length()) done2 = true;
            }

            if(hit) soundHit();
            else soundMiss();
        }

        delay(30);
    }

    // ===== SCORING =====
    if(done1 && !done2){
        p1 += 2;
        drawFeedback("PLAYER 1 WINS ROUND 2!", LIGHTGREEN);
    }
    else if(done2 && !done1){
        p2 += 2;
        drawFeedback("PLAYER 2 WINS ROUND 2!", LIGHTGREEN);
    }
    else if(done1 && done2){
        p1 += 1;
        p2 += 1;
        drawFeedback("BOTH PLAYERS FINISHED! +1 EACH", YELLOW);
    }
    else{
        drawFeedback("TIME UP! NO POINTS", RED);
    }

    // ===== FINAL DISPLAY =====
    setactivepage(page);
    cleardevice();
    drawCosmicBackground(width, height);
    drawHeader(width);
    drawScoreboard(p1, p2, width);

    drawRound2Words(p1Word, p2Word, width, height);
    drawTypingProgress(p1Word, typed1, 1, width, height);
    drawTypingProgress(p2Word, typed2, 2, width, height);

    setvisualpage(page);
    page = 1 - page;

    delay(2000);
    continue;
}

                else { 
                    // ROUND 3: Mix of both rounds with strict timers
                    // Randomly choose between symbol mode and word mode
                    if(rand()%2==0){ 
                        // SYMBOL MODE (like Round 1) - 2 seconds to react
                        sym=symbols[rand()%numSymbols]; 
                        displayChar1=sym.keyP1; 
                        displayChar2=sym.keyP2; 
                        useSymbol=true;
                        
                        // Display symbol with timer
                        setactivepage(page); cleardevice(); 
                        drawCosmicBackground(width,height); 
                        drawHeader(width); 
                        drawScoreboard(p1,p2,width);
                        drawSymbolWithGlow(sym,width,height); 
                        drawKeyPanel(sym,width,height);
                        drawRound3Timer(2, width, height, true);
                        setvisualpage(page); page=1-page;
                        clearKeyboardBuffer();
                        unsigned long start=GetTickCount(); 
                        bool reacted=false;
                        
                        while(!reacted){
                            // Check time left
                            unsigned long currentTime = GetTickCount();
                            int timeLeft = 2 - ((currentTime - start) / 1000);
                            
                            if(timeLeft <= 0){
                                // Time's up
                                setactivepage(page); cleardevice(); 
                                drawCosmicBackground(width,height); 
                                drawHeader(width); 
                                drawScoreboard(p1,p2,width);
                                drawFeedback("2 seconds passed! Too slow!", RED);
                                soundMiss();
                                setvisualpage(page); page=1-page;
                                reacted=true;
                                delay(1000);
                                break;
                            }
                            
                            // Update timer display
                            setactivepage(page); cleardevice(); 
                            drawCosmicBackground(width,height); 
                            drawHeader(width); 
                            drawScoreboard(p1,p2,width);
                            drawSymbolWithGlow(sym,width,height); 
                            drawKeyPanel(sym,width,height);
                            drawRound3Timer(timeLeft, width, height, true);
                            setvisualpage(page); page=1-page;
                            
                            if(kbhit()){
                                int ch=getch(); 
                                if(ch==0||ch==224){ 
                                    getch(); 
                                    continue;
                                }
                                char key=toupper((char)ch);
                                
                                if(key==toupper(sym.keyP1)){ 
                                    p1+=sym.points; 
                                    if(p1<0) p1=0; 
                                    drawFeedback(">>> Player 1 HIT! <<<",LIGHTGREEN); 
                                    soundHit();
                                    reacted=true;
                                }
                                else if(key==toupper(sym.keyP2)){ 
                                    p2+=sym.points; 
                                    if(p2<0) p2=0; 
                                    drawFeedback(">>> Player 2 HIT! <<<",LIGHTGREEN); 
                                    soundHit();
                                    reacted=true;
                                }
                                else { 
                                    drawFeedback("Wrong key! No points.",RED); 
                                    soundMiss(); 
                                    reacted=true;
                                }
                                
                                setvisualpage(page); page=1-page;
                            }
                            delay(30);
                        }
                        delay(800);
                        continue;
                    }
                    else { 
                        // WORD MODE (like Round 2) - 5 seconds to type full word
                        // Ensure words start with different letters
                        do {
                            word1 = animals[rand()%numAnimals];
                            word2 = animals[rand()%numAnimals];
                        } while(word2 == word1 || toupper(word1[0]) == toupper(word2[0]));
                        
                        useSymbol=false;
                        
                        // Display words with 5-second timer
                        setactivepage(page); cleardevice(); 
                        drawCosmicBackground(width,height); 
                        drawHeader(width); 
                        drawScoreboard(p1,p2,width);
                        drawRound2Words(word1, word2, width, height);
                        drawRound3Timer(5, width, height, false);
                        
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                        setcolor(LIGHTGRAY);
                        outtextxy(width/2 - textwidth("Type first letter FAST to become active!")/2, height-100, 
                                 (char*)"Type first letter FAST to become active!");
                        
                        setvisualpage(page); page=1-page;

                        // Wait for first key press to determine active player - with 2 second limit
                        int activePlayer = 0;
                        char activeFirstChar = 0;
                        string targetWord, typedWord;
                        unsigned long reactionStart = 0;
                        bool firstLetterTimeout = false;
                        unsigned long firstLetterStart = GetTickCount();
                        
                        while(activePlayer == 0){
                            // Check if 2 seconds passed for first letter
                            if(GetTickCount() - firstLetterStart > 2000){
                                firstLetterTimeout = true;
                                break;
                            }
                            
                            if(kbhit()){
                                int ch=getch(); 
                                if(ch==0 || ch==224) { 
                                    getch(); 
                                    continue; 
                                }
                                
                                char key=toupper((char)ch);
                                
                                if(key == toupper(word1[0])){
                                    activePlayer = 1;
                                    activeFirstChar = toupper(word1[0]);
                                    targetWord = word1;
                                    reactionStart = GetTickCount();
                                    soundHit();
                                }
                                else if(key == toupper(word2[0])){
                                    activePlayer = 2;
                                    activeFirstChar = toupper(word2[0]);
                                    targetWord = word2;
                                    reactionStart = GetTickCount();
                                    soundHit();
                                }
                                else{
                                    drawFeedback("Wrong first letter!", RED);
                                    soundMiss();
                                    setvisualpage(page); page=1-page;
                                    delay(200);
                                }
                            }
                            delay(50);
                        }
                        
                        if(firstLetterTimeout){
                            // No one pressed first letter in time
                            setactivepage(page); cleardevice(); 
                            drawCosmicBackground(width,height); 
                            drawHeader(width); 
                            drawScoreboard(p1,p2,width);
                            drawFeedback("No first letter in 2 seconds! Next round.", YELLOW);
                            setvisualpage(page); page=1-page;
                            delay(1200);
                            continue;
                        }

                        // Now active player types the full word within 5 seconds
                        typedWord = "";
                        typedWord += activeFirstChar;
                        
                        bool wordCompleted = false;
                        bool timeout = false;
                        
                        while(!wordCompleted && !timeout){
                            // Calculate time left (5 seconds total)
                            unsigned long currentTime = GetTickCount();
                            int timeLeft = 5 - ((currentTime - reactionStart) / 1000);
                            
                            if(timeLeft <= 0){
                                timeout = true;
                                break;
                            }
                            
                            // Redraw screen with progress and timer
                            setactivepage(page); cleardevice(); 
                            drawCosmicBackground(width,height); 
                            drawHeader(width); 
                            drawScoreboard(p1,p2,width);
                            drawRound2Words(word1, word2, width, height);
                            drawTypingProgress(targetWord, typedWord, activePlayer, width, height);
                            drawRound3Timer(timeLeft, width, height, false);
                            
                            // Show active player
                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                            setcolor(YELLOW);
                            char playerMsg[50];
                            sprintf(playerMsg, "Player %d typing... %d sec left!", activePlayer, timeLeft);
                            outtextxy(width/2 - textwidth(playerMsg)/2, 200, playerMsg);
                            
                            setvisualpage(page); page=1-page;
                            
                            // Check for keyboard input
                            if(kbhit()){
                                int ch=getch(); 
                                if(ch==0 || ch==224) { 
                                    getch(); 
                                    continue; 
                                }
                                
                                char key=toupper((char)ch);
                                
                                // Check if it's backspace
                                if(ch == 8 || ch == 127){ // Backspace
                                    if(typedWord.length() > 1){
                                        typedWord = typedWord.substr(0, typedWord.length()-1);
                                    }
                                }
                                // Check if it's the next correct character
                                else if(typedWord.length() < targetWord.length() && 
                                       key == toupper(targetWord[typedWord.length()])){
                                    typedWord += key;
                                    soundHit();
                                    
                                    // Check if word is complete
                                    if(typedWord.length() == targetWord.length()){
                                        wordCompleted = true;
                                    }
                                }
                                else{
                                    drawFeedback("Wrong letter!", RED);
                                    soundMiss();
                                    setvisualpage(page); page=1-page;
                                    delay(100);
                                }
                            }
                            
                            delay(50);
                        }
                        
                        // Process result
if(wordCompleted){
    if(activePlayer == 1){
        p1 += 2;
    } else {
        p2 += 2;
    }

    // SHOW FULL WORD COMPLETION
    setactivepage(page);
    cleardevice();
    drawCosmicBackground(width, height);
    drawHeader(width);
    drawScoreboard(p1, p2, width);

    drawRound2Words(word1, word2, width, height);  // display both words
    drawTypingProgress(targetWord, targetWord, activePlayer, width, height);  // full typed word

    drawFeedback("WORD COMPLETED!", LIGHTGREEN);

    setvisualpage(page);
    page = 1 - page;

    soundHit();
    delay(1500);
}
else if(timeout){
    setactivepage(page);
    cleardevice();
    drawCosmicBackground(width, height);
    drawHeader(width);
    drawScoreboard(p1, p2, width);
    drawRound2Words(word1, word2, width, height);  // still show words
    drawTypingProgress(targetWord, typedWord, activePlayer, width, height);

    drawFeedback("Time's up! Word not completed.", YELLOW);

    setvisualpage(page);
    page = 1 - page;

    soundMiss();
    delay(1500);
                            continue;
}


                    }
                }

                // This part is only for Rounds 1 (Round 2 and 3 have continue statements)
                if(roundNumber == 1){
                    // Display for Round 1
                    setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width); drawScoreboard(p1,p2,width);
                    drawSymbolWithGlow(sym,width,height); 
                    drawKeyPanel(sym,width,height);
                    setvisualpage(page); page=1-page;
                    clearKeyboardBuffer();
                    unsigned long start=GetTickCount(); bool reacted=false;
                    while(!reacted){
                        if(kbhit()){
                            int ch=getch(); if(ch==0||ch==224){ getch(); continue;}
                            char key=toupper((char)ch);
                            setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width); drawScoreboard(p1,p2,width);
                            drawSymbolWithGlow(sym,width,height); 
                            drawKeyPanel(sym,width,height);

                            if(key==toupper(sym.keyP1)){ 
                                p1+=sym.points; 
                                if(p1<0) p1=0; 
                                drawFeedback(">>> Player 1 HIT! <<<",LIGHTGREEN); 
                                soundHit();
                            }
                            else if(key==toupper(sym.keyP2)){ 
                                p2+=sym.points; 
                                if(p2<0) p2=0; 
                                drawFeedback(">>> Player 2 HIT! <<<",LIGHTGREEN); 
                                soundHit();
                            }
                            else { 
                                drawFeedback("Wrong key! No points.",RED); 
                                soundMiss(); 
                            }

                            reacted=true; setvisualpage(page); page=1-page;
                        }

                        if(GetTickCount()-start>3000){  

                            drawFeedback("Time's up! Next round.",YELLOW); 

                            reacted=true; 
                        }
                        delay(30);
                    }
                    delay(1200);
                }
            }

            // Save round scores
            if(roundNumber == 1){
                round1_p1 = p1;
                round1_p2 = p2;
            } else if(roundNumber == 2){
                round2_p1 = p1;
                round2_p2 = p2;
            } else if(roundNumber == 3){
                round3_p1 = p1;
                round3_p2 = p2;
            }

            // Winner of round
            setactivepage(page); cleardevice(); drawCosmicBackground(width,height); drawHeader(width);
            if(p1>=10){ 
                showCenteredMessage("PLAYER 1 WINS THE ROUND!",width,height,5,YELLOW); 
            }
            else { 
                showCenteredMessage("PLAYER 2 WINS THE ROUND!",width,height,5,YELLOW); 
            }
            soundRound(); celebrateWinner(width,height); setvisualpage(page); page=1-page; delay(3000);

            if(roundNumber<3){ 
                roundNumber++; 
                showCenteredMessage("Next round incoming!",width,height,4,LIGHTCYAN); 
                setvisualpage(page); page=1-page; 
                delay(2000);
            }
            else break;
        }

        // Show final scoreboard
        int total_p1 = round1_p1 + round2_p1 + round3_p1;
        int total_p2 = round1_p2 + round2_p2 + round3_p2;
        drawFinalScoreboard(round1_p1, round1_p2, round2_p1, round2_p2, 
                           round3_p1, round3_p2, total_p1, total_p2, 
                           width, height, playedRound3);

        // Ask if they want to play again
        showCenteredMessage("Play again? Press Y or N",width,height,3,LIGHTCYAN); setvisualpage(page); page=1-page;
        bool decisionMade=false;
        while(!decisionMade){ 
            if(kbhit()){ 
                char c=toupper(getch()); 
                if(c=='Y'){ 
                    playAgain=true; 
                    decisionMade=true; 
                } 
                else if(c=='N'){ 
                    playAgain=false; 
                    decisionMade=true;
                } 
            } 
            delay(50);
        }
    }

    closegraph();
    return 0;
}