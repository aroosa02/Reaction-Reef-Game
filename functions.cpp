#include "header.h"

int page = 0;

// --- Sound functions
void soundHit()   { Beep(1200,120); }
void soundMiss()  { Beep(400,150); }
void soundRound() { Beep(800,250); }

// --- Graphics functions
void drawCosmicBackground(int width, int height) {
    setfillstyle(SOLID_FILL, BLACK);
    bar(0,0,width,height);
    for(int i=0;i<200;i++) putpixel(rand()%width, rand()%height, WHITE);
    setfillstyle(SOLID_FILL,MAGENTA);
    bar(0,0,width,height);
    for (int i = 0; i < 200; ++i) {
        putpixel(rand() % width, rand() % height, WHITE);
    }  
}

void drawHeader(int width){
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    setcolor(YELLOW);
    int tw=textwidth((char*)"~~~ Reaction Reef ~~~");
    outtextxy((width-tw)/2,20,(char*)"~~~ Reaction Reef ~~~");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    setcolor(LIGHTMAGENTA);
    const char* msg="First to 10 points wins!";
    int msgTw=textwidth((char*)msg);
    outtextxy((width-msgTw)/2,60,(char*)msg);
}

void drawScoreboard(int p1,int p2,int width){
    int sx=width/2-160, sy=100;
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL,BLACK);
    bar(sx-10,sy-10,sx+320,sy+50);
    rectangle(sx-10,sy-10,sx+320,sy+50);
    setcolor(LIGHTMAGENTA);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    char buff[100];
    sprintf(buff,"P1: %d     P2: %d",p1,p2);
    int tw=textwidth(buff);
    outtextxy(sx+(300-tw)/2,sy+5,buff);
}

void showCenteredMessage(const char* msg,int width,int height,int size,int color){
    settextstyle(BOLD_FONT,HORIZ_DIR,size);
    int tw=textwidth((char*)msg), th=textheight((char*)msg);
    setcolor(color); outtextxy((width-tw)/2,(height-th)/2,(char*)msg);
}

void drawKeyPanel(const Symbol& sym,int width,int height){
    int py=height-120, cx=width/2;
    setcolor(LIGHTCYAN); setfillstyle(SOLID_FILL,BLACK);
    bar(50,py,cx-50,py+80); rectangle(50,py,cx-50,py+80);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2); setcolor(WHITE);
    outtextxy(70,py+10,(char*)"PLAYER 1 KEY:");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    char k1[2]={sym.keyP1,'\0'}; setcolor(LIGHTBLUE);
    outtextxy(80,py+35,k1);

    setcolor(LIGHTCYAN); setfillstyle(SOLID_FILL,BLACK);
    bar(cx+50,py,width-50,py+80); rectangle(cx+50,py,width-50,py+80);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2); setcolor(WHITE);
    outtextxy(cx+70,py+10,(char*)"PLAYER 2 KEY:");
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    char k2[2]={sym.keyP2,'\0'}; setcolor(LIGHTBLUE);
    outtextxy(cx+80,py+35,k2);
}

void drawSymbolWithGlow(Symbol sym,int width,int height){
    int cx=width/2, cy=height/2+30;
    for(int r=120;r>=100;r-=5){ setcolor(MAGENTA+(120-r)/10*3); circle(cx,cy,r); delay(10);}
    setfillstyle(SOLID_FILL,LIGHTMAGENTA); setcolor(WHITE); fillellipse(cx,cy,100,100);
    settextstyle(BOLD_FONT,HORIZ_DIR,10);
    char s[2]={sym.display,'\0'};
    setcolor(MAGENTA); outtextxy(cx-30+2,cy-40+2,s);
    setcolor(WHITE); outtextxy(cx-30,cy-40,s);
}

void drawFooterHint(int width,int height,const char* msg){
    settextstyle(DEFAULT_FONT,HORIZ_DIR,1); setcolor(LIGHTGRAY); outtextxy(20,height-20,(char*)msg);
}

void drawFeedback(const char* msg,int color){ 
    setcolor(color); 
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2); 
    outtextxy(40,180,(char*)msg); 
}

void celebrateWinner(int width,int height){
    for(int i=0;i<6;i++){ 
        setcolor(rand()%16); 
        circle(rand()%width,rand()%height,20+rand()%50); 
        delay(150); 
        floodfill(rand()%width,rand()%height,rand()%16);
    }
}

void drawRound2Words(const string& word1, const string& word2, int width, int height){
    settextstyle(BOLD_FONT,HORIZ_DIR,5);
    setcolor(LIGHTCYAN);
    outtextxy(width/4 - textwidth((char*)word1.c_str())/2, height/2, (char*)word1.c_str());
    outtextxy(3*width/4 - textwidth((char*)word2.c_str())/2, height/2, (char*)word2.c_str());
}

void drawTypingProgress(const string& target, const string& typed, int player, int width, int height){
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(LIGHTGREEN);
    
    string progress;
    for(size_t i=0; i<typed.length(); i++){
        if(i < typed.length()){
            progress += typed[i];
        }
    }
    
    if(player == 1){
        outtextxy(width/4 - textwidth((char*)progress.c_str())/2, height/2 + 80, (char*)progress.c_str());
    } else {
        outtextxy(3*width/4 - textwidth((char*)progress.c_str())/2, height/2 + 80, (char*)progress.c_str());
    }
}

void drawTimer(int timeLeft, int width, int height){
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    char timerMsg[50];
    sprintf(timerMsg, "Time: %d", timeLeft);
    outtextxy(width/2 - textwidth(timerMsg)/2, height - 150, timerMsg);
}

void drawRound3Timer(int timeLeft, int width, int height, bool isSymbolMode){
    settextstyle(BOLD_FONT,HORIZ_DIR,2);
    if(isSymbolMode){
        setcolor(RED);
    } else {
        setcolor(LIGHTMAGENTA);
    }
    char timerMsg[50];
    sprintf(timerMsg, "HURRY! %d sec", timeLeft);
    outtextxy(width/2 - textwidth(timerMsg)/2, 200, timerMsg);
}

void clearKeyboardBuffer() {
    while (kbhit()) {
        getch();
    }
}

void drawFinalScoreboard(int round1_p1, int round1_p2, int round2_p1, int round2_p2, 
                         int round3_p1, int round3_p2, int total_p1, int total_p2, 
                         int width, int height, bool showRound3) {
    setactivepage(page);
    cleardevice();
    drawCosmicBackground(width, height);
    drawHeader(width);
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(LIGHTCYAN);
    showCenteredMessage("SCOREBOARD", width, height/4, 4, LIGHTCYAN);
    
    int startY = height/3;
    int rowHeight = 60;

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(width/4 - 100, startY, (char*)"ROUND");
    outtextxy(width/2 - 50, startY, (char*)"PLAYER 1");
    outtextxy(3*width/4 - 50, startY, (char*)"PLAYER 2");
    
    setcolor(LIGHTGRAY);
    line(width/4 - 120, startY + 30, 3*width/4 + 120, startY + 30);
    
    setcolor(LIGHTGREEN);
    outtextxy(width/4 - 100, startY + rowHeight, (char*)"Round 1");
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char r1p1[20], r1p2[20];
    sprintf(r1p1, "%d", round1_p1);
    sprintf(r1p2, "%d", round1_p2);
    outtextxy(width/2 - 50, startY + rowHeight, r1p1);
    outtextxy(3*width/4 - 50, startY + rowHeight, r1p2);
    
    // Round 2 scores
    setcolor(LIGHTBLUE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(width/4 - 100, startY + 2*rowHeight, (char*)"Round 2");
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    char r2p1[20], r2p2[20];
    sprintf(r2p1, "%d", round2_p1);
    sprintf(r2p2, "%d", round2_p2);
    outtextxy(width/2 - 50, startY + 2*rowHeight, r2p1);
    outtextxy(3*width/4 - 50, startY + 2*rowHeight, r2p2);
    
    // Round 3 scores (only if played)
    if(showRound3) {
        setcolor(LIGHTMAGENTA);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        outtextxy(width/4 - 100, startY + 3*rowHeight, (char*)"Round 3");
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        char r3p1[20], r3p2[20];
        sprintf(r3p1, "%d", round3_p1);
        sprintf(r3p2, "%d", round3_p2);
        outtextxy(width/2 - 50, startY + 3*rowHeight, r3p1);
        outtextxy(3*width/4 - 50, startY + 3*rowHeight, r3p2);
    }
    
    // Total scores
    setcolor(YELLOW);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(width/4 - 100, startY + (showRound3 ? 4 : 3)*rowHeight, (char*)"TOTAL");
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    char total1[20], total2[20];
    sprintf(total1, "%d", total_p1);
    sprintf(total2, "%d", total_p2);
    outtextxy(width/2 - 50, startY + (showRound3 ? 4 : 3)*rowHeight, total1);
    outtextxy(3*width/4 - 50, startY + (showRound3 ? 4 : 3)*rowHeight, total2);
    
    // Draw final separator line
    setcolor(LIGHTGRAY);
    line(width/4 - 120, startY + (showRound3 ? 4 : 3)*rowHeight - 15, 
         3*width/4 + 120, startY + (showRound3 ? 4 : 3)*rowHeight - 15);
    
    // Show winner
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    if(total_p1 > total_p2) {
        setcolor(LIGHTGREEN);
        showCenteredMessage("PLAYER 1 WINS THE GAME!", width, height - 300, 3, LIGHTGREEN);
    } else if(total_p2 > total_p1) {
        setcolor(LIGHTBLUE);
        showCenteredMessage("PLAYER 2 WINS THE GAME!", width, height - 300, 3, LIGHTBLUE);
    } else {
        setcolor(YELLOW);
        showCenteredMessage("IT'S A TIE!", width, height - 100, 3, YELLOW);
    }
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(LIGHTGRAY);
    int bottomPadding = 05;
    showCenteredMessage("Press any key to continue...", width, height - bottomPadding, 1, LIGHTGRAY);
    
    setvisualpage(page);
    page = 1 - page;
    
    // Wait for key press
    while(!kbhit()) {
        delay(50);
    }
    getch(); // Clear the key
}



bool showRound3Choice(int width, int height, int round1_p1, int round1_p2, int round2_p1, int round2_p2){
    setactivepage(page); 
    cleardevice(); 
    drawCosmicBackground(width,height); 
    drawHeader(width);
    
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    setcolor(LIGHTCYAN);
    showCenteredMessage("ROUND 3: CRAZY SHUFFLE!", width, height/4, 4, LIGHTCYAN);
    
    // Show current scores
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char scoreMsg[100];
    sprintf(scoreMsg, "Current Scores: P1: %d | P2: %d", round1_p1 + round2_p1, round1_p2 + round2_p2);
    outtextxy(width/2 - textwidth(scoreMsg)/2, height/4 + 60, scoreMsg);
    
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    setcolor(WHITE);
    string rules[] = {
        "Mix of Round 1 & Round 2!",
        "Word Mode: 5 seconds to type full word",
        "Symbol Mode: 2 seconds to press key",
        "Ready for the challenge?"
    };
    
    for(int i=0; i<4; i++){
        outtextxy(width/2 - textwidth((char*)rules[i].c_str())/2, 
                  height/2 + i*40, 
                  (char*)rules[i].c_str());
    }
    
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(YELLOW);
    showCenteredMessage("Press Y to play Round 3 or N to skip to final scores", width, height-100, 3, YELLOW);
    
    setvisualpage(page); 
    page=1-page;
    
    // Wait for user choice
    while(true){
        if(kbhit()){
            char ch = toupper(getch());
            if(ch == 'Y'){
                soundRound();
                return true;
            } else if(ch == 'N'){
                return false;
            }
        }
        delay(50);
    }
}