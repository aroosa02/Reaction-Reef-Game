#ifndef HEADER_H
#define HEADER_H
#include <graphics.h>
#include <winbgim.h>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

extern int page;

struct Symbol {
    char display;
    char keyP1;
    char keyP2;
    int points;
    const char* desc;
};
void initwindow(int width, int height, int title, int x,int y);

// --- Sound functions
void soundHit();
void soundMiss();
void soundRound();

// --- Graphics functions
void drawCosmicBackground(int width, int height);
void drawHeader(int width);
void drawScoreboard(int p1, int p2, int width);
void showCenteredMessage(const char* msg, int width, int height, int size = 3, int color = WHITE);
void drawKeyPanel(const Symbol& sym, int width, int height);
void drawSymbolWithGlow(Symbol sym, int width, int height);
void drawFooterHint(int width, int height, const char* msg);
void drawFeedback(const char* msg, int color);
void celebrateWinner(int width, int height);
void clearKeyboardBuffer();

// --- Round 2 functions
void drawRound2Words(const string& word1, const string& word2, int width, int height);
void drawTypingProgress(const string& target, const string& typed, int player, int width, int height);
void drawTimer(int timeLeft, int width, int height);


// --- Round 3 functions
void drawRound3Timer(int timeLeft, int width, int height, bool isSymbolMode);
bool showRound3Choice(int width, int height, int round1_p1, int round1_p2, int round2_p1, int round2_p2);
void drawRound3DoubleWords( string p1w1, string p1w2, int stage1, string p2w1, string p2w2, int stage2, int width, int height);

// --- Final scoreboard
void drawFinalScoreboard(int round1_p1, int round1_p2, int round2_p1, int round2_p2, 
                         int round3_p1, int round3_p2, int total_p1, int total_p2, 
                         int width, int height, bool showRound3);

#endif