#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Исходная колода карт. Значения от 2 до 14 (14 - это туз).
std::vector<int> deck = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

// Функция раздачи карт (возвращает вектор из двух случайных карт)
vector<int> deal(std::vector<int>& deck) {
    vector<int> hand;
    for (int i = 0; i < 2; i++) {
        std::random_shuffle(deck.begin(), deck.end()); // Перемешивание колоды
        int card = deck.back(); // Берем последнюю карту из колоды
        deck.pop_back(); // Удаляем ее из колоды
      // Если карта - 11, 12, 13 или 14, заменяем на J, Q, K или A соответственно
        if (card == 11) card = 'J';
        if (card == 12) card = 'Q';
        if (card == 13) card = 'K';
        if (card == 14) card = 'A';
        hand.push_back(card); // Добавляем карту в руку
    }
    return hand;
}

void play_again();

// Функция для вычисления суммы очков в руке
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

// Функция для взятия еще одной карты из колоды
std::vector<int> hit(std::vector<int>& hand) {
    int card = deck.back(); // Берем последнюю карту из колоды
    deck.pop_back(); // Удаляем ее из колоды
    if (card == 11) card = 'J';
    if (card == 12) card = 'Q';
    if (card == 13) card = 'K';
    if (card == 14) card = 'A';
    hand.push_back(card);
    return hand;
}

// Функция для очистки экрана консоли (переносимая между ОС)
void clear() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

// Функция для вывода результатов игры
void print_results(const std::vector<int>& dealer_hand, const std::vector<int>& player_hand) {
    clear();
    cout << "The dealer has a ";
    for (int card : dealer_hand) {
        std::cout << card << " ";
    }
    cout << "for a total of " << total(dealer_hand) << std::endl;
    cout << "You have a ";
    for (int card : player_hand) {
        cout << card << " ";
    }
    cout << "for a total of " << total(player_hand) << std::endl;
}

// Функция для проверки на наличие блэкджека (21 очко)
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
// Функция для определения счета игры и вывода сообщения
void score(const std::vector<int>& dealer_hand, const std::vector<int>& player_hand) {
    if (total(player_hand) == 21) {
        print_results(dealer_hand, player_hand);
        cout << "Congratulations! You got a Blackjack!\n" << std::endl;
    } else if (total(dealer_hand) == 21) {
        print_results(dealer_hand, player_hand);
        cout << "Sorry, you lose. The dealer got a blackjack.\n" << std::endl;
    } else if (total(player_hand) > 21) {
        print_results(dealer_hand, player_hand);
        cout << "Sorry. You busted. You lose.\n" << std::endl;
    } else if (total(dealer_hand) > 21) {
        print_results(dealer_hand, player_hand);
        cout << "Dealer busts. You win!\n" << std::endl;
    } else if (total(player_hand) < total(dealer_hand)) {
        print_results(dealer_hand, player_hand);
        cout << "Sorry. Your score isn't higher than the dealer. You lose.\n" << std::endl;
    } else if (total(player_hand) > total(dealer_hand)) {
        print_results(dealer_hand, player_hand);
        cout << "Congratulations. Your score is higher than the dealer. You win\n" << std::endl;
    }
}


void game();
// Функция, чтобы сыграть еще раз 
void play_again() {
    string again;
    cout << "Do you want to play again? (Y/N): ";
    cin >> again;
    transform(again.begin(), again.end(), again.begin(), ::tolower);
    if (again == "y") {
        vector<int> dealer_hand;
        vector<int> player_hand;
        deck = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
        game();
    } else {
        out << "Bye!" << std::endl;
        exit(0);
    }
}

// Основная функция игры
void game() {
    string choice;
    clear();
    cout << "WELCOME TO BLACKJACK!\n" << std::endl;
    vector<int> dealer_hand = deal(deck);
    vector<int> player_hand = deal(deck);
    while (choice != "q") {
        cout << "The dealer is showing a " << dealer_hand[0] << std::endl;
        cout << "You have a ";
        for (int card : player_hand) {
            cout << card << " ";
        }
        cout << "for a total of " << total(player_hand) << std::endl;
        blackjack(dealer_hand, player_hand);
        cout << "Do you want to [H]it, [S]tand, or [Q]uit: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
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
            cout << "Bye!" << std::endl;
            exit(0);
        }
    }
}

int main() {
    game(); // Запуск игры
    return 0;
}

