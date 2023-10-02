#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

std::vector<int> deck = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

std::vector<int> deal(std::vector<int>& deck) {
    std::vector<int> hand;
    for (int i = 0; i < 2; i++) {
        std::random_shuffle(deck.begin(), deck.end());
        int card = deck.back();
        deck.pop_back();
        if (card == 11) card = 'J';
        if (card == 12) card = 'Q';
        if (card == 13) card = 'K';
        if (card == 14) card = 'A';
        hand.push_back(card);
    }
    return hand;
}

void play_again();

int total(const std::vector<int>& hand) {
    int total = 0;
    for (int card : hand) {
        if (card == 'J' || card == 'Q' || card == 'K') {
            total += 10;
        } else if (card == 'A') {
            if (total >= 11) total += 1;
        } else {
            total += card;
        }
    }
    return total;
}

std::vector<int> hit(std::vector<int>& hand) {
    int card = deck.back();
    deck.pop_back();
    if (card == 11) card = 'J';
    if (card == 12) card = 'Q';
    if (card == 13) card = 'K';
    if (card == 14) card = 'A';
    hand.push_back(card);
    return hand;
}

void clear() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

void print_results(const std::vector<int>& dealer_hand, const std::vector<int>& player_hand) {
    clear();
    std::cout << "The dealer has a ";
    for (int card : dealer_hand) {
        std::cout << card << " ";
    }
    std::cout << "for a total of " << total(dealer_hand) << std::endl;
    std::cout << "You have a ";
    for (int card : player_hand) {
        std::cout << card << " ";
    }
    std::cout << "for a total of " << total(player_hand) << std::endl;
}

void blackjack(const std::vector<int>& dealer_hand, const std::vector<int>& player_hand) {
    if (total(player_hand) == 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Congratulations! You got a Blackjack!\n" << std::endl;
        play_again();
    } else if (total(dealer_hand) == 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Sorry, you lose. The dealer got a blackjack.\n" << std::endl;
        play_again();
    }
}

void score(const std::vector<int>& dealer_hand, const std::vector<int>& player_hand) {
    if (total(player_hand) == 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Congratulations! You got a Blackjack!\n" << std::endl;
    } else if (total(dealer_hand) == 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Sorry, you lose. The dealer got a blackjack.\n" << std::endl;
    } else if (total(player_hand) > 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Sorry. You busted. You lose.\n" << std::endl;
    } else if (total(dealer_hand) > 21) {
        print_results(dealer_hand, player_hand);
        std::cout << "Dealer busts. You win!\n" << std::endl;
    } else if (total(player_hand) < total(dealer_hand)) {
        print_results(dealer_hand, player_hand);
        std::cout << "Sorry. Your score isn't higher than the dealer. You lose.\n" << std::endl;
    } else if (total(player_hand) > total(dealer_hand)) {
        print_results(dealer_hand, player_hand);
        std::cout << "Congratulations. Your score is higher than the dealer. You win\n" << std::endl;
    }
}

void game();

void play_again() {
    std::string again;
    std::cout << "Do you want to play again? (Y/N): ";
    std::cin >> again;
    std::transform(again.begin(), again.end(), again.begin(), ::tolower);
    if (again == "y") {
        std::vector<int> dealer_hand;
        std::vector<int> player_hand;
        deck = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        game();
    } else {
        std::cout << "Bye!" << std::endl;
        exit(0);
    }
}

void game() {
    std::string choice;
    clear();
    std::cout << "WELCOME TO BLACKJACK!\n" << std::endl;
    std::vector<int> dealer_hand = deal(deck);
    std::vector<int> player_hand = deal(deck);
    while (choice != "q") {
        std::cout << "The dealer is showing a " << dealer_hand[0] << std::endl;
        std::cout << "You have a ";
        for (int card : player_hand) {
            std::cout << card << " ";
        }
        std::cout << "for a total of " << total(player_hand) << std::endl;
        blackjack(dealer_hand, player_hand);
        std::cout << "Do you want to [H]it, [S]tand, or [Q]uit: ";
        std::cin >> choice;
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
        clear();
        if (choice == "h") {
            hit(player_hand);
            while (total(dealer_hand) < 17) {
                hit(dealer_hand);
            }
            score(dealer_hand, player_hand);
            play_again();
        } else if (choice == "s") {
            while (total(dealer_hand) < 17) {
                hit(dealer_hand);
            }
            score(dealer_hand, player_hand);
            play_again();
        } else if (choice == "q") {
            std::cout << "Bye!" << std::endl;
            exit(0);
        }
    }
}

int main() {
    game();
    return 0;
}
