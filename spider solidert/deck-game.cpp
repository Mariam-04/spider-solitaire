#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "ConsoleFunctions.h"

class PlayingCard
{
private:
    int rank; //integer 1 – 13
    int suit; //integer 0 – 3
    char color; // red or black - ‘b’ for black, ‘r’ for red
public:
    static const int Diamond = 0;
    static const int Heart = 1;
    static const int Spade = 2;
    static const int Club = 3;
    PlayingCard(int rrank = 0, int ssuit = 0)
    {
        if (rrank >= 1 && rrank <= 13 && ssuit >= 0 && ssuit <= 3)
        {
            rank = rrank;
            suit = ssuit;
            if (suit == 0 || suit == 1) {
                color = 'r';
            }
            else
            {
                color = 'b';
            }
        }
    }
    void display(int x, int y)
    {
        ConsoleColor backcol(white);
        ConsoleFunctions c1;

        // Set the text color based on the card's suit
        if (suit == Heart) {
            ConsoleColor textcol(red);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 8 + 1; j++) {
                    c1.SetCursorAt(y + j, x + i);

                    if (i == 0 && j == 0) {
                        c1.SetColor(textcol, backcol);
                        c1.SetCursorAt(y + j, x + i);
                        wstring symbol = L"\u2665";
                        _setmode(_fileno(stdout), _O_U8TEXT);
                        wcout << symbol;
                        _setmode(_fileno(stdout), _O_TEXT);

                    }
                    else if (i == 0 && j == 1) {
                        c1.SetColor(textcol, backcol);
                        if (rank == 11) cout << 'J';
                        else if (rank == 1) cout << 'A';
                        else if (rank == 12) cout << 'Q';
                        else if (rank == 13) cout << 'K';
                        else if (rank == 10) {
                            cout << rank;
                            j++;
                        }
                        else cout << rank;
                    }
                    else if ((i == 1 || i == 4) && j == 0 || (i == 1 || i == 4) && j == 7 || i == 2 && j == 0 || i == 3 && j == 7) {
                        c1.SetColor(textcol, backcol);
                        cout << " ";
                    }
                    else if (i == 5 && j == 7) {
                        c1.SetColor(textcol, backcol);
                        if (rank == 11) cout << 'J';
                        else if (rank == 1) cout << 'A';
                        else if (rank == 12) cout << 'Q';
                        else if (rank == 13) cout << 'K';
                        else if (rank == 10) {
                            cout << rank;
                            j++;
                        }
                        else cout << rank;
                    }
                    else if (i == 5 && j == 6) {
                        c1.SetColor(textcol, backcol);
                        c1.SetCursorAt(y + j, x + i);
                        wstring symbol = L"\u2665";
                        _setmode(_fileno(stdout), _O_U8TEXT);
                        wcout << symbol;
                        _setmode(_fileno(stdout), _O_TEXT);
                    }
                    else {
                        cout << " ";
                    }
                }
            }
        }
        // Similar code for other suits (Diamond, Spade, Club)...
    }
};

class PileofCards {
private:
    std::vector<PlayingCard> pile;
public:
    PileofCards() {}
    void Add(const PlayingCard& card) {
        pile.push_back(card);
    }
    PlayingCard Remove() {
        if (IsEmpty()) {
            std::cout << "Error: The Pile of Cards is already empty!" << std::endl;
            return PlayingCard();
        }
        else {
            PlayingCard removed_card = pile.back();
            pile.pop_back();
            return removed_card;
        }
    }
    PlayingCard Peek() const {
        return pile.back();
    }
    bool IsEmpty() const {
        return pile.empty();
    }
    void display(int x, int y) {
        for (const auto& card : pile) {
            card.display(x, y);
            y += 10;
        }
    }
};

class Deck {
private:
    std::vector<PlayingCard> deck;
public:
    Deck() {
        for (int i = 1; i <= 13; i++) {
            deck.emplace_back(i, PlayingCard::Diamond);
            deck.emplace_back(i, PlayingCard::Heart);
            deck.emplace_back(i, PlayingCard::Spade);
            deck.emplace_back(i, PlayingCard::Club);
        }
    }
    void Shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }
    bool IsEmpty() {
        return deck.empty();
    }
    PlayingCard Draw() {
        if (IsEmpty()) {
            std::cout << "Error: The Deck is empty!" << std::endl;
            return PlayingCard();
        }
        else {
            PlayingCard drawn_card = deck.back();
            deck.pop_back();
            return drawn_card;
        }
    }
    void display(int x, int y) {
        ConsoleFunctions c;
        c.setConsoleWindowAndBufferSize(800, 800);
        for (const auto& card : deck) {
            card.display(x, y);
            y += 10;
        }
    }
};

class SpiderSolitaire {
private:
    Deck deck;
    std::vector<PileofCards> tableau;
    PileofCards stock;
public:
    SpiderSolitaire() : tableau(10) {
        deck.Shuffle();
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < (i < 4 ? 6 : 5); j++) {
                tableau[i].Add(deck.Draw());
            }
        }
    }
    void display() {
        int x = 0;
        int y = 0;
        for (auto& pile : tableau) {
            pile.display(x, y);
            x += 12;
        }
        stock.display(x, y);
    }
};

int main() {
    SpiderSolitaire game;
    game.display();
    return 0;
}
