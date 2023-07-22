/*
Jogo de Bingo. Neste exercício você vai simular o jogo de Bingo para apenas uma cartela.
Começa gerando uma lista de todas as chamadas válidas de bingo (B1 até O75). Depois que
a lista estiver pronta, você pode embaralhar seus elementos chamando a função shuffle do
módulo random do Python. Então seu programa deve ir utilizando os valores da lista para
anunciar os números sorteados e zerar os números correspondentes na cartela até que ela
contenha uma linha, coluna ou diagonal zerada. No seu programa principal, faça uma
simulação de 1.000 partidas (sempre com uma nova cartela) e mostre o número mínimo, o
máximo e a média de chamadas até que se tenha uma cartela vencedora. Utilize seu código
dos dois exercícios anteriores e não se esqueça de criar novas funções sempre que você
identificar algum procedimento que pode ser melhor organizado dentro de uma função.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <functional>

struct Results
{
    int min;
    int max;
    int total_plays;
    int lucky;
    int unlucky;
    float mean;
};
typedef std::vector<int> bingo_card_t;

bool is_in(std::vector<int> list, int num);
bingo_card_t generate_card();
Results simulate_n_times(
    int num,
    std::function<bool (int)> break_callback = [] (int plays) {return false;}
);
int simulate(bingo_card_t &card);
void mark(bingo_card_t &card, int num);
bool check_win(bingo_card_t card);

std::vector<int> numbers;

int main()
{
    srand(time(NULL));
    for (size_t i = 1; i < 76; i++)
        numbers.push_back(i);

    long unsigned int total = 0;
    int lucky = 0;
    int unlucky = 0;
    for (int i = 0; i < 200; i++)
    {
        if (i % 2 == 0)
        {
            std::cout << "\r" << i / 2 << "%";
            fflush(stdout);
        }

        Results r = simulate_n_times(100000);
        total += r.total_plays;
        lucky += r.lucky;
        unlucky += r.unlucky;
    }

    std::cout << std::endl;
    std::cout << "Total: " << total << std::endl
              << "Lucky: " << lucky << " Unlucky" << unlucky << std::endl
              << "Probability lucky: " << (double)lucky / total << std::endl
              << "Probability unlucky: " << (double)unlucky / total << std::endl;

    /*
    std::cout << "Min: " << r.min << std::endl
              << "Max: " << r.max << std::endl
              << "Mean: " << r.mean << std::endl
              << "Lucky: " << r.lucky << std::endl
              << "Unlucky: " << r.unlucky << std::endl
              << "Total plays: " << r.total_plays << std::endl;
    */

    return 0;
}

bool is_in(std::vector<int> list, int num)
{
    for (int e : list)
        if (e == num)
            return true;

    return false;
}

bingo_card_t generate_card()
{
    bingo_card_t card;
    std::vector<int> used_num;
    int i = 0;
    while (i < 25)
    {
        int num = rand() % 75 + 1;
        if (is_in(used_num, num))
            continue;

        card.push_back(num);
        used_num.push_back(num);
        i++;
    }

    return card;
}

Results simulate_n_times(int num, std::function<bool (int)> break_callback)
{
    Results r;
    r.min = 0;
    r.max = 0;
    r.total_plays = 0;
    r.lucky = 0;
    r.unlucky = 0;
    r.mean = 0;
    for (size_t i = 0; i < num; i++)
    {
        bingo_card_t card = generate_card();
        int plays = simulate(card);
        if (plays <= r.min || r.min == 0)
            r.min = plays;
        if (plays >= r.max || r.max == 0)
            r.max = plays;

        if (plays == 5)
            r.lucky++;
        else if (plays == 71)
            r.unlucky++;
        if (break_callback(plays))
            break;

        r.mean += plays;
        r.total_plays++;
    }
    r.mean /= r.total_plays;

    return r;
}

int simulate(bingo_card_t &card)
{
    std::vector<int> nums;
    for (int e : numbers)
        nums.push_back(e);

    int i = 0;
    while (!check_win(card))
    {
        int random_idx = rand() % nums.size();
        mark(card, nums[random_idx]);
        nums.erase(nums.begin() + random_idx);
        i++;
    }

    return i;
}

void mark(bingo_card_t &card, int num)
{
    for (size_t i = 0; i < card.size(); i++)
    {
        if (card[i] == num)
        {
            card[i] = 0;
            return;
        }
    }
}

bool check_win(bingo_card_t card)
{
    // vertical wins
    for (int i = 0; i < 5; i++)
        if (card[i] == 0 && card[i + 5] == 0 && card[i + 10] == 0
            && card[i + 15] == 0 && card[i + 20] == 0)
            return true;

    // horizontal wins
    for (int i = 0; i < 21; i += 5)
        if (card[i] == 0 && card[i + 1] == 0 && card[i + 2] == 0
            && card[i + 3] == 0 && card[i + 4] == 0)
            return true;

    // diagonals wins
    return (card[0] == 0 && card[6] == 0 && card[12] == 0 && card[18] == 0 && card[24] == 0)
           || (card[4] == 0 && card[8] == 0 && card[12] == 0 && card[16] == 0 && card[20] == 0);
}
